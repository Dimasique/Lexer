//
// Created by Дима on 26.11.2020.
//
#include "Lexer.h"

Lexer::Lexer(const string& path)
{
    for (auto& p : fs::directory_iterator(path)) {
        fsms.emplace_back(p.path().string());
    }

    is_valid.resize(fsms.size(), true);
}

void Lexer::load(const string& path)
{
    ifstream in(path);
    stringstream buffer;
    buffer << in.rdbuf();
    text = buffer.str();

    text += char(1);
    in.close();
}

vector<Lexeme> Lexer::find_lexemes(int skip)
{
    vector<Lexeme> result;
    int num_fsm = (int)fsms.size();
    int prev = skip;

    for (auto& fsm : fsms) {
        fsm.init();
    }

    for (int i = skip; i < text.size(); ++i) {

        for (int j = 0; j < (int)fsms.size(); ++j) {
            if (!is_valid[j]) {
                continue;
            }

            bool ok = fsms[j].next(text[i], i);
            if (!ok) {
                is_valid[j] = false;
                --num_fsm;
            }
        }


        if (num_fsm == 0) {

            int max_prior = -1;
            int max_length = 0;
            string mem_type;


            for (auto& fsm : fsms) {
                int prior = fsm.get_priority();
                int len = fsm.get_found();
                string type = fsm.get_type();

                if (len > max_length) {
                    max_length = len;
                    max_prior = prior;
                    mem_type = type;
                }
                else if (len == max_length && prior > max_prior) {
                    max_prior = prior;
                    mem_type = type;
                }
            }

            assert(max_prior >= 0);
            for (auto& fsm : fsms) {
                fsm.init();
            }

            num_fsm = fsms.size();
            for(int j = 0; j < num_fsm; ++j) {
                is_valid[j] = true;
            }

            i = max_length;
            result.emplace_back(text.substr(prev, max_length - prev + 1), mem_type);
            prev = max_length + 1;

            if (i == text.size() - 2) {
                break;
            }
        }
    }


    return result;
}

