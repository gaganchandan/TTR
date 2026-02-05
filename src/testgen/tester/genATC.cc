#include "genATC.hh"
#include <iostream>

// ============================================================================
// ATCGenerator Implementation
// ============================================================================

ATCGenerator::ATCGenerator(const Spec *spec, TypeMap typeMap)
    : spec(spec), typeMap(std::move(typeMap)) {
  std::cout << "Received Spec with " << spec->globals.size() << " globals, "
            << spec->init.size() << " init statements, "
            << spec->functions.size() << " functions, and "
            << spec->blocks.size() << " blocks." << std::endl;
}

/**
 * Generate initialization statements from spec.global
 * For each global variable declaration, create initialization
 */
vector<std::unique_ptr<Stmt>> ATCGenerator::genInit(const Spec *spec) {
  vector<std::unique_ptr<Stmt>> initStmts;

  // Process global variable initializations from spec.init
  for (const auto &init : spec->init) {
    // Create assignment: varName = expr
    auto assignStmt =
        std::make_unique<Assign>(std::make_unique<Var>(init->varName),
                                 convertExpr(init->expr, nullptr, ""));
    initStmts.push_back(std::move(assignStmt));
  }

  return initStmts;
}

/**
 * Convert expression by renaming local variables with suffix
 * Global variables (not in symTable) remain unchanged
 */
std::unique_ptr<Expr>
ATCGenerator::convertExpr(const std::unique_ptr<Expr> &expr,
                          SymbolTable *symTable, const string &suffix) {
  if (!expr) {
    return nullptr;
  }

  // Handle Var
  if (expr->exprType == ExprType::VAR) {
    Var *var = dynamic_cast<Var *>(expr.get());
    // If variable is in local scope, add suffix
    if (symTable && symTable->hasKey(const_cast<string *>(&var->name))) {
      return std::make_unique<Var>(var->name + suffix);
    }
    // Global variable - no suffix
    return std::make_unique<Var>(var->name);
  }

  // Handle FuncCall
  else if (expr->exprType == ExprType::FUNC_CALL_EXPR) {
    FuncCall *func = dynamic_cast<FuncCall *>(expr.get());
    vector<std::unique_ptr<Expr>> newArgs;
    for (const auto &arg : func->args) {
      newArgs.push_back(convertExpr(arg, symTable, suffix));
    }
    return std::make_unique<FuncCall>(func->name, std::move(newArgs));
  }
  // Handle Num
  else if (expr->exprType == ExprType::NUM) {
    Num *num = dynamic_cast<Num *>(expr.get());
    return std::make_unique<Num>(num->value);
  }
  // Handle String
  else if (expr->exprType == ExprType::STRING) {
    String *str = dynamic_cast<String *>(expr.get());
    return std::make_unique<String>(str->value);
  }

  // Handle Bool
  else if (expr->exprType == ExprType::BOOL) {
    Bool *b = dynamic_cast<Bool *>(expr.get());
    return std::make_unique<Bool>(b->value);
  }

  // Handle Set
  else if (expr->exprType == ExprType::SET) {
    Set *set = dynamic_cast<Set *>(expr.get());
    vector<std::unique_ptr<Expr>> newElements;
    for (const auto &elem : set->elements) {
      newElements.push_back(convertExpr(elem, symTable, suffix));
    }
    return std::make_unique<Set>(std::move(newElements));
  }

  // Handle Map
  else if (expr->exprType == ExprType::MAP) {
    Map *map = dynamic_cast<Map *>(expr.get());
    vector<pair<std::unique_ptr<Var>, std::unique_ptr<Expr>>> newValue;
    for (const auto &kv : map->value) {
      auto newKey =
          convertExpr(reinterpret_cast<const std::unique_ptr<Expr> &>(kv.first),
                      symTable, suffix);
      auto newVal = convertExpr(kv.second, symTable, suffix);
      newValue.push_back(
          make_pair(std::unique_ptr<Var>(dynamic_cast<Var *>(newKey.release())),
                    std::move(newVal)));
    }
    return std::make_unique<Map>(std::move(newValue));
  }

  // Handle Tuple
  else if (expr->exprType == ExprType::TUPLE) {
    Tuple *tuple = dynamic_cast<Tuple *>(expr.get());
    vector<std::unique_ptr<Expr>> newExprs;
    for (const auto &e : tuple->exprs) {
      newExprs.push_back(convertExpr(e, symTable, suffix));
    }
    return std::make_unique<Tuple>(std::move(newExprs));
  }

  return nullptr;
}

/**
 * Extract variables with prime notation (') from postcondition
 * Example: U' in "U' = U union {uid -> p}" → adds "U" to primedVars
 */
void ATCGenerator::extractPrimedVars(const std::unique_ptr<Expr> &expr,
                                     set<string> &primedVars) {
  if (!expr)
    return;

  // Check for prime function call: '(varname)
  if (expr->exprType == ExprType::FUNC_CALL_EXPR) {
    FuncCall *func = dynamic_cast<FuncCall *>(expr.get());
    if (func->name == "'" && func->args.size() > 0) {
      // Extract the variable name inside the prime
      if (func->args[0]->exprType == ExprType::VAR) {
        Var *var = dynamic_cast<Var *>(func->args[0].get());
        primedVars.insert(var->name);
      }
    } else {
      // Recursively check arguments
      for (const auto &arg : func->args) {
        extractPrimedVars(arg, primedVars);
      }
    }
  }

  // Handle Set
  else if (expr->exprType == ExprType::SET) {
    Set *set = dynamic_cast<Set *>(expr.get());
    for (const auto &elem : set->elements) {
      extractPrimedVars(elem, primedVars);
    }
  }

  // Handle Map
  else if (expr->exprType == ExprType::MAP) {
    Map *map = dynamic_cast<Map *>(expr.get());
    for (const auto &kv : map->value) {
      extractPrimedVars(
          reinterpret_cast<const std::unique_ptr<Expr> &>(kv.first),
          primedVars);
      extractPrimedVars(kv.second, primedVars);
    }
  }

  // Handle Tuple
  else if (expr->exprType == ExprType::TUPLE) {
    Tuple *tuple = dynamic_cast<Tuple *>(expr.get());
    for (const auto &e : tuple->exprs) {
      extractPrimedVars(e, primedVars);
    }
  }
}

/**
 * Remove prime notation from expression
 * - '(U) → U
 * - U (when U is in primedVars) → U_old
 */
std::unique_ptr<Expr>
ATCGenerator::removePrimeNotation(const std::unique_ptr<Expr> &expr,
                                  const set<string> &primedVars,
                                  bool insidePrime) {
  if (!expr)
    return nullptr;

  // Handle Var
  if (expr->exprType == ExprType::VAR) {
    Var *var = dynamic_cast<Var *>(expr.get());
    if (insidePrime) {
      // Inside prime: '(U) → U
      return std::make_unique<Var>(var->name);
    } else if (primedVars.find(var->name) != primedVars.end()) {
      // Outside prime but variable has primed version: U → U_old
      return std::make_unique<Var>(var->name + "_old");
    }
    return std::make_unique<Var>(var->name);
  }

  // Handle FuncCall
  if (expr->exprType == ExprType::FUNC_CALL_EXPR) {
    FuncCall *func = dynamic_cast<FuncCall *>(expr.get());
    if (func->name == "'" && func->args.size() > 0) {
      // Remove the prime operator
      return removePrimeNotation(func->args[0], primedVars, true);
    }

    vector<std::unique_ptr<Expr>> newArgs;
    for (const auto &arg : func->args) {
      newArgs.push_back(removePrimeNotation(arg, primedVars, insidePrime));
    }
    return std::make_unique<FuncCall>(func->name, std::move(newArgs));
  }

  // Handle Num
  if (expr->exprType == ExprType::NUM) {
    Num *num = dynamic_cast<Num *>(expr.get());
    return std::make_unique<Num>(num->value);
  }

  // Handle String
  if (expr->exprType == ExprType::STRING) {
    String *str = dynamic_cast<String *>(expr.get());
    return std::make_unique<String>(str->value);
  }

  // Handle Set
  if (expr->exprType == ExprType::SET) {
    Set *set = dynamic_cast<Set *>(expr.get());
    vector<std::unique_ptr<Expr>> newElements;
    for (const auto &elem : set->elements) {
      newElements.push_back(removePrimeNotation(elem, primedVars, insidePrime));
    }
    return std::make_unique<Set>(std::move(newElements));
  }

  // Handle Map
  if (expr->exprType == ExprType::MAP) {
    Map *map = dynamic_cast<Map *>(expr.get());
    vector<pair<std::unique_ptr<Var>, std::unique_ptr<Expr>>> newValue;
    for (const auto &kv : map->value) {
      auto newKey = removePrimeNotation(
          reinterpret_cast<const std::unique_ptr<Expr> &>(kv.first), primedVars,
          insidePrime);
      auto newVal = removePrimeNotation(kv.second, primedVars, insidePrime);
      newValue.push_back(
          make_pair(std::unique_ptr<Var>(dynamic_cast<Var *>(newKey.release())),
                    std::move(newVal)));
    }
    return std::make_unique<Map>(std::move(newValue));
  }

  // Handle Tuple
  if (expr->exprType == ExprType::TUPLE) {
    Tuple *tuple = dynamic_cast<Tuple *>(expr.get());
    vector<std::unique_ptr<Expr>> newExprs;
    for (const auto &e : tuple->exprs) {
      newExprs.push_back(removePrimeNotation(e, primedVars, insidePrime));
    }
    return std::make_unique<Tuple>(std::move(newExprs));
  }

  return nullptr;
}

/**
 * Collect input variables from expression
 * Only variables in local symbol table are considered input variables
 */
void ATCGenerator::collectInputVars(const std::unique_ptr<Expr> &expr,
                                    vector<std::unique_ptr<Expr>> &inputVars,
                                    const string &suffix, SymbolTable *symTable,
                                    TypeMap &localTypeMap) {
  if (!expr)
    return;

  // Handle Var
  if (expr->exprType == ExprType::VAR) {
    Var *var = dynamic_cast<Var *>(expr.get());
    if (symTable && symTable->hasKey(const_cast<string *>(&var->name))) {
      // This is an input variable
      inputVars.push_back(std::make_unique<Var>(var->name + suffix));

      // Track type if available
      if (typeMap.hasValue(var->name)) {
        // Copy type to local type map with suffix
        // Note: Type cloning would be needed for proper implementation
      }
    }
    return;
  }

  // Handle FuncCall - recurse into arguments
  if (expr->exprType == ExprType::FUNC_CALL_EXPR) {
    FuncCall *func = dynamic_cast<FuncCall *>(expr.get());
    for (const auto &arg : func->args) {
      collectInputVars(arg, inputVars, suffix, symTable, localTypeMap);
    }
    return;
  }

  // Handle Set
  if (expr->exprType == ExprType::SET) {
    Set *set = dynamic_cast<Set *>(expr.get());
    for (const auto &elem : set->elements) {
      collectInputVars(elem, inputVars, suffix, symTable, localTypeMap);
    }
    return;
  }

  // Handle Map
  if (expr->exprType == ExprType::MAP) {
    Map *map = dynamic_cast<Map *>(expr.get());
    for (const auto &kv : map->value) {
      collectInputVars(
          reinterpret_cast<const std::unique_ptr<Expr> &>(kv.first), inputVars,
          suffix, symTable, localTypeMap);
      collectInputVars(kv.second, inputVars, suffix, symTable, localTypeMap);
    }
    return;
  }

  // Handle Tuple
  if (expr->exprType == ExprType::TUPLE) {
    Tuple *tuple = dynamic_cast<Tuple *>(expr.get());
    for (const auto &e : tuple->exprs) {
      collectInputVars(e, inputVars, suffix, symTable, localTypeMap);
    }
    return;
  }
}

/**
 * Convert HTTPResponseCode to string variable name
 */
string httpResponseCodeToString(HTTPResponseCode code) {
  switch (code) {
  case HTTPResponseCode::OK_200:
    return "_RESPONSE_200";
  case HTTPResponseCode::CREATED_201:
    return "_RESPONSE_201";
  case HTTPResponseCode::BAD_REQUEST_400:
    return "_RESPONSE_400";
  default:
    return "_RESPONSE_UNKNOWN";
  }
}

/**
 * Create input statement: var := input()
 */
std::unique_ptr<Stmt>
ATCGenerator::makeInputStmt(std::unique_ptr<Expr> varExpr) {
  if (varExpr->exprType != ExprType::VAR) {
    return nullptr;
  }

  Var *var = dynamic_cast<Var *>(varExpr.get());
  vector<std::unique_ptr<Expr>> args;
  auto inputCall = std::make_unique<FuncCall>("input", std::move(args));

  return std::make_unique<Assign>(std::make_unique<Var>(var->name),
                                  std::move(inputCall));
}

/**
 * Generate a block for a single API call
 * Following the algorithm from design notes
 */
vector<std::unique_ptr<Stmt>> ATCGenerator::genBlock(const Spec *spec,
                                                     const API *block,
                                                     SymbolTable *blockSymTable,
                                                     int blockIndex) {
  vector<std::unique_ptr<Stmt>> blockStmts;
  TypeMap localTypeMap;
  string suffix = to_string(blockIndex);

  // Step 1: Collect input variables from API call arguments and precondition
  vector<std::unique_ptr<Expr>> rawInputVars;
  // Collect from args
  for (const auto &arg : block->call->call->args) {
    collectInputVars(arg, rawInputVars, suffix, blockSymTable, localTypeMap);
  }
  // Collect from precondition (to support Any(x))
  if (block->pre) {
    collectInputVars(block->pre, rawInputVars, suffix, blockSymTable,
                     localTypeMap);
  }

  // Deduplicate input variables
  vector<std::unique_ptr<Expr>> inputVars;
  set<string> seenVars;
  for (auto &varExpr : rawInputVars) {
    if (varExpr->exprType == ExprType::VAR) {
      Var *v = dynamic_cast<Var *>(varExpr.get());
      if (seenVars.find(v->name) == seenVars.end()) {
        seenVars.insert(v->name);
        inputVars.push_back(std::move(varExpr));
      }
    }
  }

  // Step 2: Create input statements for each input variable
  // μ[a] := input(σ_b[a])()
  for (auto &inputVar : inputVars) {
    auto inputStmt = makeInputStmt(std::move(inputVar));
    if (inputStmt) {
      blockStmts.push_back(std::move(inputStmt));
    }
  }

  // Step 3: Generate precondition assumption
  // assume(genPred(σ_b))
  if (block->pre) {
    auto convertedPre = convertExpr(block->pre, blockSymTable, suffix);
    blockStmts.push_back(std::make_unique<Assume>(std::move(convertedPre)));
  }

  // Step 4: Handle primed variables in postcondition
  // Extract variables with prime notation (e.g., U')
  set<string> primedVars;
  if (block->call->response.expr) {
    extractPrimedVars(block->call->response.expr, primedVars);
  }

  // Step 5: Create old variable assignments for primed variables
  // For each primed variable U', create: U_old = U
  for (const auto &varName : primedVars) {
    vector<std::unique_ptr<Expr>> eqArgs;
    eqArgs.push_back(std::make_unique<Var>(varName + "_old"));
    eqArgs.push_back(std::make_unique<Var>(varName));
    auto eqCall = std::make_unique<FuncCall>("=", std::move(eqArgs));
    blockStmts.push_back(
        std::make_unique<Assign>(std::make_unique<Var>(varName + "_old"),
                                 std::make_unique<Var>(varName)));
  }

  // Step 6: Generate API call statement
  // Convert the API call with renamed variables
  vector<std::unique_ptr<Expr>> convertedArgs;
  for (const auto &arg : block->call->call->args) {
    convertedArgs.push_back(convertExpr(arg, blockSymTable, suffix));
  }
  auto convertedCall = std::make_unique<FuncCall>(block->call->call->name,
                                                  std::move(convertedArgs));

  // Create LHS using ResponseExpr from the API call response
  // ResponseExpr contains (_RESPONSE_CODE_XXX, expr) or just _RESPONSE_CODE_XXX
  std::unique_ptr<Expr> returnVar = nullptr;

  if (block->call->response.expr) {
    // Convert the response expression to get variable names with suffix
    returnVar = convertExpr(block->call->response.expr, blockSymTable, suffix);
  } else {
    // Fallback to default result variable
    returnVar = std::make_unique<Var>("_result" + suffix);
  }

  // Create assignment
  auto callStmt = std::make_unique<Assign>(
      std::unique_ptr<Var>(dynamic_cast<Var *>(returnVar.release())),
      std::move(convertedCall));
  blockStmts.push_back(std::move(callStmt));

  // Step 7: Generate postcondition assertion
  // assert(post) where primes are removed
  // if (block->call->response.expr) {
  //   auto convertedPost =
  //       convertExpr(block->call->response.expr, blockSymTable, suffix);
  //   auto postWithoutPrimes = removePrimeNotation(convertedPost, primedVars);
  //   blockStmts.push_back(
  //       std::make_unique<Assert>(std::move(postWithoutPrimes)));
  // }
  if (block->post) {
    auto convertedPost = convertExpr(block->post, blockSymTable, suffix);
    auto postWithoutPrimes = removePrimeNotation(convertedPost, primedVars);
    blockStmts.push_back(
        std::make_unique<Assert>(std::move(postWithoutPrimes)));
  }

  return blockStmts;
}

/**
 * Main generation function
 * Implements the genATC algorithm from design notes
 */
Program ATCGenerator::generate(const Spec *spec, SymbolTable *globalSymTable,
                               vector<string> testString) {
  vector<std::unique_ptr<Stmt>> programStmts;

  // Step 1: Generate initialization block
  auto initStmts = genInit(spec);
  for (auto &stmt : initStmts) {
    programStmts.push_back(std::move(stmt));
  }

  // Step 2: Generate blocks for each API call in spec
  // Each block uses a child symbol table from the global symbol table

  for (size_t j = 0; j < testString.size(); j++) {

    for (size_t i = 0; i < spec->blocks.size(); i++) {
      std::cout << "Processing block: " << spec->blocks[i]->name
                << " against test string: " << testString[j] << std::endl;
      if (testString[j] != spec->blocks[i]->name) {
        continue;
      } else {
        const API *block = spec->blocks[i].get();
        SymbolTable *blockSymTable =
            globalSymTable ? globalSymTable->getChild(i) : nullptr;

        if (block && blockSymTable) {
          // Generate statements for this block
          auto blockStmts = genBlock(spec, block, blockSymTable, i);
          for (auto &stmt : blockStmts) {
            programStmts.push_back(std::move(stmt));
          }
        }
      }
    }
  }

  return Program(std::move(programStmts));
}
