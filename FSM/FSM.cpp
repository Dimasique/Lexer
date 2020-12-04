//
// Created by Дима on 26.11.2020.
//

#include "FSM.h"

FSM::FSM(const string& path) : found(-1)
{

    std::ifstream in(path);
    json j;

    in >> j;
    this->priority = j["priority"];
    this->type = j["type"];


    for(const auto& state : j["init_states"]) {
        this->init_states.insert((string)state);
    }
    for(const auto& state : j["term_states"]) {
        this->term_states.insert((string)state);
    }

    auto go_json = j["go"];
    for(const auto& el : go_json.items()) {
        const string& state = el.key();

        for(const auto& in_el : el.value().items()) {

            for(const auto& next_state : in_el.value()) {

                if (in_el.key() == "any_letter") {
                    add_any_letter(state, next_state);
                }
                else if (in_el.key() == "any_digit") {
                    add_any_digit(state, next_state);
                }
                else
                    this->go[make_pair(state, in_el.key()[0])] = next_state;
            }
        }
    }
    init();
}

bool FSM::next(char ch, int idx)
{
    unordered_set<string> next_states;

    for (const auto& state : cur_states) {

        auto pair = make_pair(state, ch);

        if (!go.count(pair)) {
            continue;
        }

        string next_state = go[pair];
        next_states.insert(next_state);

        if (term_states.count(next_state)) {
            found = idx;
        }
    }

    cur_states = next_states;
    return !cur_states.empty();
}

void FSM::init()
{
    found = -1;
    cur_states = init_states;
}

int FSM::get_priority() const
{
    return priority;
}

int FSM::get_found() const
{
    return found;
}

string FSM::get_type() const {
    return type;
}

void FSM::add_any_letter(const string& state1, const string& state2) {
    for(char c = 'a'; c <= 'z'; ++c) {
        go[make_pair(state1, c)] = state2;
    }
}

void FSM::add_any_digit(const string &state1, const string &state2) {
    for(char c = '0'; c <= '9'; ++c) {
        go[make_pair(state1, c)] = state2;
    }
}
