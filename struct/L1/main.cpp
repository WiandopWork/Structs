#include <iostream>
#include <cmath>
#include <set>
#include <fstream>

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

void init(L1 &); // O(1)
void reverse(L1 &);
Node* make_node(int); // O(1)

int front(L1 &); // O(1)
int back(L1 &); // O(1)

void push_front(L1 &, int); // O(1)
void push_back(L1 &, int); // O(1)
Node* get_by_index(L1 &, int); // O(n)
void push_by_index(L1 &, int, int); // O(n)

void pop_front(L1 &); // O(1)
void pop_by_index(L1 &, int); // O(n)
void pop_back(L1 &); // thetta(n)

void print_L1(L1 &); // O(n)

int main() {
    L1 list;
    init(list);

    for (int i = 1; i < 6; i++) {
        push_back(list, i);
    }

    print_L1(list);

    reverse(list);

    print_L1(list);

    return 0;
}

void reverse(L1 &list) {
    Node* cur = list.head;

    while (cur->next != NULL) {
        cur = cur->next;
    }

    cur->next = list.head;
    list.head = list.head->next;

    cur = cur->next;
    cur->next = NULL;

    print_L1(list);
    return;
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


void push_front(L1 &list, int key) {
    Node* new_node = make_node(key);
    new_node->next = list.head;
    list.head = new_node;

    if (list.size == 0) {
        list.tail = new_node;
    }

    list.size++;

    return;
}

void push_back(L1 &list, int key) {
    if (list.size == 0) {
        push_front(list, key);
        return;
    }

    Node* new_node = make_node(key);
    list.tail->next = new_node;
    list.tail = new_node;

    list.size++;

    return;
}

Node* get_by_index(L1 &list, int index) {
    if (index < 0 || index >= list.size) return NULL;
    if (index == list.size - 1) return list.tail;

    Node* runner = list.head;
    for (int i = 0; i < index; i++) runner = runner->next;

    return runner;
}

void push_by_index(L1 &list, int index, int key) {
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
    p->next = new_node;

    list.size++;

    return;
}

void pop_front(L1 &list) {
    if (list.size == 0) {
        cerr << "Try to pop_front from an empty list" << endl;
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

void pop_by_index(L1 &list, int index) {
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
    delete tmp;

    if (index == list.size - 1) {
        list.tail = p;
    }

    list.size--;

    return;
}

void pop_back(L1 &list) {
    if (list.size == 0) {
        cerr << "Try to pop_back from an empty list" << endl;
        return;
    }

    if (list.size == 1) {
        pop_front(list);
        return;
    }

    pop_by_index(list, list.size - 1);

    return;
}

void print_L1(L1 & list) {
    Node* runner = list.head;
    for (int i = 0; i < list.size; i++) {
        cout << runner->val << " -> ";
        runner = runner->next;
    }
    cout << "NULL" << endl;

    return;
}