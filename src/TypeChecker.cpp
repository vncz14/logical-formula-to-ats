#include <string>
#include <iostream>

#include "TypeAnnotationListLexer.h"
#include "TypeAnnotationListParser.h"

#include "TypeChecker.h"

TypeChecker::TypeChecker(TypeAnnotationListParser::TypeAnnotationListContext &typeListTree)
{
    for (auto typeAnnotation : typeListTree.typeAnnotation())
    {
        std::string symbolName = typeAnnotation->Id()->getText();
        typeMap[symbolName] = Symbol(typeAnnotation);
    }

    for (const auto &pair : typeMap)
    {
        const std::string &name = pair.first;
        const Symbol &symbol = pair.second;

        std::cout << "Symbol: " << name << ", Type: ";
        switch (symbol.type)
        {
        case Symbol::SymbolType::ENUM:
            std::cout << "ENUM";
            break;
        case Symbol::SymbolType::INT:
            std::cout << "INT";
            break;
        case Symbol::SymbolType::BOOL:
            std::cout << "BOOL";
            break;
        }
        std::cout << std::endl;
    }
}