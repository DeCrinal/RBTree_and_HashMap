#include "BRTree.h"


FILE* pFile;
fstream f;


Node* Node::uncle() {

    if (parent == NULL or parent->parent == NULL)
        return NULL;
    if (parent->is_on_left())
        return parent->parent->right;
    else
        return parent->parent->left;
}


Node* Node::sibling() {

    if (parent == NULL)
        return NULL;

    if (is_on_left())
        return parent->right;

    return parent->left;
}


void Node::move_down(Node* nParent) {
    if (parent != NULL) {
        if (is_on_left()) {
            parent->left = nParent;
        }
        else {
            parent->right = nParent;
        }
    }
    nParent->parent = parent;
    parent = nParent;
}

bool Node::has_red_child() {
    return (left != NULL and left->color == RED) or
        (right != NULL and right->color == RED);
}


void RBTree::left_rotate(Node* x) {

    Node* nParent = x->right;
    if (x == root)
        root = nParent;

    x->move_down(nParent);

    x->right = nParent->left;

    if (nParent->left != NULL)
        nParent->left->parent = x;

    nParent->left = x;
}


void RBTree::right_rotate(Node* x) {

    Node* nParent = x->left;


    if (x == root)
        root = nParent;

    x->move_down(nParent);


    x->left = nParent->right;

    if (nParent->right != NULL)
        nParent->right->parent = x;


    nParent->right = x;
}


void RBTree::swap_colors(Node* x1, Node* x2) {
    COLOR temp;
    temp = x1->color;
    x1->color = x2->color;
    x2->color = temp;
}


void RBTree::swap_values(Node* u, Node* v) {
    string temp;
    temp = u->val;
    u->val = v->val;
    v->val = temp;
}



void RBTree::fix_red_red(Node* x) {

    if (x == root) {
        x->color = BLACK;
        return;
    }


    Node* parent = x->parent, * grandparent = parent->parent,
        * uncle = x->uncle();

    if (parent->color != BLACK) {
        if (uncle != NULL && uncle->color == RED) {

            parent->color = BLACK;
            uncle->color = BLACK;
            grandparent->color = RED;
            fix_red_red(grandparent);
        }
        else {

            if (parent->is_on_left()) {
                if (x->is_on_left()) {

                    swap_colors(parent, grandparent);
                }
                else {
                    left_rotate(parent);
                    swap_colors(x, grandparent);
                }

                right_rotate(grandparent);
            }
            else {
                if (x->is_on_left()) {

                    right_rotate(parent);
                    swap_colors(x, grandparent);
                }
                else {
                    swap_colors(parent, grandparent);
                }

                left_rotate(grandparent);
            }
        }
    }
}



Node* RBTree::successor(Node* x) {
    Node* temp = x;

    while (temp->left != NULL)
        temp = temp->left;

    return temp;
}


Node* RBTree::BST_replace(Node* x) {

    if (x->left != NULL and x->right != NULL)
        return successor(x->right);


    if (x->left == NULL and x->right == NULL)
        return NULL;


    if (x->left != NULL)
        return x->left;
    else
        return x->right;
}


void RBTree::delete_Node(Node* v) {
    Node* u = BST_replace(v);

    bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
    Node* parent = v->parent;

    if (u == NULL) {

        if (v == root) {

            root = NULL;
        }
        else {
            if (uvBlack) {
                fix_double_black(v);
            }
            else {

                if (v->sibling() != NULL)

                    v->sibling()->color = RED;
            }

            if (v->is_on_left()) {
                parent->left = NULL;
            }
            else {
                parent->right = NULL;
            }
        }
        delete v;
        return;
    }

    if (v->left == NULL or v->right == NULL) {

        if (v == root) {

            v->val = u->val;
            v->left = v->right = NULL;
            delete u;
        }
        else {

            if (v->is_on_left()) {
                parent->left = u;
                parent->mesto = 0;
            }
            else {
                parent->right = u;
                parent->mesto = 1;
            }
            delete v;
            u->parent = parent;
            if (uvBlack) {

                fix_double_black(u);
            }
            else {

                u->color = BLACK;
            }
        }
        return;
    }


    swap_values(u, v);
    delete_Node(u);
}




void RBTree::fix_double_black(Node* x) {
    if (x == root)

        return;

    Node* sibling = x->sibling(), * parent = x->parent;
    if (sibling == NULL) {

        fix_double_black(parent);
    }
    else {
        if (sibling->color == RED) {

            parent->color = RED;
            sibling->color = BLACK;
            if (sibling->is_on_left()) {

                right_rotate(parent);
            }
            else {

                left_rotate(parent);
            }
            fix_double_black(x);
        }
        else {

            if (sibling->has_red_child()) {

                if (sibling->left != NULL and sibling->left->color == RED) {
                    if (sibling->is_on_left()) {

                        sibling->left->color = sibling->color;
                        sibling->color = parent->color;
                        right_rotate(parent);
                    }
                    else {

                        sibling->left->color = parent->color;
                        right_rotate(sibling);
                        left_rotate(parent);
                    }
                }
                else {
                    if (sibling->is_on_left()) {

                        sibling->right->color = parent->color;
                        left_rotate(sibling);
                        right_rotate(parent);
                    }
                    else {

                        sibling->right->color = sibling->color;
                        sibling->color = parent->color;
                        left_rotate(parent);
                    }
                }
                parent->color = BLACK;
            }
            else {

                sibling->color = RED;
                if (parent->color == BLACK)
                    fix_double_black(parent);
                else
                    parent->color = BLACK;
            }
        }
    }
}



void RBTree::level_order(Node* x) {
    if (x == NULL)

        return;

    queue<Node*> q;
    Node* curr;

    q.push(x);

    while (!q.empty()) {

        curr = q.front();
        q.pop();
        cout << curr->val << " ";

        if (curr->left != NULL)
            q.push(curr->left);
        if (curr->right != NULL)
            q.push(curr->right);
    }
}




void RBTree::inorder(Node* x) {
    if (x == NULL)
        return;
    inorder(x->left);
    cout << x->val << " ";
    inorder(x->right);
}




Node* RBTree::search(string n)
{
    Node* temp = root;
    while (temp != NULL) {
        if (n < temp->val) {
            if (temp->left == NULL)
                break;
            else
                temp = temp->left;
        }
        else if (n == temp->val) {
            break;
        }
        else {
            if (temp->right == NULL)
                break;
            else
                temp = temp->right;
        }
    }

    return temp;
}


void RBTree::insert(string n)
{
    Node* newNode = new Node(n);


    if (root == NULL) {

        newNode->color = BLACK;
        root = newNode;
    }
    else {
        Node* temp = search(n);

        if (temp->val == n) {
            cout << "Word is in dictionary." << endl;
            cout << "Location:" << endl;
            return;
        }
        newNode->parent = temp;

        if (n < temp->val)
        {
            temp->left = newNode;
        }

        else
        {
            temp->right = newNode;
        }

        fix_red_red(newNode);
    }

}


void RBTree::deleteSl(string n) {
    if (root == NULL)

        return;

    Node* v = search(n), * u;

    if (v->val != n) {
        cout << "Word" << n << " wasn't found." << endl;
        return;
    }


    delete_Node(v);
}

bool RBTree::delete_or_not(string n)
{
    Node* v = search(n);
    if (v->val == n)
        return true;
    else
        return false;
}

void RBTree::search_element(string n)
{
    {
        Node* v = search(n);

        if (v->val == n)
        {
            cout << "Word" << n << " is in dictionary" << endl;
            cout << "\n Color: ";
            if (v->color == BLACK)
                cout << "Black";
            else
                cout << "Red";
            if (v->parent != NULL)
                cout << "\n Parent: " << v->parent->val;
            else
                cout << "\n Is root";
            if (v->right != NULL)
                cout << "\n Right: " << v->right->val;
            else
                cout << "\n Right:\n Color: Black\n" << "Vale: NULL";
            if (v->left != NULL)
                cout << "\n Left: " << v->left->val;
            else
                cout << "\n Left:\n Color: Black\n" << " Value: NULL";
            cout << endl;
        }
        else
        {
            cout << "Word" << n << " is not in dictionary" << endl;
        }
    }
}


void RBTree::clear()
{
    while (root != NULL)
    {
        deleteSl(root->val);
    }
}




void RBTree::read(string str)
{
    string data, pos;
    ifstream file(str);

    while (getline(file, data))
    {

        cout << data << endl;
    }
    file.close();
}


void RBTree::out_file(string str)
{
    string data, str1;
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


void RBTree::disp()
{
    display(root);
}

void RBTree::display(Node* p)
{
    if (root == NULL)
    {
        cout << "\nThe dictionary is empty.";
        return;
    }
    if (p != NULL)
    {
        cout << "\n Word: " << p->val;
        cout << "\n Color: ";
        if (p->color == BLACK)
            cout << "Black";
        else
            cout << "Red";
        if (p->parent != NULL)
            cout << "\n Parent: " << p->parent->val;
        else
            cout << "\n Is root";
        if (p->right != NULL && p->right->val != "")
            cout << "\n Right: " << p->right->val;
        else
            cout << "\n Right:\n Color: Black\n" << " Value: NULL";
        if (p->left != NULL && p->left->val != "")
            cout << "\n Left: " << p->left->val;
        else
            cout << "\n Left:\n Color: Black\n" << " Value: NULL";
        cout << endl;
        if (p->left)
        {
            cout << "\n\nLeft:\n";
            display(p->left);
        }

        if (p->right)
        {
            cout << "\n\nRight:\n";
            display(p->right);
        }

    }
    else
        cout<<"---";
}

void RBTree::print_insert(string slovo)
{

    Node* v = search(slovo);
    cout << "\n Color: ";
    if (v->color == BLACK)
        cout << "Black";
    else
        cout << "Red";
    if (v->parent != NULL)
        cout << "\n Parent: " << v->parent->val;
    else
        cout << "\n Is root";
    if (v->right != NULL)
        cout << "\n Right: " << v->right->val;
    else
        cout << "\nColor: Black\n" << "Value: NULL\n";
    if (v->left != NULL)
        cout << "\n Left: " << v->left->val;
    else
        cout << "\nColor: Black\n" << "Value: NULL\n";
    cout << endl;
}

