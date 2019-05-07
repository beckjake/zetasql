
#include "absl/strings/string_view.h"
#include "zetasql/parser/parser.h"
#include "zetasql/parser/parse_tree.h"

extern "C" {

int iterate_ast_node(const zetasql::ASTNode *node, const int depth) {
    auto range = node->GetParseLocationRange();
    auto start = range.start().GetByteOffset();
    auto end = range.end().GetByteOffset();
    std::cout << std::string(depth, ' ') << std::string(depth, ' ') << node->SingleNodeDebugString() << " [" << start << '-' << end << "]\n";
    int found = 1;

    for (int i=0; i < node->num_children(); i++) {
        const zetasql::ASTNode* child = node->child(i);
        if (child != nullptr) {
            found += iterate_ast_node(child, depth+1);
        }
    }
    return found;
}

int get_statement_parts(const char *statement) {
    auto input = absl::string_view(statement, strlen(statement));
    auto opts = zetasql::ParserOptions();
    std::unique_ptr<zetasql::ParserOutput> parser_output;
    auto status = zetasql::ParseStatement(input, opts, &parser_output);
    if (!status.ok()) {
        std::cout << "got a sad status during parsing: " << status << "\n";
        return -1;
    }
    auto parsed = parser_output->statement();
    std::cout << "parser_output->statement()->DebugString():\n" << parsed->DebugString() << "\n\n";

    std::cout << "manual iteration:\n";
    return iterate_ast_node(parsed, 0);
}

}
