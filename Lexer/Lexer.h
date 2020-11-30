//
// Created by Дима on 26.11.2020.
//
#pragma once
#include "../FSM/FSM.h"
#include "../Lexem/Lexem.h"
#include <fstream>
#include <sstream>

using std::ifstream;
using std::stringstream;

class Lexer
{
public:
    explicit Lexer(const string& path);
    void load(const string& path);
    vector<Lexeme> find_lexemes(int skip = 0);

private:
    vector<FSM> fsms;
    vector<bool> is_valid;
    string text;
};


