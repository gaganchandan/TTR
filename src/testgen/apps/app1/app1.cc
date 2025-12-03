#include "app1.hh"

F1::F1(vector<Expr*> as) {
    a1 = (dynamic_cast<Num*>(as[0]))->value;
    a2 = (dynamic_cast<Num*>(as[1]))->value;
}

unique_ptr<Expr> F1::execute() {
    cout << "Executing f1 ..." << endl;
    int s = a1 + a2;
    return make_unique<Num>(s);
}

unique_ptr<Expr> F2::execute() {
    cout << "Executing f2 ..." << endl;
    return make_unique<Num>(0);
}

unique_ptr<Expr> GetY::execute() {
    cout << "Executing get_y() -> " << *globalY << endl;
    return make_unique<Num>(*globalY);
}

unique_ptr<Expr> SetY::execute() {
    cout << "Executing set_y(" << value << ")" << endl;
    *globalY = value;
    return make_unique<Num>(value);
}

unique_ptr<Function> App1FunctionFactory::getFunction(string fname, vector<Expr*> args) {
    if(fname == "f1") {
        return make_unique<F1>(args);
    }
    else if(fname == "f2") {
        return make_unique<F2>();
    }
    else if(fname == "get_y") {
        return make_unique<GetY>(&globalY);
    }
    else if(fname == "set_y") {
        if(args.size() >= 1) {
            int val = (dynamic_cast<Num*>(args[0]))->value;
            return make_unique<SetY>(&globalY, val);
        }
        throw "set_y requires 1 argument!";
    }
    else {
        throw "Unknown function!";
    }
}
