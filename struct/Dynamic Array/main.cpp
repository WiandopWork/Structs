#include <iostream>
#include <cmath>
#include <set>
#include <fstream>

using namespace std;

struct DynArray {
    int* mas;
    unsigned int size;
    unsigned int capacity;
};

void init(DynArray &, int n = 1);
void push_back(DynArray &, int);
int pop_back(DynArray &);
int find(DynArray &, int);

int main() {
    DynArray A,B;
    init(A);
    init(B,100);
    push_back(A,123);
    cout << A.capacity << endl;
    pop_back(A);
    cout << A.capacity << endl;
    return 0;
}

void init(DynArray &da, int n) {
    da.capacity = n;
    da.mas = new int[n];
    da.size = 0;
    return;
}

void push_back(DynArray &da, int key) {
    if (da.capacity == da.size) {
        int* new_mas = new int[da.capacity << 1]; // *2
        for (int i = 0; i < da.capacity; i++) {
            new_mas[i] = da.mas[i];
        }

        delete [] da.mas;
        da.mas = new_mas;
        da.capacity <<= 1;
    }

    da.mas[da.size] = key;
    da.size++;
    return;
}

int pop_back(DynArray &da) {
    if (da.size == 0) {
        cerr << "Attempt to pop_back empty array" << endl;
        return -2e8;
    }

    da.size--;

    if (da.size <= (da.capacity >> 2)) {
        int* new_mas = new int[da.capacity >> 1]; // /2
        for (int i = 0; i < da.size; i++) {
            new_mas[i] = da.mas[i];
        }

        delete [] da.mas;
        da.mas = new_mas;
        da.capacity >>= 1;
    }

    return da.mas[da.size];
}

int find(DynArray &da, int key) {
    for (int i = 0; i < da.size; i++) {
        if (da.mas[i] == key) {
            return i;
        }
    }
    return -1;
}