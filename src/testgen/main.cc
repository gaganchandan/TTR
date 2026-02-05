#include "apps/app1/app1.hh"
#include "language/ast.hh"
#include "language/env.hh"
#include "language/printer.hh"
#include "language/typemap.hh"
#include "tester/genATC.hh"
#include "tester/test_utils.hh"
#include "tester/tester.hh"
#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>

extern int yyparse();
extern Spec *astRoot;
extern FILE *yyin;

class TestGen {

protected:
  string fileName;
  Printer printer;

  std::unique_ptr<Spec> makeSpec() {
    if (yyparse() != 0) {
      throw std::runtime_error("Parsing failed");
      return nullptr;
    }
    std::cout << "✓ Spec parsed successfully" << std::endl;
    if (astRoot == nullptr) {
      throw std::runtime_error("No spec generated");
      return nullptr;
    }
    return std::unique_ptr<Spec>(astRoot);
  }

  SymbolTable *makeSymbolTables(Spec *spec) {
    // Create global symbol table
    auto *globalTable = new SymbolTable(nullptr);

    // Create symbol tables for each API block
    for (const auto &block : spec->blocks) {
      auto *blockTable = new SymbolTable(globalTable);
      // Add parameters to block symbol table
      if (block->call) {
        const FuncCall *fc =
            dynamic_cast<const FuncCall *>(block->call->call.get());
        if (fc) {
          for (const auto &arg : fc->args) {
            const Var *varArg = dynamic_cast<const Var *>(arg.get());
            if (varArg) {
              string *varName = new string(varArg->name);
              blockTable->addMapping(varName, nullptr);
            }
          }
        }
      }
      globalTable->addChild(blockTable);
    }
    return globalTable;
  }

  std::vector<string> makeTestString(Spec *spec) {
    std::vector<string> testString;
    for (const auto &block : spec->blocks) {
      if (block->call) {
        const FuncCall *fc =
            dynamic_cast<const FuncCall *>(block->call->call.get());
        if (fc) {
          testString.push_back(fc->name);
        }
      }
    }
    return testString;
  }

  void cleanup(SymbolTable *globalTable) {
    if (globalTable) {
      // Delete children first
      for (size_t i = 0; i < globalTable->getChildCount(); i++) {
        delete globalTable->getChild(i);
      }
      delete globalTable;
    }
  }

public:
  TestGen(const string &name) : fileName(name) {}
  ~TestGen() = default;

  void execute() {
    std::cout << "\n" << string(80, '=') << std::endl;
    std::cout << "E2E Test: " << fileName << std::endl;
    std::cout << string(80, '=') << std::endl;

    // ===== STAGE 1: Create Specification =====
    std::cout << "\n[STAGE 1] Creating API Specification..." << std::endl;
    yyin = fopen(fileName.c_str(), "r");
    if (!yyin) {
      throw std::runtime_error("Failed to open spec file: " + fileName);
    }
    std::cout << "Parsing spec file: " << fileName << std::endl;
    std::unique_ptr<Spec> spec = makeSpec();
    assert(spec != nullptr);

    std::cout << "\nSpecification:" << std::endl;
    printer.visitSpec(*spec);

    // ===== STAGE 2: Generate Abstract Test Case =====
    std::cout << "\n[STAGE 2] Generating Abstract Test Case (ATC)..."
              << std::endl;
    SymbolTable *globalSymTable = makeSymbolTables(spec.get());
    TypeMap typeMap;
    std::vector<string> testString = makeTestString(spec.get());
    std::cout << "Test String: ";
    for (const auto &s : testString) {
      std::cout << s << " ";
    }
    ATCGenerator generator(spec.get(), std::move(typeMap));
    Program atc = generator.generate(spec.get(), globalSymTable, testString);

    std::cout << "\nAbstract Test Case (ATC):" << std::endl;
    printer.visitProgram(atc);

    // ===== STAGE 3: Generate Concrete Test Case =====
    std::cout << "\n[STAGE 3] Generating Concrete Test Case (CTC) via Symbolic "
                 "Execution..."
              << std::endl;

    FunctionFactory *functionFactory = new App1FunctionFactory();
    Tester tester(functionFactory);
    std::vector<Expr *> initialConcreteVals;
    ValueEnvironment ve(nullptr);

    std::unique_ptr<Program> atcCopy = std::make_unique<Program>(std::move(
        const_cast<std::vector<std::unique_ptr<Stmt>> &>(atc.statements)));

    std::unique_ptr<Program> ctc =
        tester.generateCTC(std::move(atcCopy), initialConcreteVals, &ve);

    std::cout << "\nConcrete Test Case (CTC):" << std::endl;
    printer.visitProgram(*ctc);

    // Cleanup
    cleanup(globalSymTable);
    delete functionFactory;
  }
};

int main(int argc, char *argv[]) {
  // std::cout << "End-to-End Test Suite: Spec -> ATC -> CTC" << std::endl;
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
    return 1;
  }
  string inputFile = argv[1];
  TestGen testGen(inputFile);
  testGen.execute();
}
