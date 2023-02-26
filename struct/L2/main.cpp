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
Node* get_by_index(L2 &, int); // O(n)
void push_by_index(L2 &, int, int); // O(n)

void pop_front(L2 &); // O(1)
void pop_by_index(L2 &, int); // O(n)
void pop_back(L2 &); // thetta(n)

void print_L2(L2 &); // O(n)

int main() {
    L2 list;
    init(list);

    string str;
    int buf = 0;

    //while (true) {
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
   // }
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
        cerr << "Try to get value an empty list" << endl;
        return 2e9;
    }

    return list.head->val;
}

int back(L2 &list) {
    if (list.size == 0) {
        cerr << "Try to get value an empty list" << endl;
        return 2e9;
    }

    return list.tail->val;
}

void push_front(L2 &list, int key) {
    Node* new_node = make_node(key);
    new_node->next = list.head;
    list.head = new_node;

    if (list.size == 0) {
        list.tail = new_node;
    }

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

Node* get_by_index(L2 &list, int index) {
    if (index < 0 || index >= list.size) return NULL;
    if (index == list.size - 1) return list.tail;

    Node* runner = list.head;
    for (int i = 0; i < index; i++) runner = runner->next;

    return runner;
}

void push_by_index(L2 &list, int index, int key) {
    if (index == 0) {
        push_front(list, key);
        return;
    }

    if (index == list.size) {
        push_back(list, key);
        return;
    }

    Node* p, * q;
    p = get_by_index(list, index - 1);
    q = p->next;

    Node* new_node = make_node(key);
    new_node->next = q;
    new_node->last = p;
    q->last = new_node;
    p->next = new_node;

    list.size++;

    return;
}

void pop_front(L2 &list) {
    if (list.size == 0) {
        cerr << "Try to pop_front from an empty list" << endl;
        return;
    }

    Node* tmp = list.head;
    list.head = list.head->next;
    list.head->last = NULL;
    delete tmp;

    if (list.size == 1) {
        list.tail = NULL;
    }

    list.size--;

    return;
}

void pop_by_index(L2 &list, int index) {
    if (list.size == 0) {
        cerr << "Try to pop_by_index from an empty list" << endl;
        return;
    }

    if (index < 0 || index >= list.size) {
        cerr << "Bad index of pop_by_index" << endl;
        return;
    }

    if (list.size == 1 || index == 0) {
        pop_front(list);
        return;
    }


    Node* p, *q, *tmp;
    p = get_by_index(list, index - 1);
    tmp = p->next;
    q = tmp->next;
    p->next = q;
    q->last = p;
    delete tmp;

    if (index == list.size - 1) {
        list.tail = p;
    }

    list.size--;

    return;
}

void pop_back(L2 &list) {
    if (list.size == 0) {
        cerr << "Try to pop_back from an empty list" << endl;
        return;
    }

    if (list.size == 1) {
        pop_front(list);
        return;
    }

    Node* tmp;
    tmp = list.tail;
    list.tail = tmp->last;
    delete(tmp);
    list.tail->next = NULL;

    list.size--;

    return;
}

void print_L2(L2 & list) {
    Node* runner = list.head;
    for (int i = 0; i < list.size; i++) {
        cout << runner->val << " <- -> ";
        runner = runner->next;
    }
    cout << "NULL" << endl;

    return;
}