#include <unordered_map>
#include <string>
#include <iostream>

#include "FormulaBaseVisitor.h"
#include "Symbol.h"

class PredicateCheckerVisitor : public FormulaBaseVisitor
{
public:
    PredicateCheckerVisitor(const std::unordered_map<std::string, Symbol> &symbolTable,
                            std::vector<FormulaParser::PredicatesContext *> &errors)
        : symbolTable(symbolTable), errors(errors) {}

    antlrcpp::Any visitFormula(FormulaParser::FormulaContext *ctx) override;
    antlrcpp::Any visitPredicates(FormulaParser::PredicatesContext *ctx) override;

private:
    const std::unordered_map<std::string, Symbol> &symbolTable;
    std::vector<FormulaParser::PredicatesContext *> &errors;
};