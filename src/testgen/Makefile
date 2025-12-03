CC=g++
CCFLAGS= -g
BUILD=build
TEST=test
BIN=bin
INC=-I language
INC_SYM=-I see
LIB=-lz3

# Common object file dependencies
COMMON_OBJS=$(BUILD)/ast.o $(BUILD)/astvisitor.o $(BUILD)/env.o $(BUILD)/symvar.o $(BUILD)/clonevisitor.o 
SEE_OBJS=$(BUILD)/see.o $(BUILD)/z3solver.o $(BUILD)/solver.o
TEST_OBJS=$(BUILD)/test_utils.o
TESTER_OBJS=$(BUILD)/tester.o
APP_OBJS=$(BUILD)/app1.o
# All dependencies for tests
ALL_TEST_DEPS=$(TEST_OBJS) $(SEE_OBJS) $(COMMON_OBJS) $(APP_OBJS)
# --------------------------------------------------
#  Object build rules (only what is actually used)
# --------------------------------------------------
$(BUILD)/app1.o : apps/app1/app1.cc apps/app1/app1.hh language/ast.hh language/astvisitor.hh language/symvar.hh language/clonevisitor.hh
	$(CC) $(CCFLAGS) -c apps/app1/app1.cc -o $@ $(INC) $(INC_SYM) 


$(BUILD)/astvisitor.o : language/astvisitor.cc language/astvisitor.hh language/ast.hh
	$(CC) $(CCFLAGS) -c language/astvisitor.cc -o $@ $(INC)

$(BUILD)/ast.o : $(BUILD)/astvisitor.o language/ast.cc language/ast.hh language/astvisitor.hh
	$(CC) $(CCFLAGS) -c language/ast.cc -o $@ $(INC)

$(BUILD)/env.o : language/env.cc language/env.hh
	$(CC) $(CCFLAGS) -c language/env.cc -o $@ $(INC)

$(BUILD)/symvar.o : language/symvar.cc language/symvar.hh language/ast.hh language/astvisitor.hh
	$(CC) $(CCFLAGS) -c language/symvar.cc -o $@ $(INC)

$(BUILD)/clonevisitor.o : language/clonevisitor.cc language/clonevisitor.hh language/ast.hh language/astvisitor.hh language/symvar.hh
	$(CC) $(CCFLAGS) -c language/clonevisitor.cc -o $@ $(INC)

$(BUILD)/solver.o : see/solver.cc see/solver.hh language/ast.hh
	$(CC) $(CCFLAGS) -c see/solver.cc -o $@ $(INC) $(LIB)

$(BUILD)/see.o : see/see.cc see/see.hh language/ast.hh language/env.hh see/functionfactory.hh language/clonevisitor.hh
	$(CC) $(CCFLAGS) -c see/see.cc -o $@ $(INC)

$(BUILD)/z3solver.o : see/z3solver.cc see/z3solver.hh see/solver.hh language/ast.hh language/symvar.hh
	$(CC) $(CCFLAGS) -c see/z3solver.cc -o $@ $(INC) $(LIB)

$(BUILD)/tester.o : tester/tester.cc tester/tester.hh language/ast.hh language/clonevisitor.hh
	$(CC) $(CCFLAGS) -c tester/tester.cc -o $@ $(INC) $(LIB)

$(BUILD)/test_utils.o : tester/test_utils.cc tester/test_utils.hh see/see.hh see/z3solver.hh
	$(CC) $(CCFLAGS) -c tester/test_utils.cc -o $@ $(INC) $(LIB)


# --------------------------------------------------
#  TEST binaries
# --------------------------------------------------
test_see: $(ALL_TEST_DEPS) tester/test_utils.hh $(TEST)/test_see/test_see.cc
	$(CC) $(CCFLAGS) $(TEST)/test_see/test_see.cc \
        $(ALL_TEST_DEPS) \
        -o $(BIN)/test_see $(INC) $(INC_SYM) $(LIB)

test_z3solver: $(ALL_TEST_DEPS) tester/test_utils.hh $(TEST)/test_z3solver/test_z3solver.cc
	$(CC) $(CCFLAGS) $(TEST)/test_z3solver/test_z3solver.cc \
        $(ALL_TEST_DEPS) \
        -o $(BIN)/test_z3solver $(INC) $(INC_SYM) $(LIB)

test_tester: $(ALL_TEST_DEPS) $(TESTER_OBJS) tester/test_utils.hh $(TEST)/test_tester/test_tester.cc
	$(CC) $(CCFLAGS) $(TEST)/test_tester/test_tester.cc \
        $(ALL_TEST_DEPS) $(TESTER_OBJS) \
        -o $(BIN)/test_tester $(INC) $(INC_SYM) $(LIB)

# --------------------------------------------------
#  Test run rules
# --------------------------------------------------
run_test_see: test_see
	./$(BIN)/test_see

run_test_z3solver: test_z3solver
	./$(BIN)/test_z3solver

run_test_tester: test_tester
	./$(BIN)/test_tester

test: run_test_see run_test_z3solver run_test_tester

clean:
	rm -f $(BUILD)/*.o $(BIN)/test_see $(BIN)/test_z3solver $(BIN)/test_tester
