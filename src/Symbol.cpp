#include "Symbol.h"

// dummy default constructor
Symbol::Symbol() {}

Symbol::Symbol(TypeAnnotationListParser::TypeAnnotationContext *typeAnnotation)
{
    name = typeAnnotation->Id()->getText();

    std::string typeText = typeAnnotation->getStart()->getText();

    if (typeText == "Int")
    {
        type = SymbolType::INT;
    }
    else if (typeText == "Bool")
    {
        type = SymbolType::BOOL;
    }
    else if (typeText == "Enum")
    {
        type = SymbolType::ENUM;
    }
    else
    {
        throw std::invalid_argument("Unknown type: " + typeText);
    }

    if (type == SymbolType::ENUM)
    {
        for (auto value : typeAnnotation->commaSeparatedIdList()->Id())
        {
            enumValues.push_back(value->getText());
        }
    }
}
