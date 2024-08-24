#include <iostream>
#include <list>
#include <string.h>

enum token_type {
    start_file,
    number,
    paran_open,
    paran_close
};

string parse_token_type_as_string(token_type type) {
    switch (type) {
        case start_file:
            return "start_file";
        case number:
            return "number";
        default:
            return "NULL";
    }
}

struct token {
    token_type Type;
    string Value;
    int ParentTokenID;
};

void tokenizeCode(list<token> &token_list, string code) {
    token start{start_file, "-", -1};
    token_list.push_back(start);
    list<string> spaced_split_code;
    string collected_word = "";
    for (auto i : code) {
        cout << i;
        collected_word += i;
        if (i == ' ') {
            spaced_split_code.push_back(collected_word);
            collected_word = "";
        }
    }
    spaced_split_code.push_back(collected_word);
    cout << '\n';
    for (auto i : spaced_split_code) {
        cout << i << '\n';
    }
    
    for (auto i : spaced_split_code) {
        // token tmp{start_file};
    }

    for (auto i : token_list) {
        cout << parse_token_type_as_string(i.Type) << ' ';
    }
    cout << '\n';
    for (auto i : token_list) {
        cout << i.Value << ' ';
    }
}