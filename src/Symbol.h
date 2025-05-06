#include <vector>
#include <string>
#include "TypeAnnotationListParser.h"

class Symbol
{
public:
    enum class SymbolType
    {
        ENUM,
        INT,
        BOOL
    };

    std::string name;
    SymbolType type;
    std::vector<std::string> enumValues;

    // dummy default constructor
    Symbol();

    Symbol(TypeAnnotationListParser::TypeAnnotationContext *typeAnnotation);
};