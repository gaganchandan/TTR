#include "app.hh"

F1::F1(vector<Expr*> as) {
    a1 = (dynamic_cast<Num*>(as[0]))->value;
    a2 = (dynamic_cast<Num*>(as[1]))->value;
}

unique_ptr<Expr> F1::execute() {
    cout << "Executing f1 ..." << endl;
    s = a1 + a2;
    return make_unique<Num>(s);
}

unique_ptr<Expr> F2::execute() {
    cout << "Executing f2 ..." << endl;
    return make_unique<Num>(0);
}

unique_ptr<Function> App1FunctionFactory::getFunction(string fname, vector<Expr*> args) {
    if(fname == "f1") {
        return make_unique<F1>(args);
    }
    else if(fname == "f2") {
            return make_unique<F2>();
    }
    else {
        throw "Unknown function!";
    }
}
