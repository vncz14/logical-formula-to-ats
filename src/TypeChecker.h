#include <string>

#include "TypeAnnotationListParser.h"

#include "Symbol.h"

class TypeChecker
{
private:
    std::unordered_map<std::string, Symbol> typeMap;

public:
    // dummy default constructor
    TypeChecker() {};

    TypeChecker(std::string typeAnnotationList);
    TypeChecker(TypeAnnotationListParser::TypeAnnotationListContext &typeListTree);
    static FormulaParser::FormulaContext *formulaToTree(std::string formula);

    std::vector<FormulaParser::PredicatesContext *> check(FormulaParser::FormulaContext *tree);
};
