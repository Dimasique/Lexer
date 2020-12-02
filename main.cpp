#include "Lexer/Lexer.h"

int main() {

    string jsons_path = R"(C:\ClionProjects\resources\jsons)";
    string text_path = R"(C:\ClionProjects\resources\input.txt)";

    Lexer lexer(jsons_path);
    lexer.load(text_path);

    auto res = lexer.find_lexemes(5);
    for (const auto& i : res) {
        std::cout << i << '\n';
    }
}