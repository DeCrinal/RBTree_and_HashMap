//#include <Windows.h>
#include"includes.h"
using std::cout;
using std::string;
using std::cin;
using std::endl;
int Input()
{
    string s;
    while (true)
    {
        cin >> s;
        if (s.find_first_not_of("1234567890") != string::npos)
        {
            cout << "Incorrect value!\nTry again: ";
        }
        else
            return atoi(s.c_str());
    }
}


string InputWord()
{
    string s;
    while (true)
    {
        cin >> s;
        if (s.find_first_not_of("????????????????????????????????????????????????????????????????") != string::npos)
        {
            cout << "Incorrect value.\nTry again: : ";
        }
        else
            return s;
    }
}

int main()
{
    setlocale(LC_ALL,"CP1251");
    RBTree tree;
    hash_table h_table;
    fstream f;
    string word;
    bool is_hash= false, is_RBT=false;
    string decision;
    get_decision(decision, "Do you want to word with RB-Tree[T] or with Hash-table [H]?\n");
    if(decision=="H"||decision=="h")
        is_hash=true;
    else
        is_RBT = true;
    while(is_hash){
        int op;
        get_number(op,0,10,"\nChoose: \n1 Build dictionary \n2 - Add word\n3 - Delete word\n4 - Find word\n5 - Delete Dictionary\n6 - Show dictionary\n0 - Exit\n");
        switch(op)
        {
        case(1):
        {
            h_table.read("Test");
            h_table.out_file("Test");
            h_table.disp();
        }
        case(2):
        {
            cout<<"Input word: "<<endl;
            cin>>word;
            h_table.insert(word);
            std::cout<<"Inserted"<<std::endl;
            break;
        }
        case(3):{
            cout<<"Input word to delete: "<<endl;
            word = InputWord();
            h_table.erase(word);
            break;
        }
        case(4):{
            cout<<"Input word to find: "<<endl;
            word = InputWord();
            h_table.find(word);
            break;
        }
        case(5):{
            h_table.clear();
            cout<<"Clearin done"<<endl;
            break;
        }
        case(6):{
            h_table.disp();
            break;
        }
        case(0):{
            is_hash=false;
            break;
        }
        default:{
            cout<<"Unknown operation"<<endl;
        }
        }
    }
    while (is_RBT)
    {

        char q, k;
        cout << "\nChoose: \n1 - Build dictionary\n2 - Add word\n3 - Delete word\n4 - Find word\n5 - Delete Dictionary\n6 - Show dictionary\n";
        cout << "0 - Exit\n";
        q = Input();

        switch (q)
        {
        case 1:
            tree.read("Test");
            tree.out_file("Test");
            tree.disp();
            break;
        case 2:
            cout << "Input word:" << endl;
            cin>>word;

            tree.insert(word);

            tree.print_insert(word);
            cout << "\nChoose: \n1-show full dicrionary\n2-continue" << endl;
            k = Input();
            switch (k)
            {
            case 1:
                tree.disp();
                break;
            case 2:
                break;
            default:
                cout << "Incorrect value. Input again: " << endl;
                break;
            }

            break;
        case 3:
            cout << "Input word:" << endl;
            word = InputWord();
            if (tree.delete_or_not(word))
                cout << "The word was deleted." << endl;
            tree.deleteSl(word);

            cout << "\nChoose: \n1-show full dictionary\n2-continue" << endl;
            k = Input();
            switch (k)
            {
            case 1:
                tree.disp();
                break;
            case 2:
                break;
            default:
                cout << "Incorrect value. Input again: " << endl;
                break;
            }
            break;
        case 4:
            cout << "Input word:" << endl;
            word = InputWord();
            tree.search_element(word);

            break;
        case 5:
            tree.clear();
            cout << "\nThe dictionary was deleted." << endl;
            break;
        case 6:
            tree.disp();
            break;
        case 0:
            is_RBT = false;
            break;
        default:
            cout << "Incorrect value. Input again: " << endl;
            break;
        }
    }
    return 0;
}
