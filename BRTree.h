#pragma once
#include"includes.h"

using namespace std;
enum COLOR { RED, BLACK };

class Node {
public:
    string val;
    COLOR color;
    Node* left, * right, * parent;
    int mesto;

    Node(string val) : val(val) {
        parent = left = right = NULL;
        color = RED;
    }
    bool has_red_child();
    Node* uncle();
    bool is_on_left() { return this == parent->left; }
    Node* sibling();
    void move_down(Node* nParent);
};


//????? ??????!!!!

class RBTree {
    Node* root;
    // ????? ???????
    void left_rotate(Node* x);
    //?????? ???????
    void right_rotate(Node* x);


    void swap_colors(Node* x1, Node* x2);

    void swap_values(Node* u, Node* v);
    void fix_red_red(Node* x);
    Node* successor(Node* x);
    Node* BST_replace(Node* x);
    void delete_Node(Node* v);
    void fix_double_black(Node* x);
    void level_order(Node* x);
    void inorder(Node* x);

public:

    RBTree() { root = NULL; }

    Node* get_root() { return root; }
    Node* search(string n);

    void insert(string n);
    void deleteSl(string n);

    void search_element(string n);
    void clear();
    bool delete_or_not(string n);
    void out_file(string n);
    void display(Node* p);
    void disp();
    void print_insert(string slovo);
    void read(string n);
};
