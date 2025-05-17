#include "PredicateCheckerVisitor.h"
#include "Symbol.h"

antlrcpp::Any PredicateCheckerVisitor::visitFormula(FormulaParser::FormulaContext *ctx)
{
    return visitChildren(ctx);
}

antlrcpp::Any PredicateCheckerVisitor::visitPredicates(FormulaParser::PredicatesContext *ctx)
{
    std::string idText = ctx->children[0]->getText();
    std::string operatorText = ctx->children[1]->getText();

    auto term = dynamic_cast<FormulaParser::TermContext *>(ctx->children[2]);

    std::string termText;
    Symbol::SymbolType termType;

    if (term->Id())
    {
        termText = term->Id()->getText();

        auto it = symbolTable.find(termText);
        if (it != symbolTable.end())
        {
            termType = it->second.type;
        }
        else
        {
            // if not found in symbol table, its an enum value
            termType = Symbol::SymbolType::ENUM;
        }
    }
    else if (term->Int())
    {
        termText = term->Int()->getText();
        termType = Symbol::SymbolType::INT;
    }
    else if (term->Bool())
    {
        termText = term->Bool()->getText();
        termType = Symbol::SymbolType::BOOL;
    }
    else
    {
        std::cerr << "Unknown term type" << std::endl;
        this->errors.push_back(ctx);
        return nullptr;
    }

    Symbol idSymbol;

    auto it = symbolTable.find(idText);

    if (it != symbolTable.end())
    {
        idSymbol = it->second;
    }
    else
    {
        std::cerr << "Symbol not found: " << idText << std::endl;
        this->errors.push_back(ctx);
        return nullptr;
    }

    if (idSymbol.type != termType)
    {
        std::cerr << "Type mismatch: " << idText << " and " << termText << std::endl;
    }

    if (idSymbol.type == Symbol::SymbolType::ENUM)
    {
        if (operatorText != "=" && operatorText != "!=")
        {
            std::cerr << "Invalid operator for enum: " << operatorText << std::endl;
            this->errors.push_back(ctx);
            return nullptr;
        }

        if (std::find(idSymbol.enumValues.begin(), idSymbol.enumValues.end(), termText) == idSymbol.enumValues.end())
        {
            std::cerr << "Enum value not found: " << termText << std::endl;
            this->errors.push_back(ctx);
            return nullptr;
        }
    }
    else if (idSymbol.type == Symbol::SymbolType::INT)
    {
        if (operatorText != "=" && operatorText != "!=" && operatorText != "<" && operatorText != ">" && operatorText != "<=" && operatorText != ">=")
        {
            std::cerr << "Invalid operator for int: " << operatorText << std::endl;
            this->errors.push_back(ctx);
            return nullptr;
        }
    }
    else if (idSymbol.type == Symbol::SymbolType::BOOL)
    {
        if (operatorText != "=" && operatorText != "!=")
        {
            std::cerr << "Invalid operator for bool: " << operatorText << std::endl;
            this->errors.push_back(ctx);
            return nullptr;
        }
    }

    return nullptr;
}