#include <string>
#include <iostream>

#include "TypeAnnotationListLexer.h"
#include "TypeAnnotationListParser.h"
#include "FormulaLexer.h"
#include "FormulaParser.h"

#include "PredicateCheckerVisitor.h"

#include "TypeChecker.h"

using namespace antlr4;

TypeChecker::TypeChecker(std::string typeAnnotationList)
{
    ANTLRInputStream typeAnnotationListInputStream(typeAnnotationList);
    TypeAnnotationListLexer typeAnnotationListLexer(&typeAnnotationListInputStream);
    CommonTokenStream typeAnnotationListTokens(&typeAnnotationListLexer);
    TypeAnnotationListParser typeAnnotationListParser(&typeAnnotationListTokens);
    TypeAnnotationListParser::TypeAnnotationListContext *typeListTree = typeAnnotationListParser.typeAnnotationList();

    *this = TypeChecker(*typeListTree);
}

TypeChecker::TypeChecker(TypeAnnotationListParser::TypeAnnotationListContext &typeListTree)
{
    for (auto typeAnnotation : typeListTree.typeAnnotation())
    {
        std::string symbolName = typeAnnotation->Id()->getText();
        typeMap[symbolName] = Symbol(typeAnnotation);
    }
}

std::vector<FormulaParser::PredicatesContext *> TypeChecker::check(FormulaParser::FormulaContext *tree)
{
    std::vector<FormulaParser::PredicatesContext *> errors;
    PredicateCheckerVisitor visitor(this->typeMap, errors);

    visitor.visit(tree);

    return errors;
}