#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "includes.h"
extern const int size_of_eng_alph;
//extern const std::string alphabet;
class hash_table
{
private:
    std::vector<std::set<std::string>>data;
public:
    hash_table();
    int hash_function(std::string word);
    void insert(std::string word);
    void erase(std::string word);
    int find(std::string word);
    void read(std::string str);
    void out_file(std::string str);
    void disp();
    void clear();
};
int get_symb_index(char32_t ch);
#endif // HASH_TABLE_H
