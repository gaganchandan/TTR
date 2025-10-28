#pragma once
#include "functionfactory.hh"

using namespace std;
class F1 : public Function {
    private:
        int a1;
        int a2;
    public:
        virtual unique_ptr<Expr> execute();
        F1(vector<Expr*> as);
};

class F2 : public Function {
    public:
        virtual unique_ptr<Expr> execute();
};

class App1FunctionFactory : public FunctionFactory {
    public:
        unique_ptr<Function> getFunction(string fname, vector<Expr*> args);
};
