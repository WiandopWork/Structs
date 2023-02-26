#include <iostream>
#include <cmath>
#include <set>
#include <fstream>
#include <string>

using namespace std;

struct Node {
    int val;
    Node* next;
};

struct L1 {
    Node* head;
    Node* tail;
    unsigned int size;
};

void init(L1 &);
Node* make_node(int);

int front(L1 &);

void push(L1 &, int);
void pop(L1 &);

int main() {
    L1 stack;
    init(stack);

    string str;
    int buf = 0;

    while (true) {
        cin >> str;

        if (str == "push") {
            cin >> buf;
            push(stack, buf);
            cout << "ok" << endl;

            continue;
        }

        if (str == "pop") {
            int buf = front(stack);

            if (buf != 2e9) {
                pop(stack);
                cout << buf << endl;
            }

            continue;
        }

        if (str == "back") {
            int buf = front(stack);
            if (buf != 2e9) {
                cout << buf << endl;
            }

            continue;
        }

        if (str == "size") {
            cout << stack.size << endl;

            continue;
        }

        if (str == "clear") {
            while (stack.size != 0) {
                pop(stack);
            }

            cout << "ok" << endl;

            continue;
        }

        if (str == "exit") {
            cout << "bye" << endl;
            return 0;
        }

    }

    return 0;
}

void init(L1 &list) {
    list.head = NULL;
    list.tail = NULL;
    list.size = 0;
    return;
}

Node* make_node(int key) {
    Node* p = new Node;
    p->val = key; // (*p).val = key;
    p->next = NULL;

    return p;
}

int front(L1 &list) {
    if (list.size == 0) {
        cout << "error" << endl;
        return 2e9;
    }

    return list.head->val;
}

void push(L1 &list, int key) {
    Node* new_node = make_node(key);
    new_node->next = list.head;
    list.head = new_node;

    if (list.size == 0) {
        list.tail = new_node;
    }

    list.size++;

    return;
}

void pop(L1 &list) {
    if (list.size == 0) {
        cout << "error" << endl;
        return;
    }

    Node* tmp = list.head;
    list.head = list.head->next;
    delete tmp;

    if (list.size == 1) {
        list.tail = NULL;
    }

    list.size--;

    return;
}