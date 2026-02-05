#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

// ================================================================================
// Enumerations for AST nodes
// ================================================================================

enum class HTTPResponseCode {
  OK_200,
  CREATED_201,
  BAD_REQUEST_400,
};

enum class ExprType {
  NUM,
  STRING,
  BOOL,
  VAR,
  MAP,
  SET,
  TUPLE,
  // MAP_ACCESS,
  // MAP_UPDATE,
  FUNC_CALL_EXPR,
  // POLYMORPHIC_FUNC_CALL_EXPR,
  INPUT,
  SYMVAR,
  // EQUALS
};

enum class TypeExprType {
  TYPE_CONST,
  FUNC_TYPE,
  MAP_TYPE,
  SET_TYPE,
  TUPLE_TYPE
};

enum class StmtType {
  ASSIGN,
  // FUNC_CALL_STMT,
  DECL,
  ASSUME,
  ASSERT,
};

// ================================================================================
// Type Expressions
// ================================================================================

// --- Base class for Type Expressions ---
class TypeExpr {
public:
  TypeExprType typeExprType;

public:
  virtual ~TypeExpr() = default;
  virtual std::string toString() const = 0;
  virtual std::unique_ptr<TypeExpr> clone() = 0;
  virtual bool isEqual(const TypeExpr &other) const = 0;
  bool operator==(const TypeExpr &other) const;

protected:
  TypeExpr(TypeExprType);
};

// --- Atomic / Constant Types ---
class TypeConst : public TypeExpr {
public:
  const std::string name;

public:
  TypeConst(std::string name);
  virtual std::string toString() const;
  virtual std::unique_ptr<TypeExpr> clone();
  virtual bool isEqual(const TypeExpr &other) const;
};

// --- Function Types ---
class FuncType : public TypeExpr {
public:
  const std::vector<std::unique_ptr<TypeExpr>> params;
  const std::unique_ptr<TypeExpr> returnType;

public:
  FuncType(std::vector<std::unique_ptr<TypeExpr>>, std::unique_ptr<TypeExpr>);
  virtual std::string toString() const;
  virtual std::unique_ptr<TypeExpr> clone();
  virtual bool isEqual(const TypeExpr &other) const;
};

// --- Map Types ---
class MapType : public TypeExpr {
public:
  const std::unique_ptr<TypeExpr> domain;
  const std::unique_ptr<TypeExpr> range;

public:
  MapType(std::unique_ptr<TypeExpr>, std::unique_ptr<TypeExpr>);
  virtual std::string toString() const;
  virtual std::unique_ptr<TypeExpr> clone();
  virtual bool isEqual(const TypeExpr &other) const;
};

// --- Set Types ---
class SetType : public TypeExpr {
public:
  std::unique_ptr<TypeExpr> elementType;

public:
  explicit SetType(std::unique_ptr<TypeExpr>);
  virtual std::string toString() const;
  virtual std::unique_ptr<TypeExpr> clone();
  virtual bool isEqual(const TypeExpr &other) const;
};

// --- Tuple Types ---
class TupleType : public TypeExpr {
public:
  const std::vector<std::unique_ptr<TypeExpr>> elements;

public:
  explicit TupleType(std::vector<std::unique_ptr<TypeExpr>>);
  virtual std::string toString() const;
  virtual std::unique_ptr<TypeExpr> clone();
  virtual bool isEqual(const TypeExpr &other) const;
};

// ================================================================================
// Expressions (Expr hierarchy)
// ================================================================================

// --- Base class for Expressions ---
class Expr {
public:
  ExprType exprType;

protected:
  Expr(ExprType);

public:
  virtual ~Expr() = default;
  virtual std::string toString() const = 0;
  virtual std::unique_ptr<Expr> clone() = 0;
};

// --- Literals ---
class Bool : public Expr {
public:
  const bool value;

public:
  explicit Bool(bool);
  virtual std::string toString() const;
  virtual std::unique_ptr<Expr> clone();
};

class Num : public Expr {
public:
  const int value;

public:
  explicit Num(int);
  virtual std::string toString() const;
  virtual std::unique_ptr<Expr> clone();
};

class String : public Expr {
public:
  const std::string value;

public:
  explicit String(std::string);
  virtual std::string toString() const;
  virtual std::unique_ptr<Expr> clone();
};

// --- Variables and Input ---
class Var : public Expr {
public:
  std::string name;

public:
  explicit Var(std::string);
  bool operator<(const Var &v) const;
  virtual std::string toString() const;
  virtual std::unique_ptr<Expr> clone();
};

class Input : public Expr {
public:
  Input();
  virtual std::string toString() const;
  virtual std::unique_ptr<Expr> clone();
};

// --- Collections ---
// --- Set ---
class Set : public Expr {
public:
  const std::vector<std::unique_ptr<Expr>> elements;

public:
  explicit Set(std::vector<std::unique_ptr<Expr>>);
  virtual std::string toString() const;
  virtual std::unique_ptr<Expr> clone();
};

// --- Map ---
class Map : public Expr {
public:
  const std::vector<std::pair<std::unique_ptr<Var>, std::unique_ptr<Expr>>>
      value;

public:
  explicit Map(
      std::vector<std::pair<std::unique_ptr<Var>, std::unique_ptr<Expr>>>);
  virtual std::string toString() const;
  virtual std::unique_ptr<Expr> clone();
};

// class MapAccess : public Expr {
// public:
//   const std::unique_ptr<Var> mapName;
//   const std::unique_ptr<Expr> keyExpr;

// public:
//   MapAccess(std::unique_ptr<Var>, std::unique_ptr<Expr>);
//   virtual std::string toString() const;
//   virtual std::unique_ptr<Expr> clone();
// };

// class MapUpdate : public Expr {
// public:
//   const std::unique_ptr<Var> mapName;
//   const std::unique_ptr<Expr> keyExpr;
//   const std::unique_ptr<Expr> valueExpr;

// public:
//   MapUpdate(std::unique_ptr<Var>, std::unique_ptr<Expr>,
//   std::unique_ptr<Expr>); virtual std::string toString() const; virtual
//   std::unique_ptr<Expr> clone();
// };

// --- Tuples ---
class Tuple : public Expr {
public:
  const std::vector<std::unique_ptr<Expr>> exprs;

public:
  explicit Tuple(std::vector<std::unique_ptr<Expr>> exprs);
  virtual std::string toString() const;
  virtual std::unique_ptr<Expr> clone();
};

// --- Function Calls ---
class FuncCall : public Expr {
public:
  const std::string name;
  const std::vector<std::unique_ptr<Expr>> args;

public:
  FuncCall(std::string, std::vector<std::unique_ptr<Expr>>);
  virtual std::string toString() const;
  virtual std::unique_ptr<Expr> clone();
};

// --- Equality ---
// class Equals : public Expr {
// public:
//   const std::unique_ptr<Expr> left;
//   const std::unique_ptr<Expr> right;

// public:
//   Equals(std::unique_ptr<Expr>, std::unique_ptr<Expr>);
//   virtual std::string toString() const;
//   virtual std::unique_ptr<Expr> clone();
// };

// ================================================================================
// Declarations
// ================================================================================

class Decl {
public:
  std::string name;
  std::unique_ptr<TypeExpr> type;

public:
  Decl(std::string, std::unique_ptr<TypeExpr>);
  virtual ~Decl() = default;
  Decl(Decl &);
  virtual std::unique_ptr<Decl> clone();
};

// class FuncDecl {
// public:
//   const std::string name;
//   const std::vector<std::unique_ptr<TypeExpr>> params;
//   const std::unique_ptr<TypeExpr> returnType;

// public:
//   FuncDecl(std::string, std::vector<std::unique_ptr<TypeExpr>>,
//            std::unique_ptr<TypeExpr>);
//   virtual ~FuncDecl() = default;
//   FuncDecl(FuncDecl &);
//   virtual std::unique_ptr<FuncDecl> clone();
// };

class APIFuncDecl {
public:
  const std::string name;
  const std::vector<std::unique_ptr<TypeExpr>> params;
  const std::pair<HTTPResponseCode, std::unique_ptr<TypeExpr>> returnType;

public:
  APIFuncDecl(std::string, std::vector<std::unique_ptr<TypeExpr>>,
              std::pair<HTTPResponseCode, std::unique_ptr<TypeExpr>>);
  virtual ~APIFuncDecl() = default;
  APIFuncDecl(APIFuncDecl &);
  virtual std::unique_ptr<APIFuncDecl> clone();
};

// ================================================================================
// Nodes for Specification
// ================================================================================

class Init {
public:
  const std::string varName;
  const std::unique_ptr<Expr> expr;

public:
  Init(std::string, std::unique_ptr<Expr>);
};

class Response {
public:
  HTTPResponseCode code;
  std::unique_ptr<Expr> expr;

public:
  Response(HTTPResponseCode, std::unique_ptr<Expr>);
};

class APIcall {
public:
  const std::unique_ptr<FuncCall> call;
  const Response response;

public:
  APIcall(std::unique_ptr<FuncCall>, Response);
};

class API {
public:
  std::string name;
  std::unique_ptr<Expr> pre;
  std::unique_ptr<APIcall> call;
  std::unique_ptr<Expr> post;

public:
  API(std::string, std::unique_ptr<Expr>, std::unique_ptr<APIcall>,
      std::unique_ptr<Expr>);
};

// ================================================================================
// Statements
// ================================================================================

// --- Base class for Statements ---
class Stmt {
public:
  const StmtType statementType;

public:
  virtual ~Stmt() = default;
  virtual std::unique_ptr<Stmt> clone() = 0;

protected:
  Stmt(StmtType);
};

// --- Assignment Statement ---
class Assign : public Stmt {
public:
  const std::unique_ptr<Var> left;
  const std::unique_ptr<Expr> right;

public:
  Assign(std::unique_ptr<Var>, std::unique_ptr<Expr>);
  virtual std::unique_ptr<Stmt> clone();
};

// --- Function Call Statement ---
// class FuncCallStmt : public Stmt {
// public:
//   const std::unique_ptr<FuncCall> funcCall;

// public:
//   explicit FuncCallStmt(std::unique_ptr<FuncCall>);
//   virtual std::unique_ptr<Stmt> clone();
// };

// --- Assume statement ---
class Assume : public Stmt {
public:
  const std::unique_ptr<Expr> expr;

public:
  Assume(std::unique_ptr<Expr>);
  virtual std::unique_ptr<Stmt> clone();
};

// --- Assert statement ---
class Assert : public Stmt {
public:
  const std::unique_ptr<Expr> expr;

public:
  Assert(std::unique_ptr<Expr>);
  virtual std::unique_ptr<Stmt> clone();
};

// ================================================================================
// Top-level AST Nodes
// ================================================================================

class Spec {
public:
  const std::vector<std::unique_ptr<Decl>> globals;
  const std::vector<std::unique_ptr<Init>> init;
  const std::vector<std::unique_ptr<APIFuncDecl>> functions;
  const std::vector<std::unique_ptr<API>> blocks;

public:
  Spec(std::vector<std::unique_ptr<Decl>>, std::vector<std::unique_ptr<Init>>,
       std::vector<std::unique_ptr<APIFuncDecl>>,
       std::vector<std::unique_ptr<API>>);
};

class Program {
public:
  const std::vector<std::unique_ptr<Stmt>> statements;

public:
  explicit Program(std::vector<std::unique_ptr<Stmt>>);
};
