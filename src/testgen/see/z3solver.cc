#include "z3solver.hh"
#include "../language/symvar.hh"
#include <iostream>

Z3InputMaker::Z3InputMaker() {}

Z3InputMaker::~Z3InputMaker() {
    // Clean up allocated z3::expr pointers
    for (auto& entry : symVarMap) {
        delete entry.second;
    }
}

z3::expr Z3InputMaker::makeZ3Input(unique_ptr<Expr>& expr) {
    if (!expr) {
        throw runtime_error("Null expression in Z3 conversion");
    }
    
    // Handle SymVar specially since it's not part of the ExprVisitor interface
    if (expr->exprType == ExprType::SYMVAR) {
        SymVar* sv = dynamic_cast<SymVar*>(expr.get());
        unsigned int num = sv->getNum();
        
        // Check if we've already created a Z3 variable for this SymVar
        if (symVarMap.find(num) == symVarMap.end()) {
            string varName = "X" + to_string(num);
            z3::expr* z3Var = new z3::expr(ctx.int_const(varName.c_str()));
            symVarMap[num] = z3Var;
            variables.push_back(*z3Var);
        }
        
        return *symVarMap[num];
    }
    
    visit(expr.get());
    if (theStack.empty()) {
        throw runtime_error("Stack empty after visiting expression");
    }
    z3::expr result = theStack.top();
    theStack.pop();
    return result;
}

z3::expr Z3InputMaker::makeZ3Input(Expr* expr) {
    if (!expr) {
        throw runtime_error("Null expression in Z3 conversion");
    }
    
    // Handle SymVar specially since it's not part of the ExprVisitor interface
    if (expr->exprType == ExprType::SYMVAR) {
        SymVar* sv = dynamic_cast<SymVar*>(expr);
        unsigned int num = sv->getNum();
        
        // Check if we've already created a Z3 variable for this SymVar
        if (symVarMap.find(num) == symVarMap.end()) {
            string varName = "X" + to_string(num);
            z3::expr* z3Var = new z3::expr(ctx.int_const(varName.c_str()));
            symVarMap[num] = z3Var;
            variables.push_back(*z3Var);
        }
        
        return *symVarMap[num];
    }
    
    visit(expr);
    if (theStack.empty()) {
        throw runtime_error("Stack empty after visiting expression");
    }
    z3::expr result = theStack.top();
    theStack.pop();
    return result;
}

vector<z3::expr> Z3InputMaker::getVariables() {
    return variables;
}

void Z3InputMaker::visitVar(const Var &node) {
    z3::expr z3Var = ctx.int_const(node.name.c_str());
    variables.push_back(z3Var);
    theStack.push(z3Var);
}

void Z3InputMaker::visitNum(const Num &node) {
    theStack.push(ctx.int_val(node.value));
}

void Z3InputMaker::visitString(const String &node) {
    theStack.push(ctx.string_val(node.value));
}

void Z3InputMaker::visitFuncCall(const FuncCall &node) {
    // Helper lambda to convert an argument (handles SymVar specially)
    auto convertArg = [this](const unique_ptr<Expr>& arg) -> z3::expr {
        if (arg->exprType == ExprType::SYMVAR) {
            SymVar* sv = dynamic_cast<SymVar*>(arg.get());
            unsigned int num = sv->getNum();
            
            if (symVarMap.find(num) == symVarMap.end()) {
                string varName = "X" + to_string(num);
                z3::expr* z3Var = new z3::expr(ctx.int_const(varName.c_str()));
                symVarMap[num] = z3Var;
                variables.push_back(*z3Var);
            }
            
            return *symVarMap[num];
        } else {
            visit(arg.get());
            z3::expr result = theStack.top();
            theStack.pop();
            return result;
        }
    };
    
    if (node.name == "Add" && node.args.size() == 2) {
        z3::expr left = convertArg(node.args[0]);
        z3::expr right = convertArg(node.args[1]);
        theStack.push(left + right);
    }
    else if (node.name == "Mul" && node.args.size() == 2) {
        z3::expr left = convertArg(node.args[0]);
        z3::expr right = convertArg(node.args[1]);
        theStack.push(left * right);
    }
    else if (node.name == "Eq" && node.args.size() == 2) {
        z3::expr left = convertArg(node.args[0]);
        z3::expr right = convertArg(node.args[1]);
        theStack.push(left == right);
    }
    else if (node.name == "Sub" && node.args.size() == 2) {
        z3::expr left = convertArg(node.args[0]);
        z3::expr right = convertArg(node.args[1]);
        theStack.push(left - right);
    }
    else if (node.name == "Lt" && node.args.size() == 2) {
        z3::expr left = convertArg(node.args[0]);
        z3::expr right = convertArg(node.args[1]);
        theStack.push(left < right);
    }
    else if (node.name == "Gt" && node.args.size() == 2) {
        z3::expr left = convertArg(node.args[0]);
        z3::expr right = convertArg(node.args[1]);
        theStack.push(left > right);
    }
    else if (node.name == "And" && node.args.size() == 2) {
        z3::expr left = convertArg(node.args[0]);
        z3::expr right = convertArg(node.args[1]);
        theStack.push(left && right);
    }
    else if (node.name == "Or" && node.args.size() == 2) {
        z3::expr left = convertArg(node.args[0]);
        z3::expr right = convertArg(node.args[1]);
        theStack.push(left || right);
    }
    else if (node.name == "Not" && node.args.size() == 1) {
        z3::expr arg = convertArg(node.args[0]);
        theStack.push(!arg);
    }
    else {
        throw runtime_error("Unsupported function: " + node.name);
    }
}

void Z3InputMaker::visitSet(const Set &node) {
    throw runtime_error("Set expressions not yet supported in Z3 conversion");
}

void Z3InputMaker::visitMap(const Map &node) {
    throw runtime_error("Map expressions not yet supported in Z3 conversion");
}

void Z3InputMaker::visitTuple(const Tuple &node) {
    throw runtime_error("Tuple expressions not yet supported in Z3 conversion");
}

// Type expression visitors (not used for Z3 conversion)
void Z3InputMaker::visitFuncType(const FuncType &node) {
    throw runtime_error("FuncType not supported in Z3 conversion");
}

void Z3InputMaker::visitMapType(const MapType &node) {
    throw runtime_error("MapType not supported in Z3 conversion");
}

void Z3InputMaker::visitTupleType(const TupleType &node) {
    throw runtime_error("TupleType not supported in Z3 conversion");
}

void Z3InputMaker::visitSetType(const SetType &node) {
    throw runtime_error("SetType not supported in Z3 conversion");
}

// Declaration visitors (not used for Z3 conversion)
void Z3InputMaker::visitDecl(const Decl &node) {
    throw runtime_error("Decl not supported in Z3 conversion");
}

// API visitors (not used for Z3 conversion)
void Z3InputMaker::visitAPIcall(const APIcall &node) {
    throw runtime_error("APIcall not supported in Z3 conversion");
}

void Z3InputMaker::visitAPI(const API &node) {
    throw runtime_error("API not supported in Z3 conversion");
}

void Z3InputMaker::visitResponse(const Response &node) {
    throw runtime_error("Response not supported in Z3 conversion");
}

void Z3InputMaker::visitInit(const Init &node) {
    throw runtime_error("Init not supported in Z3 conversion");
}

void Z3InputMaker::visitSpec(const Spec &node) {
    throw runtime_error("Spec not supported in Z3 conversion");
}

// Statement visitors (not used for Z3 conversion)
void Z3InputMaker::visitAssign(const Assign &node) {
    throw runtime_error("Assign not supported in Z3 conversion");
}

void Z3InputMaker::visitAssume(const Assume &node) {
    throw runtime_error("Assume not supported in Z3 conversion");
}



void Z3InputMaker::visitProgram(const Program &node) {
    throw runtime_error("Program not supported in Z3 conversion");
}

Result Z3Solver::solve(unique_ptr<Expr> formula) const {
    Z3InputMaker inputMaker;
    
    // Convert the formula to Z3 format
    z3::expr z3Formula = inputMaker.makeZ3Input(formula);
    
    // Create solver and add the constraint
    z3::solver s(inputMaker.getContext());
    s.add(z3Formula);
    
    cout << "[Z3Solver] Checking satisfiability..." << endl;
    cout << "[Z3Solver] Formula: " << z3Formula << endl;
    
    if(s.check() == z3::sat) {
        cout << "[Z3Solver] SAT - Model found!" << endl;
        z3::model m = s.get_model();
        
        // Extract variable values from the model
        map<string, unique_ptr<ResultValue>> var_values;
        
        // Get all variables that were used
        vector<z3::expr> vars = inputMaker.getVariables();
        for (const auto& var : vars) {
            z3::expr val = m.eval(var, true);
            string varName = var.to_string();
            
            // Extract integer value
            if (val.is_numeral()) {
                int intVal;
                if (val.is_int() && Z3_get_numeral_int(inputMaker.getContext(), val, &intVal)) {
                    cout << "[Z3Solver] " << varName << " = " << intVal << endl;
                    var_values[varName] = make_unique<IntResultValue>(intVal);
                } else {
                    throw runtime_error("[Z3Solver] The type isn't defined yet !!!");
                }
            }
        }
        
        return Result(true, std::move(var_values));
    }
    else {
        cout << "[Z3Solver] UNSAT - No solution exists" << endl;
        return Result(false, map<string, unique_ptr<ResultValue>>());
    }
}
