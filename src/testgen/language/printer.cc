#include "printer.hh"

Printer::Printer() : indentLevel(0) { updateIndent(); }

// Type Expression visitors
void Printer::visitTypeConst(const TypeConst &node) {
  std::cout << node.toString();
}

void Printer::visitFuncType(const FuncType &node) {
  std::cout << node.toString();
}

void Printer::visitMapType(const MapType &node) {
  std::cout << node.toString();
}

void Printer::visitTupleType(const TupleType &node) {
  std::cout << node.toString();
}

void Printer::visitSetType(const SetType &node) {
  std::cout << node.toString();
}

// Expression visitors
void Printer::visitVar(const Var &node) { std::cout << node.toString(); }

void Printer::visitFuncCall(const FuncCall &node) {
  std::cout << node.toString();
}

void Printer::visitNum(const Num &node) { std::cout << node.toString(); }

void Printer::visitString(const String &node) { std::cout << node.toString(); }

void Printer::visitBool(const Bool &node) { std::cout << node.toString(); }

void Printer::visitSet(const Set &node) { std::cout << node.toString(); }

void Printer::visitMap(const Map &node) { node.toString(); }

void Printer::visitTuple(const Tuple &node) { node.toString(); }

// Statement visitors
void Printer::visitAssign(const Assign &node) {
  visit(node.left.get());
  std::cout << " := ";
  visit(node.right.get());
}

void Printer::visitAssume(const Assume &node) {
  std::cout << "assume(";
  visit(node.expr.get());
  std::cout << ")";
}

// High-level visitors
void Printer::visitDecl(const Decl &node) {
  std::cout << node.name << ": ";
  visit(node.type.get());
}

void Printer::visitAPIcall(const APIcall &node) {
  visit(node.call.get());
  std::cout << " -> ";
  visitResponse(node.response);
}

void Printer::visitAPI(const API &node) {
  std::cout << "API {" << endl;
  indent();

  printIndent();
  std::cout << "pre: ";
  visit(node.pre.get());
  std::cout << endl;

  printIndent();
  std::cout << "call: ";
  visitAPIcall(*node.call);
  std::cout << endl;

  dedent();
  printIndent();
  std::cout << "}";
}

void Printer::visitResponse(const Response &node) {
  // Print HTTP response code
  // std::cout << "Response(";
  // switch (node.code) {
  //     case HTTPResponseCode::OK_200:
  //         std::cout << "200";
  //         break;
  //     case HTTPResponseCode::CREATED_201:
  //         std::cout << "201";
  //         break;
  //     case HTTPResponseCode::BAD_REQUEST_400:
  //         std::cout << "400";
  //         break;
  //     default:
  //         std::cout << "???";
  //         break;
  // }
  // Print expression if present
  if (node.expr) {
    std::cout << ", ";
    visit(node.expr.get());
  }
  std::cout << ")";
}

void Printer::visitInit(const Init &node) {
  std::cout << node.varName << " := ";
  visit(node.expr.get());
}

void Printer::visitSpec(const Spec &node) {
  std::cout << "=== Spec ===" << endl;

  std::cout << "Globals:" << endl;
  for (const auto &g : node.globals) {
    printIndent();
    visitDecl(*g);
    std::cout << endl;
  }

  std::cout << "Init:" << endl;
  for (const auto &i : node.init) {
    printIndent();
    visitInit(*i);
    std::cout << endl;
  }

  std::cout << "Blocks:" << endl;
  for (const auto &b : node.blocks) {
    visitAPI(*b);
    std::cout << endl;
  }

  std::cout << "=== End Spec ===" << endl;
}

void Printer::visitProgram(const Program &node) {
  std::cout << "=== Program ===" << endl;
  for (size_t i = 0; i < node.statements.size(); i++) {
    std::cout << "Statement " << i << ": ";
    printStmt(node.statements[i].get());
    std::cout << endl;
  }
  std::cout << "=== End Program ===" << endl;
}

// Convenience methods
void Printer::printExpr(const Expr *expr) {
  if (!expr) {
    std::cout << "null";
    return;
  }
  visit(expr);
}

void Printer::printStmt(const Stmt *stmt) {
  if (!stmt) {
    std::cout << "null";
    return;
  }

  // Check if it's an Assert (not in base visitor yet)
  // Assert uses ASSUME type but is a different class
  const Assert *assertStmt = dynamic_cast<const Assert *>(stmt);
  if (assertStmt) {
    std::cout << "assert(";
    if (assertStmt->expr) {
      visit(assertStmt->expr.get());
    }
    std::cout << ")";
    return;
  }

  // Try regular visitor dispatch
  try {
    visit(stmt);
  } catch (const std::runtime_error &e) {
    std::cout << "UnknownStmt";
  }
}

void Printer::printTypeExpr(const TypeExpr *type) {
  if (!type) {
    std::cout << "null";
    return;
  }
  visit(type);
}
