//
// Created by Дима on 26.11.2020.
//
#pragma once

#include "../Lexem/Lexem.h"
#include <string>
#include <unordered_set>
#include <map>
#include <vector>
#include <filesystem>
#include "../json_lib/json.hpp"
#include <fstream>

namespace fs = std::filesystem;
using json = nlohmann::json;


using std::string;
using std::unordered_set;
using std::map;
using std::pair;
using std::vector;
using std::make_pair;
using std::filesystem::path;


class FSM
{

public:

    FSM(const string& path);

    bool next(char ch, int idx);
    void init();

    int get_priority() const;
    string get_type() const;
    vector<int> get_found() const;

private:

    int priority;
    string type;

    unordered_set<string> cur_states;
    unordered_set<string> init_states;
    unordered_set<string> term_states;

    map<pair<string, char>, string> go;
    vector<int> found;

    void add_any_letter(const string& state1, const string& state2);
    void add_any_digit(const string& state1, const string& state2);
};

