//
// Created by Дима on 26.11.2020.
//

#include "Lexem.h"
#include <utility>

Lexeme::Lexeme(std::string str, std::string type) : str(std::move(str)), type(std::move(type)) {}

std::string Lexeme::getStr()
{
    return str;
}

std::string Lexeme::getType()
{
    return type;
}


std::ostream& operator<<(std::ostream& out, const Lexeme& lex)
{
    std::string s = lex.str;
    if (s == "\n") {
        s = "\\n";
    }
    else if (s == "\t") {
        s = "\\t";
    }
    else if (s == "\r") {
        s = "\\r";
    }

    return out << "{\"" << s << "\", " << lex.type << "}";
}

