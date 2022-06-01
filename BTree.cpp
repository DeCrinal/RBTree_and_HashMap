#include "BTree.h"
/*
Node* BPlusTree::find_leaf(int key) {
    Node* cur = root;
    while (cur->getLeaf() != true)
        for (int i = 0; i < cur->getKey_num(); i++)
            if (i == cur->getKey_num() or key < cur->getKey(i)){
                cur = cur->getChild(i);
                break;
            }
    return cur;
}

bool BPlusTree::in(int k, Node* node) {
    bool flag=0;
    while (node->getLeaf() != true)
    for (int i = 0; i < node->getKey_num(); i++)
        if (k == node->getKey(i))
            flag = true;
        else {
            node = node->getChild(i);
            break;
        }
    return flag;
}
/*
Node* BPlusTree::find_key(int key) {
    Node* cur = root;
    while (cur->getLeaf() != true)
        for (int i = 0; i < cur->getKey_num(); i++)
            if (i == cur->getKey_num() or key < cur->getKey(i)) {
                cur = cur->getChild(i);
                break;
            }
    return cur;
}*/

/*

void BPlusTree::split(Node* node) {
    Node* new_node=new Node;                  //??????? ????? ????

    // ?????????????? right ? left ?????????
    new_node->setRignt(node->getRight());
    node->getRight()->setLeft(new_node);
    node->setRignt(new_node);
    new_node->setLeft(node);

        // ?????????? t - 1 ???????? ? ??????????????? ?? ?????????? ? new_node
    int mid_key = node->getKey(t);
    new_node->setKey_num(t - 1);
    node->setKey_num(t);
    for (int i = 0; i < new_node->getKey_num() - 1; i++) {
        new_node->setKey(i, node->getKey(i + t + 1));
        new_node->setPointers(i, node->getPointers(i + t + 1));
        new_node->setChild(i, node->getChild(i + t + 1));
    }
    new_node->setChild(new_node->getKey_num(), node->getChild(2 * t));
    if (node->getLeaf()) {
        new_node->setKey_num(new_node->getKey_num() + 1);
        new_node->setLeaf(true);
        // ?????????? ? new_node ?????????? ??? ????????? ??????? mid_key
        for (int i = new_node->getKey_num()- 1; i > 1; i--){
            new_node->setKey(i, new_node->getKey(i - 1));
            new_node->setPointers(i, new_node->getPointers(i - 1));
        }
        new_node->setKey(0, node->getKey(t));
        new_node->setPointers(0, node->getPointers(t));
    }
    if (node == root) {
        root = new Node;               // ??????? ????? ?????? T.root
        root->setKey(0, mid_key);
        root->setChild(0, node);
        root->setChild(1, new_node);
        root->setKey_num(1);
        node->setParent(root);
        new_node->setParent(root);
    }
    else {
        new_node->setParent(node->getParent());
        Node *parent = node->getParent();

            // »??? ??????? mid_key ? ????
        int pos = 0;
        while (pos < parent->getKey_num() && parent->getKey(pos) < mid_key)
            ++pos;

                // ????????? mid_key ? ???? ? ?????????? ?????? ?? ???? ?? new_node
        for (int i = parent->getKey_num(); i > pos + 1; i--)
            parent->setKey(i, parent->getKey(i - 1));
        for (int i = parent->getKey_num() + 1; i > pos + 2; i--)
            parent->setChild(i, parent->getChild(i - 1));
        parent->setKey(pos, mid_key);
        parent->setChild(pos + 1, new_node);
        parent->setKey_num(parent->getKey_num()+1);
        if (parent->getKey_num() == 2 * t)
            split(parent);
    }
}

bool BPlusTree::insert(int key, string value) {
    Node* leaf=find_leaf(key);// = find_key(T, key);
    if (in(key, leaf));
        return false;

            // »??? ??????? ??? ?????? ?????
    int pos = 0;
    while (pos < leaf->getKey_num() && leaf->getKey(pos) < key)
        ++pos;

                // ¬???????? ????
    for (int i = leaf->getKey_num(); i > pos + 1; i--) {
        leaf->setKey(i, leaf->getKey(i - 1));
        leaf->setPointers(i, leaf->getPointers(i - 1));
    }
    leaf->setKey(pos,key);
    leaf->setPointers(pos, value);
    leaf->setKey_num(leaf->getKey_num()+1);

    if (leaf->getKey_num() == 2 * t)             // t ? ??????? ??????
        split(leaf);                  // ????????? ????
    return true;
}


bool BPlusTree::deleteElement(int key) {
    Node* leaf = find_leaf(key);
    int pos = 0;
    if (!in(key, leaf))
        return false;
    else
    {
        delete_in_node(leaf, key);                    // ??????? ???? ?? ???????
        return true;
    }
}

void BPlusTree::delete_in_node(Node* tec, int key) {
    if (!in(key, tec))
        return;

    // »??? ??????? ?????????? ?????
    int pos = 0;
    while (pos < tec->getKey_num() && tec->getKey(pos) < key)
        ++pos;

    // ??????? ????
    for (int i = pos; i < tec->getKey_num() - 1; i++) {
        tec->setKey(i, tec->getKey(i + 1));
        tec->setPointers(i, tec->getPointers(i + 1));
    }
    for (int i = pos + 1; i < tec->getKey_num(); i++)
        tec->setChild(i, tec->getChild(i + 1));

    tec->setKey_num(tec->getKey_num() + 1);

    if (tec->getKey_num() < t - 1) {
        Node* right_sibling = tec->getRight();
        Node* left_sibling = tec->getLeft();
        if (left_sibling != nullptr && left_sibling->getKey_num() > t - 1) {
            left_sibling->setKey_num(left_sibling->getKey_num() - 1);
            tec->setKey_num(tec->getKey_num() + 1);



            // ?????????? ???????????? ?? left_sibling ???? ?? ?????? ??????? ? tec
            for (int i = 1; i < tec->getKey_num(); i++){
                tec->setKey(i, tec->getKey(i - 1));
                tec->setPointers(i, tec->getPointers(i - 1));
                tec->setChild(i, tec->getChild(i - 1));
            }
            tec->setChild(tec->getKey_num(), tec->getChild(tec->getKey_num() - 1));
            tec->setKey(0, left_sibling->getKey(left_sibling->getKey_num()));
            tec->setPointers(0, left_sibling->getPointers(left_sibling->getKey_num()));
            tec->setChild(0, left_sibling->getChild(left_sibling->getKey_num() + 1));

                //update(tec)                                                        // ???????? ????? ?? ???? ? ?????
        }
        else if (right_sibling != nullptr and right_sibling->getKey_num() > t - 1){
            right_sibling->setKey_num(right_sibling->getKey_num() - 1);
            tec->setKey_num(tec->getKey_num() + 1);

                // ?????????? ??????????? ?? right_sibling ???? ?? ????????? ??????? ? tec
            tec->setKey(tec->getKey_num() - 1, right_sibling->getKey(0));
            tec->setPointers(tec->getKey_num() - 1, right_sibling->getPointers(0));
            tec->setChild(tec->getKey_num() - 1, right_sibling->getChild(0));
                //update(tec)                                                        // ???????? ????? ?? ???? ? ?????
        }*/
        /*else if (left_sibling != nullptr){

                // ??????? tec ? left_sibling
                for i = 0 to tec.key_num - 1
                    left_sibling.key[left_sibling.key_num] = tec.key[i]
                    left_sibling.pointers[left_sibling.key_num] = tec.pointers[i]
                    left_sibling.child[left_sibling.key_num + 1] = tec.child[i]
                    ++left_sibling.key_num
                    left_sibling.child[left_sibling.key_num + 1] = tec.child[tec.key_num]

                    // ?????????????? right ? left ?????????
                    left_sibling.right = tec.right
                    tec.right.left = left_sibling

                    update(left_sibling)                                            // ???????? ????? ?? ???? ? ?????
                    delete_in_node(left_sibling.parent, min_key(tec))               // ??????? ?????????????? ???? ? ????
            }
            else {

                // ??????? tec ? right_sibling
                for i = 0 to tec.key_num - 1
                    tec.key[tec.key_num] = right_sibling.key[i]
                    tec.pointers[tec.key_num] = right_sibling.pointers[i]
                    tec.child[tec.key_num + 1] = right_sibling.child[i]
                    ++tec.key_num
                    tec.child[tec.key_num + 1] = right_sibling.child[right_sibling.key_num]

                    // ?????????????? right ? left ?????????
                    right_sibling.right.left = tec
                    tec.right = right_sibling.right

                    update(tec)                                                     // ???????? ????? ?? ???? ? ?????
                    delete_in_node(tec.parent, min_key(right_sibling))              // ??????? ?????????????? ???? ? ????
            }	if T.root.key_num == 1
                        T.root = T.root.child[0]
    }
}*/
