#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

#define elem_t int
#define NaV -2e9

struct Node {
    elem_t val;
    Node* next;
};

struct BucketHT {
    int bucket_count;
    Node** bucket;
    int size;
};

int hash_f(elem_t, int);
Node* make_node(elem_t);
void init(BucketHT &, int b_count = 10007);
void insert(BucketHT &, elem_t);
Node* find(BucketHT &, elem_t);
void erase(BucketHT &, elem_t, bool del_all = false);
void print_table(BucketHT &);

int main() {
    BucketHT table;
    init (table, 11);
    for (int i = 0; i < 40; i++) {
        insert(table, i);
    }

    print_table(table);
    return 0;
}

int hash_f(elem_t key, int mod) {
    return key % mod; // Работает для int

    /* Работает для string & mas
     * int ans = 0;
     * int pow = 1;
     * for (int i = 0; i < key.size; i++) {
     *      ans += (key[i] * pow) % mod;
     *      ans %= mod;
     *      pow = (pow * 2) % mod;
     * }
     *
     * return ans;
    */
}

Node* make_node(elem_t key) {
    Node* answer = new Node;
    answer->val = key;
    answer->next = NULL;

    return answer;
}

void init(BucketHT &table, int b_count) {
    table.bucket_count = b_count;
    table.size = 0;
    table.bucket = new Node* [b_count];

    for (int i = 0; i < b_count; i++) {
        table.bucket[i] = NULL;
    }

    return;
}

void insert(BucketHT &table, elem_t key) {
    int bucket_num = hash_f(key, table.bucket_count);
    Node* new_node = make_node(key);

    new_node->next = table.bucket[bucket_num];
    table.bucket[bucket_num] = new_node;
    table.size++;

    return;
}

Node* find(BucketHT &table, elem_t key) {
    int bucket_num = hash_f(key, table.bucket_count);
    Node* runner = table.bucket[bucket_num];

    while (runner) {
        if (runner->val == key) {
            return runner;
        }

        runner = runner->next;
    }

    return NULL;
}

void erase(BucketHT &table, elem_t key, bool del_all) {
    int bucket_num = hash_f(key, table.bucket_count);
    Node* runner = table.bucket[bucket_num];
    Node* prev = NULL;

    while (runner) {
        if (runner->val == key) {
            if (!prev) { // Удаляется первый узел в корзине
                table.bucket[bucket_num] = runner->next;
                delete runner;
                table.size--;

                if (!del_all) {
                    return;
                }

                runner = table.bucket[bucket_num];
                prev = NULL;
            } else {
                prev->next = runner->next;
                delete runner;
                table.size--;

                if (!del_all) {
                    return;
                }

                runner = prev->next;
            }

            continue;
        }

        prev = runner;
        runner = runner->next;
    }

    return;
}

void print_table(BucketHT &table) {
    for (int i = 0; i < table.bucket_count; i++) {
        if (table.bucket[i]) {
            cout << i << "  ";
            Node* runner = table.bucket[i];

            while (runner) {
                cout << runner->val << " ";
                runner = runner->next;
            }

            cout << endl;
        }
    }

    return;
}