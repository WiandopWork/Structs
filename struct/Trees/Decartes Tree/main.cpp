#include <iostream>

using namespace std;

#define elem_t int

struct Node {
    elem_t key;
    int prior;
    Node* left;
    Node* right;
};

Node* make_node(elem_t);
Node* Merge(Node*, Node*);
pair <Node*, Node*> Split(Node*, elem_t);
Node* insert(Node*, elem_t);
Node* erase(Node*, elem_t);

void print_tree (Node*);
void print_lvl_tree (Node*);
int print_slice (Node*, int);

int main() {
    Node* DTree = NULL;

    for (int i = 1; i <= 10; i++) {
        DTree = insert(DTree, i);
        print_lvl_tree(DTree);
        cout << "-----------------------------------" << endl;
    }
    return 0;
}

Node* make_node(elem_t key) {
    Node* ans = new Node;
    ans->right = ans->left = NULL;
    ans->key = key;
    ans->prior = rand();

    return ans;
}

Node* Merge(Node* root1, Node* root2) {
    // Все ключи T1 должны быть меньше ключей T2

    if (root1 == NULL) {
        return root2;
    }

    if (root2 == NULL) {
        return root1;
    }

    if (root1->prior > root2->prior) {
        root1->right = Merge(root1->right, root2);
        return root1;
    }

    root2->left = Merge(root1, root2->left);
    return root2;
}

pair <Node*, Node*> Split(Node* tree, elem_t x) {
    if (tree == NULL) {
        return {NULL, NULL};
    }

    pair <Node*, Node*> tmp;

    if (tree->key <= x) {
        tmp = Split(tree->right, x);
        tree->right = tmp.first;

        return {tree, tmp.second};
    }

    tmp = Split(tree->left, x);
    tree->left = tmp.second;

    return {tmp.first, tree};
}

Node* insert(Node* tree, elem_t key) {
    pair <Node*, Node*> P = Split(tree, key);
    Node* new_node = make_node(key);

    return Merge(P.first, Merge(new_node, P.second));
}

Node* erase(Node* tree, elem_t key) {
    pair <Node*, Node*> P = Split(tree, key);
    pair <Node*, Node*> D = Split(P.first, key-1);

    // Если ключи уникальные и целочисленные
    if (D.second != NULL) {
        delete D.second;
    }

    return Merge(D.first, P.second);
}


void print_tree (Node* root) {
    if (root == NULL) return;

    cout << root->key << ' ';
    print_tree(root->left);
    print_tree(root->right);
}

void print_lvl_tree (Node* root) {
    int i = 0;
    while (print_slice(root, i++) != 0) {cout << endl;}
    cout << endl;
    return;
}

int print_slice (Node* root, int lvl) {
    if (root == NULL) return 0;
    if (lvl == 0) {
        cout << "(" << root->key << ',' << root->prior << ") ";
        return 1;
    }

    return print_slice(root->left, lvl - 1) + print_slice(root->right, lvl - 1);
}