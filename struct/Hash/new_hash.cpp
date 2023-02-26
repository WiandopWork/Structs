#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

#define elem_t int
#define NaV -2e9

enum State { FREE, BUSY, DELETED };

struct Cell {
    elem_t val;
    State state;
    int iter_hash;
};

struct OpenHT {
    int capacity;
    int size;
    Cell* table;
};

int linear_hash(elem_t, int, int);
int quadratic_hash(elem_t, int, int);
void init(OpenHT &, int capacity = 1000003);
void insert(OpenHT &, elem_t);
int find(OpenHT &, elem_t);
void erase(OpenHT &, elem_t);
void print_table(OpenHT &);
void Swap(elem_t &, elem_t &);

int main() {
    OpenHT table;
    init(table, 11);

//    for (int i = 0; i < 7; i++) {
//        insert(table, i * i);
//    }
//
//    erase(table, 16);

    insert(table, 1);
    insert(table, 4);
    insert(table, 3);
    insert(table, 2);
    insert(table, 2);

    erase(table, 2);
    erase(table, 4);
    print_table(table);
    return 0;
}

int linear_hash(elem_t key, int iter, int mod) {
    return (key + iter) % mod;
}

void init(OpenHT &table, int capacity) {
    table.capacity = capacity;
    table.size = 0;
    table.table = new Cell[capacity];

    for (int i = 0; i < capacity; i++) {
        table.table[i].state = FREE;
        table.table[i].val = -1;
        table.table[i].iter_hash = 0;
    }

    return;
}

void insert(OpenHT &table, elem_t key) {
    if (table.size >= table.capacity) {
        //cout << "No capacity" << endl;
        return;
    }

    int i = 0;
    int hash = linear_hash(key, i, table.capacity);

    while (table.table[hash].state == BUSY) {
        hash = linear_hash(key, ++i, table.capacity);
    }

    table.table[hash].state = BUSY;
    table.table[hash].val = key;
    table.size++;
    table.table[hash].iter_hash = i;
}

int find(OpenHT &table, elem_t key) {
    int hash = linear_hash(key, 0, table.capacity);
    int i = 1;

    while (table.table[hash].state != FREE) {
        Cell cur = table.table[hash];

        if (cur.state == BUSY && cur.val == key) {
            return hash;
        }

        hash = linear_hash(key, i++, table.capacity);

        if (i > table.capacity) {
            break;
        }
    }

    return -1;
}

void erase(OpenHT &table, elem_t key) {
    int key_pos = find(table, key);
    if (key_pos == -1) {
        return;
    }

    int i = table.table[key_pos].iter_hash;
    int hash = linear_hash(key, i + 1, table.capacity);

    if (table.table[hash].state == FREE) {
        table.table[key_pos].state = FREE;
    } else {
        table.table[key_pos].state = DELETED;
    }

    return;
}

void print_table(OpenHT &table) {
    for (int i = 0; i < table.capacity; i++) {
        if (table.table[i].state == FREE) {
            cout << "FREE ";
        }

        if (table.table[i].state == BUSY) {
            cout << "BUSY ";
        }

        if (table.table[i].state == DELETED) {
            cout << "DELETED ";
        }

        cout << table.table[i].val << " " << table.table[i].iter_hash << endl;
    }
}

void Swap(elem_t &x, elem_t &y) {
    elem_t tmp = x;
    x = y;
    y = tmp;
    return;
}