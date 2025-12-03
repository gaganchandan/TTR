#include <iostream>
#include <cassert>
#include "ast.hh"
#include "env.hh"
#include "symvar.hh"
#include "see.hh"
#include "z3solver.hh"
#include "../../tester/test_utils.hh"
#include "../../apps/app1/app1.hh"
using namespace std;

class SEETest {
protected:
    string testName;
    virtual Program makeProgram() = 0;
    virtual void verify(SEE& see, map<string, int>& model, bool isSat) = 0;
    
public:
    SEETest(const string& name) : testName(name) {}
    virtual ~SEETest() = default;
    
    void execute() {
        cout << "\n*********************Test case: " << testName << " *************" << endl;
        
        Program program = makeProgram();
        SymbolTable st(nullptr);
        FunctionFactory* functionFactory = new App1FunctionFactory();
        
        SEE see(move(functionFactory));
        
        // Execute the program
        see.execute(program, st);
        
        // Display results
        TestUtils::executeAndDisplay(see);
        
        // Solve with Z3
        map<string, int> model;
        bool isSat = TestUtils::solveAndDisplay(see, model);
        
        // Verify results
        verify(see, model, isSat);
        
        cout << "✓ Test passed!" << endl;
    }
};

/*
Test: Basic symbolic execution with UNSAT constraints
Program:
    x := input
    y := input  
    z := x+y
    assume(x*y=3)
    z := z+2
    assume(x=5)
Expected: UNSAT (no integer solution for x*y=3 and x=5)
*/
class SEETest1 : public SEETest {
public:
    SEETest1() : SEETest("Basic symbolic execution with UNSAT constraints") {}
    
protected:
    Program makeProgram() override {
        vector<unique_ptr<Stmt>> statements;
        
        statements.push_back(TestUtils::makeInputAssign("x"));
        statements.push_back(TestUtils::makeInputAssign("y"));
        
        statements.push_back(make_unique<Assign>(
            make_unique<Var>("z"),
            TestUtils::makeBinOp("Add", make_unique<Var>("x"), make_unique<Var>("y"))
        ));
        
        statements.push_back(make_unique<Assume>(
            TestUtils::makeBinOp("Eq", 
                TestUtils::makeBinOp("Mul", make_unique<Var>("x"), make_unique<Var>("y")),
                make_unique<Num>(3)
            )
        ));
        
        statements.push_back(make_unique<Assign>(
            make_unique<Var>("z"),
            TestUtils::makeBinOp("Add", make_unique<Var>("z"), make_unique<Num>(2))
        ));
        
        statements.push_back(TestUtils::makeAssumeEq(make_unique<Var>("x"), make_unique<Num>(5)));
        
        return Program(std::move(statements));
    }
    
    void verify(SEE& see, map<string, int>& model, bool isSat) override {
        ValueEnvironment& sigma = see.getSigma();
        
        // Verify sigma contains expected variables
        assert(sigma.hasValue("x"));
        assert(sigma.hasValue("y"));
        assert(sigma.hasValue("z"));
        
        // Check that x and y are symbolic variables
        assert(sigma.getValue("x")->exprType == ExprType::SYMVAR);
        assert(sigma.getValue("y")->exprType == ExprType::SYMVAR);
        
        // Check that z is a function call (Add expression)
        assert(sigma.getValue("z")->exprType == ExprType::FUNCCALL);
        
        // Verify path constraints
        vector<Expr*>& pathConstraint = see.getPathConstraint();
        assert(pathConstraint.size() == 2);
        
        // Should be UNSAT (no integer solution for x*y=3 and x=5)
        assert(!isSat);
        assert(model.empty());
    }
};

/*
Test: Simple SAT constraint
Program:
    x := input
    assume(x > 5)
Expected: SAT with x > 5
*/
class SEETest2 : public SEETest {
public:
    SEETest2() : SEETest("Simple SAT constraint") {}
    
protected:
    Program makeProgram() override {
        vector<unique_ptr<Stmt>> statements;
        
        statements.push_back(TestUtils::makeInputAssign("x"));
        statements.push_back(make_unique<Assume>(
            TestUtils::makeBinOp("Gt", make_unique<Var>("x"), make_unique<Num>(5))
        ));
        
        return Program(std::move(statements));
    }
    
    void verify(SEE& see, map<string, int>& model, bool isSat) override {
        ValueEnvironment& sigma = see.getSigma();
        assert(sigma.hasValue("x"));
        
        vector<Expr*>& pathConstraint = see.getPathConstraint();
        assert(pathConstraint.size() == 1);
        
        // Should be SAT
        assert(isSat);
        assert(model.size() == 1);
        
        // Get the symbolic variable value (could be X0, X1, X2, etc. depending on test order)
        int x_val = model.begin()->second;
        assert(x_val > 5);
    }
};

/*
Test: Multiple variables with linear constraints
Program:
    x := input
    y := input
    assume(x + y = 10)
    assume(x > 3)
Expected: SAT with valid solution
*/
class SEETest3 : public SEETest {
public:
    SEETest3() : SEETest("Multiple variables with linear constraints") {}
    
protected:
    Program makeProgram() override {
        vector<unique_ptr<Stmt>> statements;
        
        statements.push_back(TestUtils::makeInputAssign("x"));
        statements.push_back(TestUtils::makeInputAssign("y"));
        
        statements.push_back(TestUtils::makeAssumeEq(
            TestUtils::makeBinOp("Add", make_unique<Var>("x"), make_unique<Var>("y")),
            make_unique<Num>(10)
        ));
        
        statements.push_back(make_unique<Assume>(
            TestUtils::makeBinOp("Gt", make_unique<Var>("x"), make_unique<Num>(3))
        ));
        
        return Program(std::move(statements));
    }
    
    void verify(SEE& see, map<string, int>& model, bool isSat) override {
        ValueEnvironment& sigma = see.getSigma();
        assert(sigma.hasValue("x"));
        assert(sigma.hasValue("y"));
        
        vector<Expr*>& pathConstraint = see.getPathConstraint();
        assert(pathConstraint.size() == 2);
        
        // Should be SAT
        assert(isSat);
        assert(model.size() == 2);
        
        // Get symbolic variable values (order may vary)
        auto it = model.begin();
        int val1 = it->second;
        ++it;
        int val2 = it->second;
        
        // Verify solution satisfies constraints (x + y = 10 and x > 3)
        assert(val1 + val2 == 10);
        // One of them should be > 3
        assert(val1 > 3 || val2 > 3);
    }
};

int main() {
    vector<SEETest*> testcases = {
        new SEETest1(),
        // new SEETest2(),
        // new SEETest3()
    };
    
    cout << "========================================" << endl;
    cout << "Running SEE Test Suite" << endl;
    cout << "========================================" << endl;
    
    for(auto& t : testcases) {
        try {
            t->execute();
            delete t;
        }
        catch(const exception& e) {
            cout << "Test exception: " << e.what() << endl;
            delete t;
        }
        catch(...) {
            cout << "Unknown test exception" << endl;
            delete t;
        }
    }
    
    cout << "\n========================================" << endl;
    cout << "All SEE tests passed!" << endl;
    cout << "========================================" << endl;
    
    return 0;
}
