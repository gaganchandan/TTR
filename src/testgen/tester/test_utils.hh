#ifndef TEST_UTILS_HH
#define TEST_UTILS_HH

#include "../language/ast.hh"
#include "../language/env.hh"
#include "../see/see.hh"
#include "../see/z3solver.hh"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

/**
 * Base class for test utilities providing common helper functions
 * for symbolic execution and Z3 solver testing.
 */
class TestUtils {
public:
  // Helper function to print expressions recursively
  // static string exprToString(Expr *expr);

  // Helper function to create a binary operation function call (e.g., Add, Mul,
  // Eq)
  static unique_ptr<FuncCall> makeBinOp(string op, unique_ptr<Expr> left,
                                        unique_ptr<Expr> right);

  // Helper to create an input assignment: var := input
  static unique_ptr<Assign> makeInputAssign(const string &varName);

  // Helper to create an assume statement with a binary operation
  static unique_ptr<Assume> makeAssumeEq(unique_ptr<Expr> left,
                                         unique_ptr<Expr> right);

  // Helper to print sigma (value environment)
  static void printSigma(ValueEnvironment &sigma);

  // Helper to print path constraints
  static void printPathConstraints(vector<Expr *> &pathConstraint);

  // Helper to display execution results (call after see.execute)
  static void executeAndDisplay(SEE &see);

  // Helper to solve constraints and display results (returns isSat status)
  static bool solveAndDisplay(SEE &see, map<string, int> &modelOut);
};

#endif // TEST_UTILS_HH
