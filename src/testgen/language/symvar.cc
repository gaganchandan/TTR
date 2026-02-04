#include "symvar.hh"

unsigned int SymVar::count = 0;

SymVar::SymVar(unsigned int n) : Expr(ExprType::SYMVAR), num(n) {}

unique_ptr<SymVar> SymVar::getNewSymVar() {
  unique_ptr<SymVar> var = std::make_unique<SymVar>(count);
  count++;
  return var;
}

void SymVar::accept(Visitor &visitor) {}

bool SymVar::operator==(SymVar &var) { return num == var.num; }

std::string SymVar::toString() const { return "SymVar_" + std::to_string(num); }

std::unique_ptr<Expr> SymVar::clone() { return std::make_unique<SymVar>(num); }
