#include "see.hh"

unique_ptr<Expr> computePathConstraint(vector<unique_ptr<Expr>> C) {
	return make_unique<Num>(0);
}

bool isReady(unique_ptr<Stmt> s) {
	return false;
}

bool isReady(unique_ptr<Expr> e) {
	return false;
}

bool isSymbolic(unique_ptr<Expr> e) {
	return false;
}

void SEE::execute() {}
