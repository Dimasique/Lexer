//
// Created by Дима on 26.11.2020.
//
#pragma once
#include <string>
#include <iostream>

class Lexeme
{

public:
    Lexeme(std::string str, std::string type);

    std::string getStr();
    std::string getType();

    friend std::ostream& operator << (std::ostream& out, const Lexeme& lex);

private:

    std::string str;
    std::string type;
};


