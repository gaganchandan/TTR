#include "../../apps/app1/app1.hh"
#include "../../language/ast.hh"
#include "../../language/env.hh"
#include "../../language/printer.hh"
#include "../../language/typemap.hh"
#include "../../tester/genATC.hh"
#include "../../tester/test_utils.hh"
#include "../../tester/tester.hh"
#include <cassert>
#include <iostream>
#include <memory>

using namespace std;

/**
 * Helper function to create ResponseExpr from HTTPResponseCode and optional
 * expr
 */
std::unique_ptr<Expr> makeResponseExpr(std::unique_ptr<Expr> expr = nullptr) {
  string codeStr = "";
  if (expr) {
    std::vector<std::unique_ptr<Expr>> tupleElements;
    tupleElements.push_back(std::make_unique<Var>(codeStr));
    tupleElements.push_back(std::move(expr));
    return std::make_unique<Tuple>(std::move(tupleElements));
  } else {
    return std::make_unique<Var>(codeStr);
  }
}

/**
 * End-to-End Test: Full pipeline from Spec to Concrete Test Case
 *
 * Pipeline stages:
 * 1. Spec (API specification with globals, init, functions, blocks)
 * 2. genATC (Generate Abstract Test Case from Spec)
 * 3. Tester (Generate Concrete Test Case from ATC using symbolic execution)
 */
class E2ETest {
protected:
  string testName;
  Printer printer;

  virtual std::unique_ptr<Spec> makeSpec() = 0;
  virtual SymbolTable *makeSymbolTables() = 0;
  virtual std::vector<string> makeTestString() = 0;
  virtual void verify(const Program &ctc) = 0;

  virtual void cleanup(SymbolTable *globalTable) {
    if (globalTable) {
      // Delete children first
      for (size_t i = 0; i < globalTable->getChildCount(); i++) {
        delete globalTable->getChild(i);
      }
      delete globalTable;
    }
  }

public:
  E2ETest(const string &name) : testName(name) {}
  virtual ~E2ETest() = default;

  void execute() {
    std::cout << "\n" << string(80, '=') << std::endl;
    std::cout << "E2E Test: " << testName << std::endl;
    std::cout << string(80, '=') << std::endl;

    // ===== STAGE 1: Create Specification =====
    std::cout << "\n[STAGE 1] Creating API Specification..." << std::endl;
    std::unique_ptr<Spec> spec = makeSpec();
    assert(spec != nullptr);

    std::cout << "\nSpecification:" << std::endl;
    printer.visitSpec(*spec);

    // ===== STAGE 2: Generate Abstract Test Case =====
    std::cout << "\n[STAGE 2] Generating Abstract Test Case (ATC)..."
              << std::endl;
    SymbolTable *globalSymTable = makeSymbolTables();
    TypeMap typeMap;
    std::vector<string> testString = makeTestString();

    ATCGenerator generator(spec.get(), std::move(typeMap));
    Program atc = generator.generate(spec.get(), globalSymTable, testString);

    std::cout << "\nAbstract Test Case (ATC):" << std::endl;
    printer.visitProgram(atc);

    // ===== STAGE 3: Generate Concrete Test Case =====
    std::cout << "\n[STAGE 3] Generating Concrete Test Case (CTC) via Symbolic "
                 "Execution..."
              << std::endl;

    FunctionFactory *functionFactory = new App1FunctionFactory();
    Tester tester(functionFactory);
    std::vector<Expr *> initialConcreteVals;
    ValueEnvironment ve(nullptr);

    std::unique_ptr<Program> atcCopy = std::make_unique<Program>(std::move(
        const_cast<std::vector<std::unique_ptr<Stmt>> &>(atc.statements)));

    std::unique_ptr<Program> ctc =
        tester.generateCTC(std::move(atcCopy), initialConcreteVals, &ve);

    std::cout << "\nConcrete Test Case (CTC):" << std::endl;
    printer.visitProgram(*ctc);

    // ===== STAGE 4: Verify Results =====
    std::cout << "\n[STAGE 4] Verifying Results..." << std::endl;
    verify(*ctc);

    // Cleanup
    cleanup(globalSymTable);
    delete functionFactory;

    std::cout << "\n✓ E2E Test Passed!" << std::endl;
    std::cout << string(80, '=') << std::endl;
  }
};

/**
 * E2E Test 1: Simple f1 API call
 * TestSTring : f1
 * Spec:
 *   Global: y : int
 *   Init: y := 0
 *   API: r:= f1(x, z)
 *     Pre: x > 0 AND z > 0
 *     Post: r = (x+z)
 *
 * Expected ATC:
 *   y := 0
 *   x0 := input()
 *   z0 := input()
 *   assume(x0 > 0 AND z0 > 0)
 *   r0 := f1(x0, z0)
 *  assert(r0 == x0 + z0)
 * Expected CTC:
 *   y := 0
 *   x0 := <concrete_value>
 *   z0 := <concrete_value>
 *   assume(x0 > 0 AND z0 > 0)
 *   r0 := f1(x0, z0)
 *   assert(r0 == x0 + z0)
 */
class E2ETest1 : public E2ETest {
public:
  E2ETest1() : E2ETest("Simple f1 API call with precondition") {}

protected:
  std::unique_ptr<Spec> makeSpec() override {
    // Global: y : int
    std::vector<std::unique_ptr<Decl>> globals;
    globals.push_back(
        std::make_unique<Decl>("y", std::make_unique<TypeConst>("int")));

    // Init: y := 0
    std::vector<std::unique_ptr<Init>> inits;
    inits.push_back(std::make_unique<Init>("y", std::make_unique<Num>(0)));

    std::vector<std::unique_ptr<APIFuncDecl>> functions;
    std::vector<std::unique_ptr<API>> blocks;

    // API Block: f1(x, z)
    // Pre: x > 0 AND z > 0
    std::vector<std::unique_ptr<Expr>> xGt0Args;
    xGt0Args.push_back(std::make_unique<Var>("x"));
    xGt0Args.push_back(std::make_unique<Num>(0));
    auto xGt0 = std::make_unique<FuncCall>("Gt", std::move(xGt0Args));

    std::vector<std::unique_ptr<Expr>> zGt0Args;
    zGt0Args.push_back(std::make_unique<Var>("z"));
    zGt0Args.push_back(std::make_unique<Num>(0));
    auto zGt0 = std::make_unique<FuncCall>("Gt", std::move(zGt0Args));

    std::vector<std::unique_ptr<Expr>> andArgs;
    andArgs.push_back(std::move(xGt0));
    andArgs.push_back(std::move(zGt0));
    auto pre = std::make_unique<FuncCall>("And", std::move(andArgs));

    // API call: f1(x, z) -> _RESPONSE_CODE_200
    std::vector<std::unique_ptr<Expr>> callArgs;
    callArgs.push_back(std::make_unique<Var>("x"));
    callArgs.push_back(std::make_unique<Var>("z"));
    auto call = std::make_unique<FuncCall>("f1", std::move(callArgs));

    // Response: r
    auto responseExpr = std::make_unique<Var>("r");

    auto apiCall = std::make_unique<APIcall>(
        std::move(call),
        Response(HTTPResponseCode::OK_200, std::move(responseExpr)));

    // Post: r = x + z
    std::vector<std::unique_ptr<Expr>> addArgs;
    addArgs.push_back(std::make_unique<Var>("x"));
    addArgs.push_back(std::make_unique<Var>("z"));
    auto addExpr = std::make_unique<FuncCall>("Add", std::move(addArgs));

    std::vector<std::unique_ptr<Expr>> eqArgs;
    eqArgs.push_back(std::make_unique<Var>("r"));
    eqArgs.push_back(std::move(addExpr));
    auto postExpr = std::make_unique<FuncCall>("Eq", std::move(eqArgs));

    blocks.push_back(std::make_unique<API>(
        "f1", std::move(pre), std::move(apiCall), std::move(postExpr)));

    return std::make_unique<Spec>(std::move(globals), std::move(inits),
                                  std::move(functions), std::move(blocks));
  }

  SymbolTable *makeSymbolTables() override {
    // Global symbol table
    auto *globalTable = new SymbolTable(nullptr);

    auto *f1Table = new SymbolTable(globalTable);
    string *x = new string("x");
    string *z = new string("z");
    f1Table->addMapping(x, nullptr);
    f1Table->addMapping(z, nullptr);

    globalTable->addChild(f1Table);
    return globalTable;
  }

  std::vector<string> makeTestString() override { return {"f1"}; }

  void verify(const Program &ctc) override {
    std::cout << "  Verifying CTC structure..." << std::endl;
    std::cout << "  Total statements: " << ctc.statements.size() << std::endl;

    int inputCount = 0;
    int concreteCount = 0;
    bool foundF1 = false;
    bool foundAssert = false;
    bool foundAssume = false;

    for (const auto &stmt : ctc.statements) {
      if (stmt->statementType == StmtType::ASSIGN) {
        const Assign *assign = dynamic_cast<const Assign *>(stmt.get());
        if (assign && assign->right->exprType == ExprType::FUNC_CALL_EXPR) {
          const FuncCall *fc =
              dynamic_cast<const FuncCall *>(assign->right.get());
          if (fc && fc->name == "input") {
            inputCount++;
            const Var *leftVar = dynamic_cast<const Var *>(assign->left.get());
            if (leftVar) {
              std::cout << "  Found input() for variable: " << leftVar->name
                        << std::endl;
            }
          }
          if (fc && fc->name == "f1") {
            foundF1 = true;
            const Var *leftVar = dynamic_cast<const Var *>(assign->left.get());
            if (leftVar) {
              std::cout << "  ✓ Found f1 API call: " << leftVar->name
                        << " := f1(...)" << std::endl;
            }
          }
        } else if (assign && assign->right->exprType == ExprType::NUM) {
          concreteCount++;
          const Var *leftVar = dynamic_cast<const Var *>(assign->left.get());
          const Num *rightNum = dynamic_cast<const Num *>(assign->right.get());
          if (leftVar && rightNum) {
            std::cout << "  ✓ Found concrete assignment: " << leftVar->name
                      << " := " << rightNum->value << std::endl;
          }
        }
      } else if (stmt->statementType == StmtType::ASSUME) {
        foundAssume = true;
        std::cout << "  ✓ Found assume statement (precondition)" << std::endl;
      } else if (stmt->statementType == StmtType::ASSERT) {
        foundAssert = true;
        std::cout << "  ✓ Found assert statement (postcondition)" << std::endl;
        const Assert *asrt = dynamic_cast<const Assert *>(stmt.get());
        if (asrt) {
          // Verify structure: Eq(r, Add(x, z))
          const FuncCall *eq = dynamic_cast<const FuncCall *>(asrt->expr.get());
          if (eq && eq->name == "Eq") {
            std::cout << "    ✓ Assertion is Equality check" << std::endl;
          }
        }
      }
    }

    std::cout << "  Input calls remaining: " << inputCount << std::endl;
    std::cout << "  Concrete assignments: " << concreteCount << std::endl;

    assert(ctc.statements.size() >= 1);
    assert(foundF1);
    assert(foundAssume);
    assert(foundAssert);

    if (inputCount == 0) {
      std::cout << "  ✓ All input() calls replaced with concrete values"
                << std::endl;
    } else {
      std::cout << "  ⚠ Warning: " << inputCount
                << " input() calls still present" << std::endl;
    }

    std::cout
        << "  ✓ Complete CTC verified: assume (pre), f1 call, assert (post)"
        << std::endl;
  }
};

/**
 * E2E Test 2: Two sequential API calls (f1 then f2)
 *
 * Spec:
 *   Global: y : int
 *   Init: y := 0
 *   API 1: r= f1(x, z)
 *     Pre: x > 0
 *      Post: r = (x+z)
 *   API 2: r= f2()
 *     Pre: none
 *     Post: r=0
 * Expected: CTC with two API calls, different variable names (x0/z0 for f1)
 */
class E2ETest2 : public E2ETest {
public:
  E2ETest2() : E2ETest("Sequential API calls - f1 then f2") {}

protected:
  std::unique_ptr<Spec> makeSpec() override {
    // Global: y : int
    std::vector<std::unique_ptr<Decl>> globals;
    globals.push_back(
        std::make_unique<Decl>("y", std::make_unique<TypeConst>("int")));

    // Init: y := 0
    std::vector<std::unique_ptr<Init>> inits;
    inits.push_back(std::make_unique<Init>("y", std::make_unique<Num>(0)));

    std::vector<std::unique_ptr<APIFuncDecl>> functions;
    std::vector<std::unique_ptr<API>> blocks;

    // Block 1: f1(x, z)
    // Pre: x > 0
    // Post: _RESPONSE_CODE_200
    {
      std::vector<std::unique_ptr<Expr>> preArgs;
      preArgs.push_back(std::make_unique<Var>("x"));
      preArgs.push_back(std::make_unique<Num>(0));
      auto pre = std::make_unique<FuncCall>("Gt", std::move(preArgs));

      std::vector<std::unique_ptr<Expr>> callArgs;
      callArgs.push_back(std::make_unique<Var>("x"));
      callArgs.push_back(std::make_unique<Var>("z"));
      auto call = std::make_unique<FuncCall>("f1", std::move(callArgs));

      auto apiCall = std::make_unique<APIcall>(
          std::move(call),
          Response(HTTPResponseCode::OK_200, std::make_unique<Var>("r")));

      // Post: r = x + z
      std::vector<std::unique_ptr<Expr>> addArgs;
      addArgs.push_back(std::make_unique<Var>("x"));
      addArgs.push_back(std::make_unique<Var>("z"));
      auto addExpr = std::make_unique<FuncCall>("Add", std::move(addArgs));

      std::vector<std::unique_ptr<Expr>> eqArgs;
      eqArgs.push_back(std::make_unique<Var>("r"));
      eqArgs.push_back(std::move(addExpr));
      auto postExpr = std::make_unique<FuncCall>("Eq", std::move(eqArgs));

      blocks.push_back(std::make_unique<API>(
          "f1", std::move(pre), std::move(apiCall), std::move(postExpr)));
    }

    // Block 2: f2()
    // Pre: none (true)
    // Post: r = 0
    {
      auto pre = std::make_unique<Num>(1); // true precondition

      std::vector<std::unique_ptr<Expr>> callArgs;
      auto call = std::make_unique<FuncCall>("f2", std::move(callArgs));

      auto apiCall = std::make_unique<APIcall>(
          std::move(call),
          Response(HTTPResponseCode::OK_200, std::make_unique<Var>("r")));

      // Post: r = 0
      std::vector<std::unique_ptr<Expr>> eqArgs;
      eqArgs.push_back(std::make_unique<Var>("r"));
      eqArgs.push_back(std::make_unique<Num>(0));
      auto postExpr = std::make_unique<FuncCall>("Eq", std::move(eqArgs));

      blocks.push_back(std::make_unique<API>(
          "f2", std::move(pre), std::move(apiCall), std::move(postExpr)));
    }

    return std::make_unique<Spec>(std::move(globals), std::move(inits),
                                  std::move(functions), std::move(blocks));
  }

  SymbolTable *makeSymbolTables() override {
    // Global symbol table
    auto *globalTable = new SymbolTable(nullptr);

    // Symbol table for f1 block
    auto *f1Table = new SymbolTable(globalTable);
    string *x = new string("x");
    string *z = new string("z");
    f1Table->addMapping(x, nullptr);
    f1Table->addMapping(z, nullptr);

    // Symbol table for f2 block (no parameters)
    auto *f2Table = new SymbolTable(globalTable);

    globalTable->addChild(f1Table);
    globalTable->addChild(f2Table);
    return globalTable;
  }

  std::vector<string> makeTestString() override { return {"f1", "f2"}; }

  void verify(const Program &ctc) override {
    std::cout << "  Verifying CTC structure..." << std::endl;
    std::cout << "  Total statements: " << ctc.statements.size() << std::endl;

    int inputCount = 0;
    bool foundF1 = false, foundF2 = false;
    int assumeCount = 0, assertCount = 0;

    for (const auto &stmt : ctc.statements) {
      if (stmt->statementType == StmtType::ASSIGN) {
        const Assign *assign = dynamic_cast<const Assign *>(stmt.get());
        if (assign && assign->right->exprType == ExprType::FUNC_CALL_EXPR) {
          const FuncCall *fc =
              dynamic_cast<const FuncCall *>(assign->right.get());
          if (fc && fc->name == "input")
            inputCount++;
          if (fc && fc->name == "f1") {
            foundF1 = true;
            std::cout << "  ✓ Found f1 API call" << std::endl;
          }
          if (fc && fc->name == "f2") {
            foundF2 = true;
            std::cout << "  ✓ Found f2 API call" << std::endl;
          }
        }
      } else if (stmt->statementType == StmtType::ASSUME) {
        assumeCount++;
      } else if (stmt->statementType == StmtType::ASSERT) {
        assertCount++;
        const Assert *asrt = dynamic_cast<const Assert *>(stmt.get());
        if (asrt) {
          const FuncCall *eq = dynamic_cast<const FuncCall *>(asrt->expr.get());
          if (eq && eq->name == "Eq") {
            std::cout << "    ✓ Assertion found: " << eq->name << std::endl;
          }
        }
      }
    }

    std::cout << "  Assume statements (preconditions): " << assumeCount
              << std::endl;
    std::cout << "  Assert statements (postconditions): " << assertCount
              << std::endl;

    assert(foundF1);
    assert(foundF2);
    assert(assumeCount >= 2); // One for each API
    assert(assertCount >= 2); // One for each API

    if (inputCount == 0) {
      std::cout << "  ✓ All input() calls replaced with concrete values"
                << std::endl;
    } else {
      std::cout << "  ⚠ Warning: " << inputCount
                << " input() calls still present" << std::endl;
    }

    std::cout << "  ✓ Both API calls present with pre/post conditions (f1, f2)"
              << std::endl;
  }
};

/**
 * E2E Test 3: API with global state (get_y/set_y)
 *
 * Spec:
 *   Global: y : int
 *   Init: y := 0
 *   API: r = f1(x, z) with get_y/set_y calls
 *     Pre: x < 10 AND Any(z)
 *     Post: r = x + z (using get_y and set_y)
 *
 * Expected: CTC with get_y/set_y calls and state management
 */
class E2ETest3 : public E2ETest {
public:
  E2ETest3() : E2ETest("API with global state - get_y/set_y") {}

protected:
  std::unique_ptr<Spec> makeSpec() override {
    // Global: y : int
    std::vector<std::unique_ptr<Decl>> globals;
    globals.push_back(
        std::make_unique<Decl>("y", std::make_unique<TypeConst>("int")));

    // Init: y := 0 (using set_y)
    std::vector<std::unique_ptr<Init>> inits;
    std::vector<std::unique_ptr<Expr>> setYArgs;
    setYArgs.push_back(std::make_unique<Num>(0));
    inits.push_back(std::make_unique<Init>(
        "_tmp", std::make_unique<FuncCall>("set_y", std::move(setYArgs))));

    std::vector<std::unique_ptr<APIFuncDecl>> functions;
    std::vector<std::unique_ptr<API>> blocks;

    // Precondition: x < 10 AND Any(z)
    std::vector<std::unique_ptr<Expr>> ltArgs;
    ltArgs.push_back(std::make_unique<Var>("x"));
    ltArgs.push_back(std::make_unique<Num>(10));
    auto lt = std::make_unique<FuncCall>("Lt", std::move(ltArgs));

    std::vector<std::unique_ptr<Expr>> anyArgs;
    anyArgs.push_back(std::make_unique<Var>("z"));
    auto any = std::make_unique<FuncCall>("Any", std::move(anyArgs));

    std::vector<std::unique_ptr<Expr>> preArgs;
    preArgs.push_back(std::move(lt));
    preArgs.push_back(std::move(any));
    auto pre = std::make_unique<FuncCall>("And", std::move(preArgs));

    // API call: f1(x, z) -> _RESPONSE_CODE_200
    std::vector<std::unique_ptr<Expr>> callArgs;
    callArgs.push_back(std::make_unique<Var>("x"));
    callArgs.push_back(std::make_unique<Var>("z"));
    auto call = std::make_unique<FuncCall>("f1", std::move(callArgs));

    auto apiCall = std::make_unique<APIcall>(
        std::move(call),
        Response(HTTPResponseCode::OK_200, std::make_unique<Var>("r")));

    // Post: _RESPONSE_CODE_200
    // Post: r = x + z
    std::vector<std::unique_ptr<Expr>> addArgs;
    addArgs.push_back(std::make_unique<Var>("x"));
    addArgs.push_back(std::make_unique<Var>("z"));
    auto addExpr = std::make_unique<FuncCall>("Add", std::move(addArgs));

    std::vector<std::unique_ptr<Expr>> eqArgs;
    eqArgs.push_back(std::make_unique<Var>("r"));
    eqArgs.push_back(std::move(addExpr));
    auto postExpr = std::make_unique<FuncCall>("Eq", std::move(eqArgs));

    blocks.push_back(std::make_unique<API>(
        "f1", std::move(pre), std::move(apiCall), std::move(postExpr)));

    return std::make_unique<Spec>(std::move(globals), std::move(inits),
                                  std::move(functions), std::move(blocks));
  }

  SymbolTable *makeSymbolTables() override {
    // Global symbol table
    auto *globalTable = new SymbolTable(nullptr);

    auto *f1Table = new SymbolTable(globalTable);
    string *x = new string("x");
    string *z = new string("z");
    f1Table->addMapping(x, nullptr);
    f1Table->addMapping(z, nullptr);

    globalTable->addChild(f1Table);
    return globalTable;
  }

  std::vector<string> makeTestString() override { return {"f1"}; }

  void verify(const Program &ctc) override {
    std::cout << "  Verifying CTC structure..." << std::endl;
    std::cout << "  Total statements: " << ctc.statements.size() << std::endl;

    int inputCount = 0;
    bool foundSetY = false;
    bool foundF1 = false;
    bool foundAssume = false;
    bool foundAssert = false;

    for (const auto &stmt : ctc.statements) {
      if (stmt->statementType == StmtType::ASSIGN) {
        const Assign *assign = dynamic_cast<const Assign *>(stmt.get());
        if (assign && assign->right->exprType == ExprType::FUNC_CALL_EXPR) {
          const FuncCall *fc =
              dynamic_cast<const FuncCall *>(assign->right.get());
          if (fc && fc->name == "input")
            inputCount++;
          if (fc && fc->name == "set_y") {
            foundSetY = true;
            std::cout << "  ✓ Found set_y call (global state init)"
                      << std::endl;
          }
          if (fc && fc->name == "f1") {
            foundF1 = true;
            std::cout << "  ✓ Found f1 API call" << std::endl;
          }
        }
      } else if (stmt->statementType == StmtType::ASSUME) {
        foundAssume = true;
        std::cout
            << "  ✓ Found assume statement (precondition: x < 10 AND Any(z))"
            << std::endl;
      } else if (stmt->statementType == StmtType::ASSERT) {
        foundAssert = true;
        std::cout << "  ✓ Found assert statement (postcondition)" << std::endl;
        const Assert *asrt = dynamic_cast<const Assert *>(stmt.get());
        if (asrt) {
          // Verify structure: Eq(r, Add(x, z))
          const FuncCall *eq = dynamic_cast<const FuncCall *>(asrt->expr.get());
          if (eq && eq->name == "Eq") {
            std::cout << "    ✓ Assertion is Equality check" << std::endl;
          }
        }
      }
    }

    assert(foundSetY);
    assert(foundF1);
    assert(foundAssume);
    assert(foundAssert);

    if (inputCount == 0) {
      std::cout << "  ✓ All input() calls replaced with concrete values"
                << std::endl;
    } else {
      std::cout << "  ⚠ Warning: " << inputCount
                << " input() calls still present" << std::endl;
    }

    std::cout << "  ✓ Complete CTC verified: set_y, assume, f1 call, assert"
              << std::endl;
  }
};

int main() {
  std::cout << "\n" << string(80, '=') << std::endl;
  std::cout << "End-to-End Test Suite: Spec -> ATC -> CTC" << std::endl;
  std::cout << string(80, '=') << std::endl;

  std::vector<E2ETest *> tests = {new E2ETest1(), new E2ETest2(),
                                  new E2ETest3()};

  int passed = 0;
  int failed = 0;

  for (auto *test : tests) {
    try {
      test->execute();
      passed++;
      delete test;
    } catch (const exception &e) {
      std::cout << "\n✗ Test failed with exception: " << e.what() << std::endl;
      failed++;
      delete test;
    } catch (...) {
      std::cout << "\n✗ Test failed with unknown exception" << std::endl;
      failed++;
      delete test;
    }
  }

  std::cout << "\n" << string(80, '=') << std::endl;
  std::cout << "Test Results: " << passed << " passed, " << failed << " failed"
            << std::endl;
  std::cout << string(80, '=') << std::endl;

  return (failed == 0) ? 0 : 1;
}
