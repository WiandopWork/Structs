#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

#define elem_t int
#define NaV -2e9

struct Node {
    elem_t val;
    Node *left, *right, *parent;
};

struct Heap_tree {
    Node* root;
    int size;
};

void Swap (elem_t &, elem_t &);
Node* make_node (elem_t);
void init_Heap_tree (Heap_tree &);
elem_t max_elem (Heap_tree &);
void insert (Heap_tree &, elem_t);
void pop (Heap_tree &);
void print_tree (Node*);
void print_lvl_tree (Node*);
int print_slice (Node*, int);

int main() {
    Heap_tree A;
    init_Heap_tree(A);
    insert(A, 100);
    print_tree(A.root);
    cout << endl;
    cout << endl;

    insert(A, 50);
    print_tree(A.root);
    cout << endl;
    cout << endl;

    insert(A, 40);
    print_tree(A.root);
    cout << endl;
    cout << endl;

    insert(A, 3);
    print_tree(A.root);
    cout << endl;
    cout << endl;

    insert(A, 20);
    print_tree(A.root);
    cout << endl;
    cout << endl;

    pop(A);
    print_tree(A.root);
    cout << endl;
    cout << endl;

    insert(A, 200);
    print_tree(A.root);
    cout << endl;
    cout << endl;
    return 0;
}

Node* make_node (elem_t key) {
    Node* ans = new Node;
    ans->val = key;
    ans->left = ans->right = ans->parent = NULL;
    return ans;
}

void init_Heap_tree (Heap_tree &tree) {
    tree.root = NULL;
    tree.size = 0;
}

elem_t max_elem (Heap_tree &tree) {
    if (tree.size == 0) return NaV;
    return tree.root->val;
}

void insert (Heap_tree &tree, elem_t key) {
    if (tree.size == 0) {
        tree.root = make_node(key);
        tree.size++;
        return;
    }

    Node* pred_ok = NULL;
    bool dir_is_left;
    Node* runner = tree.root;

    while (runner != NULL) {
        if (runner->val < key) {
            Swap(runner->val, key);
        } else {
            int coin = rand() % 2;
            pred_ok = runner;

            if (coin) {
                runner = runner->left;
                dir_is_left = true;
            } else {
                runner = runner->right;
                dir_is_left = false;
            }
        }
    }

    runner = make_node(key);
    if (dir_is_left) {
        pred_ok->left = runner;
    } else {
        pred_ok->right = runner;
    }

    runner->parent = pred_ok;
    tree.size++;
    return;
}

void pop (Heap_tree &tree) {
    if (tree.size == 0) {
        cerr << "Tree is empty, you fool!" << endl;
        return;
    }

    Node* runner = tree.root;
    bool work_with_left;

    while (runner->left || runner->right) {
        if (runner->left && runner->right) { // Два сына
            work_with_left = (runner->left->val > runner->right->val);
        } else { // Один сын
            work_with_left = runner->left;
        }

        if (work_with_left) {
            Swap(runner->val, runner->left->val);
            runner = runner->left;
        } else {
            Swap(runner->val, runner->right->val);
            runner = runner->right;
        }
    }

    if (work_with_left) {
        runner->parent->left = NULL;
    } else {
        runner->parent->right = NULL;
    }

    delete runner;
    return;
}

void print_tree (Node* root) {
    if (root == NULL) return;

    cout << root->val << ' ';
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
        cout << root->val << ' ';
        return 1;
    }

    return print_slice(root->left, lvl - 1) + print_slice(root->right, lvl - 1);
}

void Swap (elem_t &x, elem_t &y) {
    elem_t tmp = x;
    x = y;
    y = tmp;
}