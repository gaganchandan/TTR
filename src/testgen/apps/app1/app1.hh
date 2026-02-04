#pragma once
#include "../../see/functionfactory.hh"

using namespace std;
class F1 : public Function {
private:
  int a1;
  int a2;

public:
  virtual unique_ptr<Expr> execute();
  F1(vector<Expr *> as);
};

class F2 : public Function {
public:
  virtual unique_ptr<Expr> execute();
};

// Getter function for global variable y
class GetY : public Function {
private:
  int *globalY;

public:
  GetY(int *y) : globalY(y) {}
  virtual unique_ptr<Expr> execute();
};

// Setter function for global variable y
class SetY : public Function {
private:
  int *globalY;
  int value;

public:
  SetY(int *y, int val) : globalY(y), value(val) {}
  virtual unique_ptr<Expr> execute();
};

class App1FunctionFactory : public FunctionFactory {
private:
  int globalY; // Global state variable
public:
  App1FunctionFactory() : globalY(0) {}
  unique_ptr<Function> getFunction(string fname, vector<Expr *> args);
};
