#include "ast.hh"
#include <sstream>

TypeExpr::TypeExpr(TypeExprType typeExprType) : typeExprType(typeExprType) {}

// --- Atomic / Constant Types ---
TypeConst::TypeConst(std::string n)
    : TypeExpr(TypeExprType::TYPE_CONST), name(n) {}

bool TypeExpr::operator==(const TypeExpr &other) const {
  if (this->typeExprType != other.typeExprType) {
    return false;
  }
  return this->isEqual(other);
}

std::string TypeConst::toString() const { return "TYPE_CONST{" + name + "}"; }

bool TypeConst::isEqual(const TypeExpr &other) const {
  if (other.typeExprType != TypeExprType::TYPE_CONST) {
    return false;
  }
  const TypeConst &otherConst = static_cast<const TypeConst &>(other);
  return name == otherConst.name;
}

std::unique_ptr<TypeExpr> TypeConst::clone() {
  return std::make_unique<TypeConst>(name);
}

// --- Function Types ---
FuncType::FuncType(std::vector<std::unique_ptr<TypeExpr>> params,
                   std::unique_ptr<TypeExpr> returnType)
    : TypeExpr(TypeExprType::FUNC_TYPE), params(std::move(params)),
      returnType(std::move(returnType)) {}

std::string FuncType::toString() const {
  std::ostringstream ss;
  for (size_t i = 0; i < params.size(); ++i) {
    ss << params[i]->toString();
    if (i < params.size() - 1) {
      ss << " -> ";
    }
  }
  return ss.str() + " -> " + returnType->toString();
}

bool FuncType::isEqual(const TypeExpr &other) const {
  if (other.typeExprType != TypeExprType::FUNC_TYPE) {
    return false;
  }
  const FuncType &otherFunc = static_cast<const FuncType &>(other);
  if (params.size() != otherFunc.params.size()) {
    return false;
  }
  for (size_t i = 0; i < params.size(); ++i) {
    if (!(*params[i] == *otherFunc.params[i])) {
      return false;
    }
  }
  return *returnType == *otherFunc.returnType;
}

std::unique_ptr<TypeExpr> FuncType::clone() {
  std::vector<std::unique_ptr<TypeExpr>> clonedParams;
  for (const auto &param : params) {
    clonedParams.push_back(param->clone());
  }
  return std::make_unique<FuncType>(std::move(clonedParams),
                                    returnType->clone());
}

// --- Map Types ---
MapType::MapType(std::unique_ptr<TypeExpr> domain,
                 std::unique_ptr<TypeExpr> range)
    : TypeExpr(TypeExprType::MAP_TYPE), domain(std::move(domain)),
      range(std::move(range)) {}

std::string MapType::toString() const {
  return "Map<" + domain->toString() + ", " + range->toString() + ">";
}

bool MapType::isEqual(const TypeExpr &other) const {
  if (other.typeExprType != TypeExprType::MAP_TYPE) {
    return false;
  }
  const MapType &otherMap = static_cast<const MapType &>(other);
  return (*domain == *otherMap.domain) && (*range == *otherMap.range);
}

std::unique_ptr<TypeExpr> MapType::clone() {
  return std::make_unique<MapType>(domain->clone(), range->clone());
}

// --- Tuple Types ---
TupleType::TupleType(std::vector<std::unique_ptr<TypeExpr>> elements)
    : TypeExpr(TypeExprType::TUPLE_TYPE), elements(std::move(elements)) {}

std::string TupleType::toString() const {
  std::ostringstream ss;
  ss << "Tuple<";
  for (size_t i = 0; i < elements.size(); ++i) {
    ss << elements[i]->toString();
    if (i < elements.size() - 1) {
      ss << ", ";
    }
  }
  ss << ">";
  return ss.str();
}

std::unique_ptr<TypeExpr> TupleType::clone() {
  std::vector<std::unique_ptr<TypeExpr>> clonedElements;
  for (const auto &elem : elements) {
    clonedElements.push_back(elem->clone());
  }
  return std::make_unique<TupleType>(std::move(clonedElements));
}

bool TupleType::isEqual(const TypeExpr &other) const {
  if (other.typeExprType != TypeExprType::TUPLE_TYPE) {
    return false;
  }
  const TupleType &otherTuple = static_cast<const TupleType &>(other);
  if (elements.size() != otherTuple.elements.size()) {
    return false;
  }
  for (size_t i = 0; i < elements.size(); ++i) {
    if (!(*elements[i] == *otherTuple.elements[i])) {
      return false;
    }
  }
  return true;
}

// --- Set Types ---
SetType::SetType(std::unique_ptr<TypeExpr> elementType)
    : TypeExpr(TypeExprType::SET_TYPE), elementType(std::move(elementType)) {}

std::string SetType::toString() const {
  return "Set<" + elementType->toString() + ">";
}

std::unique_ptr<TypeExpr> SetType::clone() {
  return std::make_unique<SetType>(elementType->clone());
}

bool SetType::isEqual(const TypeExpr &other) const {
  if (other.typeExprType != TypeExprType::SET_TYPE) {
    return false;
  }
  const SetType &otherSet = static_cast<const SetType &>(other);
  return *elementType == *otherSet.elementType;
}

Decl::Decl(std::string name, std::unique_ptr<TypeExpr> typeExpr)
    : name(std::move(name)), type(std::move(typeExpr)) {}

std::unique_ptr<Decl> Decl::clone() {
  return std::make_unique<Decl>(name, type->clone());
}

// ===============================================================================
// Expressions Implementation
// ===============================================================================

// --- Base class for Expressions ---
Expr::Expr(ExprType exprType) : exprType(exprType) {}

// --- Atomic / Constant Expressions ---
Bool::Bool(bool value) : Expr(ExprType::BOOL), value(value) {}

std::string Bool::toString() const { return value ? "true" : "false"; }

std::unique_ptr<Expr> Bool::clone() { return std::make_unique<Bool>(value); }

Num::Num(int value) : Expr(ExprType::NUM), value(value) {}

std::string Num::toString() const { return std::to_string(value); }

std::unique_ptr<Expr> Num::clone() { return std::make_unique<Num>(value); }

String::String(std::string value) : Expr(ExprType::STRING), value(value) {}

std::string String::toString() const { return "\"" + value + "\""; }

std::unique_ptr<Expr> String::clone() {
  return std::make_unique<String>(value);
}

// --- Variables and Input ---
Var::Var(std::string name) : Expr(ExprType::VAR), name(std::move(name)) {}

std::string Var::toString() const { return name; }

std::unique_ptr<Expr> Var::clone() { return std::make_unique<Var>(name); }

bool Var::operator<(const Var &v) const { return name < v.name; }

// Input::Input() : Expr(ExprType::INPUT) {}

// std::string Input::toString() const { return "input()"; }

// std::unique_ptr<Expr> Input::clone() { return std::make_unique<Input>(); }

// --- Collections ---
// --- Set ---
Set::Set(std::vector<std::unique_ptr<Expr>> elements)
    : Expr(ExprType::SET), elements(std::move(elements)) {}

std::string Set::toString() const {
  std::ostringstream ss;
  ss << "{";
  for (size_t i = 0; i < elements.size(); ++i) {
    ss << elements[i]->toString();
    if (i < elements.size() - 1) {
      ss << ", ";
    }
  }
  ss << "}";
  return ss.str();
};

std::unique_ptr<Expr> Set::clone() {
  std::vector<std::unique_ptr<Expr>> clonedElements;
  for (const auto &elem : elements) {
    clonedElements.push_back(elem->clone());
  }
  return std::make_unique<Set>(std::move(clonedElements));
}

// --- Map ---
Map::Map(std::vector<std::pair<std::unique_ptr<Var>, std::unique_ptr<Expr>>> v)
    : Expr(ExprType::MAP), value(std::move(v)) {}

std::string Map::toString() const {
  std::ostringstream ss;
  ss << "{";
  for (size_t i = 0; i < value.size(); ++i) {
    ss << value[i].first->toString() << ": " << value[i].second->toString();
    if (i < value.size() - 1) {
      ss << ", ";
    }
  }
  ss << "}";
  return ss.str();
}

std::unique_ptr<Expr> Map::clone() {
  std::vector<std::pair<std::unique_ptr<Var>, std::unique_ptr<Expr>>>
      clonedValue;
  for (const auto &pair : value) {
    clonedValue.push_back(std::make_pair(
        std::unique_ptr<Var>(static_cast<Var *>(pair.first->clone().release())),
        pair.second->clone()));
  }
  return std::make_unique<Map>(std::move(clonedValue));
}

// MapAccess::MapAccess(std::unique_ptr<Var> mapName,
//                      std::unique_ptr<Expr> keyExpr)
//     : Expr(ExprType::MAP_ACCESS), mapName(std::move(mapName)),
//       keyExpr(std::move(keyExpr)) {}

// std::string MapAccess::toString() const {
//   return mapName->toString() + "[" + keyExpr->toString() + "]";
// }

// std::unique_ptr<Expr> MapAccess::clone() {
//   return std::make_unique<MapAccess>(
//       std::unique_ptr<Var>(static_cast<Var *>(mapName->clone().release())),
//       keyExpr->clone());
// }

// MapUpdate::MapUpdate(std::unique_ptr<Var> mapName,
//                      std::unique_ptr<Expr> keyExpr,
//                      std::unique_ptr<Expr> valueExpr)
//     : Expr(ExprType::MAP_UPDATE), mapName(std::move(mapName)),
//       keyExpr(std::move(keyExpr)), valueExpr(std::move(valueExpr)) {}

// std::string MapUpdate::toString() const {
//   return mapName->toString() + "[" + keyExpr->toString() + "] -> " +
//          valueExpr->toString();
// }

// std::unique_ptr<Expr> MapUpdate::clone() {
//   return std::make_unique<MapUpdate>(
//       std::unique_ptr<Var>(static_cast<Var *>(mapName->clone().release())),
//       keyExpr->clone(), valueExpr->clone());
// }

// --- Tuple ---
Tuple::Tuple(std::vector<std::unique_ptr<Expr>> exprs)
    : Expr(ExprType::TUPLE), exprs(std::move(exprs)) {}

std::string Tuple::toString() const {
  std::ostringstream ss;
  ss << "(";
  for (size_t i = 0; i < exprs.size(); ++i) {
    ss << exprs[i]->toString();
    if (i < exprs.size() - 1) {
      ss << ", ";
    }
  }
  ss << ")";
  return ss.str();
};

std::unique_ptr<Expr> Tuple::clone() {
  std::vector<std::unique_ptr<Expr>> clonedExprs;
  for (const auto &expr : exprs) {
    clonedExprs.push_back(expr->clone());
  }
  return std::make_unique<Tuple>(std::move(clonedExprs));
}

// --- Function Calls ---
FuncCall::FuncCall(std::string name, std::vector<std::unique_ptr<Expr>> args)
    : Expr(ExprType::FUNC_CALL_EXPR), name(std::move(name)),
      args(std::move(args)) {}

std::string FuncCall::toString() const {
  std::ostringstream ss;
  ss << name << "(";
  for (size_t i = 0; i < args.size(); ++i) {
    ss << args[i]->toString();
    if (i < args.size() - 1) {
      ss << ", ";
    }
  }
  ss << ")";
  return ss.str();
}

std::unique_ptr<Expr> FuncCall::clone() {
  std::vector<std::unique_ptr<Expr>> clonedArgs;
  for (const auto &arg : args) {
    clonedArgs.push_back(arg->clone());
  }
  return std::make_unique<FuncCall>(name, std::move(clonedArgs));
}

// --- Equality ---
// Equals::Equals(std::unique_ptr<Expr> left, std::unique_ptr<Expr> right)
//     : Expr(ExprType::EQUALS), left(std::move(left)), right(std::move(right))
//     {}

// std::string Equals::toString() const {
//   return left->toString() + " == " + right->toString();
// }

// std::unique_ptr<Expr> Equals::clone() {
//   return std::make_unique<Equals>(left->clone(), right->clone());
// }

// ===============================================================================
// Declarations Implementation
// ===============================================================================
FuncDecl::FuncDecl(
    std::string name, std::vector<std::unique_ptr<TypeExpr>> params,
    std::pair<HTTPResponseCode, std::unique_ptr<TypeExpr>> returnType)
    : name(std::move(name)), params(std::move(params)),
      returnType(std::move(returnType)) {}

std::unique_ptr<FuncDecl> FuncDecl::clone() {
  std::vector<std::unique_ptr<TypeExpr>> clonedParams;
  for (const auto &param : params) {
    clonedParams.push_back(param->clone());
  }
  return std::make_unique<FuncDecl>(
      name, std::move(clonedParams),
      std::make_pair(returnType.first, returnType.second->clone()));
}

// ===============================================================================
// Nodes for Specification Implementation
// ===============================================================================
Init::Init(std::string varName, std::unique_ptr<Expr> expression)
    : varName(std::move(varName)), expr(std::move(expression)) {}

Response::Response(HTTPResponseCode code, std::unique_ptr<Expr> expression)
    : code(code), expr(std::move(expression)) {}

APIcall::APIcall(std::unique_ptr<FuncCall> Call, Response Response)
    : call(std::move(Call)), response(std::move(Response)) {}

API::API(std::string name, std::unique_ptr<Expr> precondition,
         std::unique_ptr<APIcall> functionCall,
         std::unique_ptr<Expr> postcondition)
    : pre(std::move(precondition)), call(std::move(functionCall)), name(name),
      post(std::move(postcondition)) {}

// ===============================================================================
// Statements Implementation
// ===============================================================================

Stmt::Stmt(StmtType type) : statementType(type) {}

Assign::Assign(std::unique_ptr<Var> left, std::unique_ptr<Expr> right)
    : Stmt(StmtType::ASSIGN), left(std::move(left)), right(std::move(right)) {}

std::unique_ptr<Stmt> Assign::clone() {
  return std::make_unique<Assign>(
      std::unique_ptr<Var>(static_cast<Var *>(left->clone().release())),
      std::unique_ptr<Expr>(right->clone().release()));
}

Assume::Assume(std::unique_ptr<Expr> e)
    : Stmt(StmtType::ASSUME), expr(std::move(e)) {}

std::unique_ptr<Stmt> Assume::clone() {
  return std::make_unique<Assume>(
      std::unique_ptr<Expr>(expr->clone().release()));
}

Assert::Assert(std::unique_ptr<Expr> e)
    : Stmt(StmtType::ASSERT), expr(std::move(e)) {}

std::unique_ptr<Stmt> Assert::clone() {
  return std::make_unique<Assert>(
      std::unique_ptr<Expr>(expr->clone().release()));
}

// ================================================================================
// Top-level AST Nodes Implementation
// ================================================================================
Spec::Spec(std::vector<std::unique_ptr<Decl>> globals,
           std::vector<std::unique_ptr<Init>> init,
           std::vector<std::unique_ptr<FuncDecl>> functions,
           std::vector<std::unique_ptr<API>> blocks)
    : globals(std::move(globals)), init(std::move(init)),
      functions(std::move(functions)), blocks(std::move(blocks)) {}

Program::Program(std::vector<std::unique_ptr<Stmt>> Statements)
    : statements(std::move(Statements)) {}
