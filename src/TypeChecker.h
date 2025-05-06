#include <string>

#include "TypeAnnotationListParser.h"

#include "Symbol.h"

class TypeChecker
{
private:
    std::unordered_map<std::string, Symbol> typeMap;

public:
    TypeChecker(TypeAnnotationListParser::TypeAnnotationListContext &typeListTree);
};
