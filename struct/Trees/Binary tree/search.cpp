#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

#define elem_t int
#define NaV -2e9

struct Node {
    elem_t val;
    Node *left, *right;
    int h;
};

struct BS_tree {
    Node* root;
};

void Swap (elem_t &, elem_t &);
Node* make_node (elem_t);
void init_BS_tree (BS_tree &);
Node* insert (Node*, elem_t);
void insert (BS_tree &, elem_t);
Node* find (Node*, elem_t);
Node* find (BS_tree &, elem_t);
Node* erase (Node*, elem_t);
void erase (BS_tree &, elem_t);
void pop (BS_tree &);
void print_tree (Node*);
void print_lvl_tree (Node*);
int print_slice (Node*, int);
Node* max (Node*);
Node* min (Node*);
int height (Node*);
Node* fix_height (Node*);

int main() {
    BS_tree A;
    init_BS_tree(A);

    insert(A, 5);
    print_tree(A.root);
    cout << endl;
    insert(A, 3);
    print_tree(A.root);
    cout << endl;
    insert(A, 10);
    print_tree(A.root);
    cout << endl;
    insert(A, 15);
    print_tree(A.root);
    return 0;
}

Node* make_node (elem_t key) {
    Node* ans = new Node;
    ans->val = key;
    ans->left = ans->right = NULL;
    ans->h = 1;
    return ans;
}

void init_BS_tree (BS_tree &tree) {
    tree.root = NULL;
    return;
}

Node* insert (Node* point, elem_t key) {
    if (!point) return make_node(key); // if (point == NULL)

    if (point->val == key) {
        cout << "Repeated element" << endl;
        return fix_height(point);
    }

    if (point->val > key) { // Ключ должен быть слева
        point->left = insert(point->left, key);
    } else if (point->val < key) {  // Ключ должен быть справа
        point->right = insert(point->right, key);
    }

    return fix_height(point);
}

void insert (BS_tree &tree, elem_t key) {
    tree.root = insert(tree.root, key);
    return;
}

Node* find (Node* point, elem_t key) {
    if (!point) return NULL; // if (point == NULL)

    if (point->val == key) {
        return point;
    }

    if (point->val > key) { // Ключ должен быть слева
        return find(point->left, key);
    }
    // Ключ должен быть справа
    return find(point->right, key);
}

Node* find (BS_tree &tree, elem_t key) {
    return find(tree.root, key);
}

Node* erase (Node* point, elem_t key) {
    if (!point) return NULL; // if (point == NULL)

    if (point->val == key) {
        if (!(point->left) && !(point->right)) { // point - лист
            delete point;
            return NULL;
        }

        if (!(point->right)) { // Справа пусто
            Node* tmp = point->left;
            delete point;
            return fix_height(tmp);
        }

        Node* minmax = min(point->right);
        point->val = minmax->val;
        point->right = erase(point->right, minmax->val);
        return fix_height(point);
    }

    if (point->val > key) { // Ключ должен быть слева
        point->left = erase(point->left, key);
    } else if (point->val < key) {  // Ключ должен быть справа
        point->right = erase(point->right, key);
    }

    return fix_height(point);
}

void erase (BS_tree &tree, elem_t key) {
    tree.root = erase(tree.root, key);
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

Node* max (Node* point) {
    if (point == NULL) return NULL;
    if (point->right == NULL) return point;
    return max(point->right);
}

Node* min (Node* point) {
    if (point == NULL) return NULL;
    if (point->left == NULL) return point;
    return min(point->left);
}

int height (Node* point) {
    if (point) return point->h;
    else return 0;
}

Node* fix_height (Node* point) {
    if (!point) return NULL;

    point->h = max(height(point->left), height(point->right)) + 1;
    return point;
}

void Swap (elem_t &x, elem_t &y) {
    elem_t tmp = x;
    x = y;
    y = tmp;
}