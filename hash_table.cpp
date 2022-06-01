#include "hash_table.h"
#include <iostream>
#include "includes.h"
const int size_of_eng_alph = 66;
//const std::string alphabet = "";
hash_table::hash_table()
{
    data.resize((size_of_eng_alph+1)*(size_of_eng_alph+1)*(size_of_eng_alph+1));
}
void hash_table::erase(std::string word){
    int index_for_erasing = hash_function(word);
    if(index_for_erasing!=-1) {
        if(data[index_for_erasing].find(word)!=data[index_for_erasing].end())
        {
            data[index_for_erasing].erase(word);
            std::cout<<"Word \'"<<word<<"\' was erased"<<std::endl;
        }
    }
    else{
        std::cout<<"No such word in dictionary"<<std::endl;
    }
    return;
}
void hash_table::insert(std::string word){
    int index_for_insertion = hash_function(word);
    if(index_for_insertion!=-1)
        data[index_for_insertion].insert(word);
    return;
}
int hash_table::find(std::string word){
    int index_for_finding = hash_function(word);
    if(data[index_for_finding].empty()){
        std::cout<<"No such word in dictionary";
        return 1;
    }
    else{
        if(data[index_for_finding].find(word)!=data[index_for_finding].end())
        {
            std::cout<<"Word is in dictionary"<<std::endl;
        }
        else{
            std::cout<<"Word is not in dictionary"<<std::endl;
        }

    }
    return 0;
}
int hash_table::hash_function(std::string word){
    int res_index = 1;
    int length = word.size();
    int index_first, index_mid, index_last;
    index_first = get_symb_index(word[0]);
    index_mid = get_symb_index(word[length/2]);
    index_last = get_symb_index(word[length-1]);
    res_index = index_first*index_mid*index_last;
    return res_index;
}
int get_symb_index(char32_t ch){
    return ch-191;
}
void hash_table::disp(){
    for(uint i = 0; i<data.size();i++){
        if(!data[i].empty()){
            for(auto it = data[i].begin();it!=data[i].end();it++){
                std::cout<<*it<<std::endl;
            }
        }
    }
}
void hash_table::clear(){
    for(uint i = 0; i<data.size();i++){
        if(!data[i].empty()){
            data[i].clear();
        }
    }
}
void hash_table::read(string str){
   string data, pos;
   ifstream file(str);

   while(getline(file, data))
   {
       cout<<data<<endl;
   }
   file.close();
}
void hash_table::out_file(std::string str)
{
    std::string data, str1;
    ifstream file(str);
    string filt_elems(""", .; :!? )(\ / ");



    while (getline(file, data, ' '))
    {

        str1 = data;
        if (str1.find_first_of(""", .; :!? )(\ /") != string::npos)
        {
            data.erase(data.end() - 1);
        }

        insert(data);
    }


    file.close();

}
