#include"includes.h"
#include <regex>
const std::regex kRxNum("[0-9]{1,4}");
const std::regex kRxDec("[TtHh]");
bool get_number(int &n, int min, int max, std::string info){
    std::cout<<info;
    std::string strInp;
    bool res = false;;
    //getline(std::cin, strInp);
    std::cin>>strInp;
    if(regex_match(strInp, kRxNum)){
        n=stoi(strInp);
        if(n>=min&&n<=max)
        {
            res = true;
        }
    }
    if(!res)
    {
        std::cout<<"Incorrect data, try again: "<<std::endl;
    }
    return res;
}
bool get_decision(std::string&str, std::string info){
   std::cout<<info;
   std::fflush(stdin);
   std::fflush(stdout);
   std::string strInp;
   bool res = false;
   getline(std::cin, strInp);
   if(regex_match(strInp, kRxDec)){
       str = strInp;
       res = true;
   }
   return res;
}
