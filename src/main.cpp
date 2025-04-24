#include "antlr4-runtime.h"

#include "TypeAnnotationListLexer.h"
#include "TypeAnnotationListParser.h"
#include "FormulaLexer.h"
#include "FormulaParser.h"

using namespace antlr4;

int main()
{
    const std::string myTypeList = R"(
        Enum request {
            commit_success,
            commit_bad,
            commit_error,
            commit_reuse,
            commit_reflect,
            unknown,
            confirm_success,
            confirm_bad,
            association_request,
            commit_success_ac_token
        };
        Enum group {
            supported,
            unsupported
        };
        Enum status_code {
            success,
            h2e,
            unsupported_cyclic_group,
            unknown_password_identifier
        };

        Bool rg_container;
        Bool ac_container;
        Bool pi_container;
        Enum rg {
            supported,
            unsupported
        };
        Bool ac;
        Bool pi;

        Enum response {
            commit_success,
            commit_error,
            timeout,
            confirm_success,
            confirm_error,
            commit_ac_token
        };
        Int ap_group;
        Int ap_send_confirm;

        Enum ap_status_code {
            success,
            h2e,
            unsupported_cyclic_group,
            unknown_password_identifier
        };

        Bool ap_pi_container;
        Bool ap_pi;
    )";

    const std::string myForumula = R"(
        H (
            ((O response=confirm_success) & request=confirm_success &
            (send_confirm < 65535 | send_confirm > ap_send_confirm))
            -> (response=confirm & ap_send_confirm = 65535)
        )
    )";

    ANTLRInputStream typeListInputStream(myTypeList);
    TypeAnnotationListLexer lexer(&typeListInputStream);
    CommonTokenStream tokens(&lexer);
    TypeAnnotationListParser parser(&tokens);
    TypeAnnotationListParser::TypeAnnotationListContext *typeListTree = parser.typeAnnotationList();

    ANTLRInputStream formulaInputStream(myForumula);
    FormulaLexer formulaLexer(&formulaInputStream);
    CommonTokenStream formulaTokens(&formulaLexer);
    FormulaParser formulaParser(&formulaTokens);
    FormulaParser::FormulaContext *formulaTree = formulaParser.formula();

    std::cout << typeListTree->toStringTree(&parser) << std::endl;
    std::cout << std::endl;
    std::cout << formulaTree->toStringTree(&formulaParser) << std::endl;
}