#include "see.hh"
#include "functionfactory.hh"

unique_ptr<Expr> SEE::computePathConstraint(vector<unique_ptr<Expr>> C) {
    return make_unique<Num>(0);
}

bool SEE::isReady(unique_ptr<Stmt> s, Env& env) {

    if(s.statementType == StmtType::ASSIGN) {
        unique_ptr<Assign> assign = FunctionFactory::dynamic_pointer_cast<Assign>(s);
        return isReady(assign.right);
    }
    else if(s.statementType == StmtType::FUNCCALL) {
        unique_ptr<FuncCallStmt> fcstmt = FunctionFactory::dynamic_pointer_cast<FuncCallStmt>(s);
        return isReady(fcstmt.call);
    }
    else {
    return false;
    }
}

bool SEE::isReady(unique_ptr<Expr> e, Env& env) {
    if(e.exprType == ExprType::FUNCCALL) {
        unique_ptr<FuncCall> fcstmt = FunctionFactory::dynamic_pointer_cast<FuncCallStmt>(s);
        for(unsigned int i = 0; i < fcstmt.args.size(); i++) {
            if(isReady(fcstmt.args[i]) == false) {
                return false;
            }
        }
        return true;
    }
    if(e.exprType == ExprType::MAP) {
        unique_ptr<Map> fcstmt = FunctionFactory::dynamic_pointer_cast<FuncCallStmt>(s);
    }
    if(e.exprType == ExprType::NUM) {
        return true;
    }
    if(e.exprType == ExprType::SET) {
        unique_ptr<Set> set = FunctionFactory::dynamic_pointer_cast<Set>(e);
        for(unsigned int i = 0; i < set.elements.size(); i++) {
            if(isReady(set.elements[i]) == false) {
                return false;
            }
        }
        return true;
    }
    if(e.exprType == ExprType::STRING) {
        return true;
    }
    if(e.exprType == ExprType::TUPLE) {
        unique_ptr<Tuple> tuple = FunctionFactory::dynamic_pointer_cast<Tuple>(e);
        for(unsigned int i = 0; i < tuple.exprs.size(); i++) {
            if(isReady(tuple.exprs[i]) == false) {
                return false;
            }
        }
        return true;
    }
    if(e.exprType == ExprType::VAR) {
        Expr& val = env.get(e);
        if(val.exprType == ExprType::SYMVAR) {
            return false;
        }
        else {
            return true;
        }
    }
    else {
        return false;
    }
}

bool SEE::isSymbolic(unique_ptr<Expr> e) {
    return false;
}

void SEE::execute() {}
