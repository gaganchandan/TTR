#ifndef Z3SOLVER_HH
#define Z3SOLVER_HH

#include<memory>
#include <stack>
#include<string>

#include "solver.hh"
#include "z3++.h"
#include "../language/astvisitor.hh"

using namespace std;

class Z3InputMaker : public ASTVisitor {
    private:
        z3::context ctx;
        stack<z3::expr> theStack;
        vector<z3::expr> variables;
        map<unsigned int, z3::expr*> symVarMap; // Map SymVar numbers to Z3 variables

    public:
        Z3InputMaker();
        ~Z3InputMaker();
        z3::expr makeZ3Input(unique_ptr<Expr>& expr);
        z3::expr makeZ3Input(Expr* expr);
	    vector<z3::expr> getVariables();
        z3::context& getContext() { return ctx; }

    protected:
        // Expression visitor methods (protected, called by base class)
        void visitVar(const Var &node) override;
        void visitFuncCall(const FuncCall &node) override;
        void visitNum(const Num &node) override;
        void visitString(const String &node) override;
        void visitSet(const Set &node) override;
        void visitMap(const Map &node) override;
        void visitTuple(const Tuple &node) override;

        // Type expression visitor methods
        void visitFuncType(const FuncType &node) override;
        void visitMapType(const MapType &node) override;
        void visitTupleType(const TupleType &node) override;
        void visitSetType(const SetType &node) override;

        // Statement visitor methods
        void visitAssign(const Assign &node) override;
        void visitAssume(const Assume &node) override;

    public:
        // High-level visitor methods
        void visitDecl(const Decl &node) override;
        void visitAPIcall(const APIcall &node) override;
        void visitAPI(const API &node) override;
        void visitResponse(const Response &node) override;
        void visitInit(const Init &node) override;
        void visitSpec(const Spec &node) override;
        void visitProgram(const Program &node) override;
};

class Z3Solver : public Solver {
    public:
        Result solve(unique_ptr<Expr>) const;
};
#endif
