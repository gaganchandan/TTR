#include "typemap.hh"
#include "ast.hh"
#include <iostream>

TypeMap::TypeMap(TypeMap *p) : Env(p) {}

string TypeMap::keyToString(string *key) { return *key; }

void TypeMap::print() {
  std::cout << "TypeMap:" << std::endl;
  for (auto &d : table) {
    std::cout << "  " << d.first << " : " << d.second->toString();
    std::cout << std::endl;
  }
}

void TypeMap::setValue(const string &varName, TypeExpr *value) {
  // For value environment, we allow updating existing values (unlike
  // SymbolTable)
  table[varName] = value;
}

TypeExpr *TypeMap::getValue(const string &varName) {
  if (table.find(varName) != table.end()) {
    return table[varName];
  }
  if (parent != nullptr) {
    TypeMap *parentEnv = dynamic_cast<TypeMap *>(parent);
    if (parentEnv) {
      return parentEnv->getValue(varName);
    }
  }
  return nullptr;
}

bool TypeMap::hasValue(const string &varName) {
  if (table.find(varName) != table.end()) {
    return true;
  }
  if (parent != nullptr) {
    TypeMap *parentEnv = dynamic_cast<TypeMap *>(parent);
    if (parentEnv) {
      return parentEnv->hasValue(varName);
    }
  }
  return false;
}
