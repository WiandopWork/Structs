#include <iostream>
#include <cmath>
#include <set>
#include <fstream>
#include <string>

using namespace std;

struct Node {
    int val;
    Node* next;
    Node* last;
};

struct L2 {
    Node* head;
    Node* tail;
    unsigned int size;
};

void init(L2 &); // O(1)
Node* make_node(int); // O(1)

int front(L2 &); // O(1)
int back(L2 &); // O(1)

void push_front(L2 &, int); // O(1)
void push_back(L2 &, int); // O(1)

void pop_front(L2 &); // O(1)
void pop_back(L2 &); // thetta(n)

void print_L2(L2 &); // O(n)

int main() {
    L2 deck;
    init(deck);

    string str;
    int buf = 0;

    while (true) {
        cin >> str;

        if (str == "push_front") {
            cin >> buf;
            push_front(deck, buf);
            cout << "ok" << endl;

            continue;
        }

        if (str == "push_back") {
            cin >> buf;
            push_back(deck, buf);
            cout << "ok" << endl;

            continue;
        }

        if (str == "pop_front") {
            int buf = front(deck);

            if (buf != 2e9) {
                pop_front(deck);
                cout << buf << endl;
            }

            continue;
        }

        if (str == "pop_back") {
            int buf = back(deck);

            if (buf != 2e9) {
                pop_back(deck);
                cout << buf << endl;
            }

            continue;
        }

        if (str == "back") {
            int buf = back(deck);
            if (buf != 2e9) {
                cout << buf << endl;
            }

            continue;
        }

        if (str == "front") {
            int buf = front(deck);
            if (buf != 2e9) {
                cout << buf << endl;
            }

            continue;
        }

        if (str == "size") {
            cout << deck.size << endl;

            continue;
        }

        if (str == "clear") {
            while (deck.size != 0) {
                pop_front(deck);
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

void init(L2 &list) {
    list.head = NULL;
    list.tail = NULL;
    list.size = 0;
    return;
}

Node* make_node(int key) {
    Node* p = new Node;
    p->val = key; // (*p).val = key;
    p->next = NULL;
    p->last = NULL;

    return p;
}

int front(L2 &list) {
    if (list.size == 0) {
        cout << "error" << endl;
        return 2e9;
    }

    return list.head->val;
}

int back(L2 &list) {
    if (list.size == 0) {
        cout << "error" << endl;
        return 2e9;
    }

    return list.tail->val;
}

void push_front(L2 &list, int key) {
    Node* new_node = make_node(key);

    if (list.size == 0) {
        list.tail = new_node;
        list.head = new_node;
        list.size++;
        return;
    }

    new_node->next = list.head;
    list.head = new_node;
    list.head->next->last = list.head;

    list.size++;

    return;
}

void push_back(L2 &list, int key) {
    if (list.size == 0) {
        push_front(list, key);
        return;
    }

    Node* new_node = make_node(key);
    list.tail->next = new_node;
    new_node->last = list.tail;
    list.tail = new_node;

    list.size++;

    return;
}

void pop_front(L2 &list) {
    if (list.size == 0) {
        cout << "error" << endl;
        return;
    }

    if (list.size == 1) {
        list.tail = NULL;
        list.head = NULL;
        list.size = 0;
        return;
    }

    Node* tmp = list.head;
    list.head = tmp->next;

    list.head->last = NULL;
    delete tmp;

    list.size--;

    return;
}

void pop_back(L2 &list) {
    if (list.size == 0) {
        cout << "error" << endl;
        return;
    }

    if (list.size == 1) {
        pop_front(list);
        return;
    }

    Node* tmp;
    tmp = list.tail;
    list.tail = tmp->last;
    delete tmp;

    list.tail->next = NULL;
    list.size--;

    return;
}
