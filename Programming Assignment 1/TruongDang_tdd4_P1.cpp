#include <iostream>
using namespace std;

int COMPCOUNT; // To count key-comparisons

bool SMALLER(int A[], int i, int j) {
    COMPCOUNT++; // Increase key-comparisons count
    return A[i] < A[j];
}

void SWAP(int A[], int i, int j) {
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

void insertionSort(int A[], int n) {
    COMPCOUNT = 0; // Reset key-comparisons count
    for (int i = 1; i < n; i++) {
        int j = i - 1; // Start at index i going backwards, compare each adjacent pair of values
        while (j >= 0 && SMALLER(A, j + 1, j)) {
            SWAP(A, j, j + 1);
            j--;
        }
    }
}

void printArray(int A[], int n) {
    for (int i = 0; i < n; i++) cout << A[i] << " ";
    cout << endl;
}

int main() {
    // 1. Small-Size Array, n = 32
    cout << "1. SMALL-SIZE ARRAY, n = 32" << endl;
    int n = 32;
    int A[n];

    // (1) Worst-case data input: Reverse sorted array
    for (int i = 0; i < n; i++) A[i] = n - i;  // Populate array in decreasing order
    cout << "Worst-case input array: ";
    printArray(A, n);
    insertionSort(A, n);
    cout << "Output (sorted) array: ";
    printArray(A, n);
    cout << "Number of key-comparisons: " << COMPCOUNT << endl;
    cout << "------------------------------------------" << endl;

    // (2) Best-case data input: Already sorted array
    for (int i = 0; i < n; i++) A[i] = i + 1;  // Populate array in increasing order
    cout << "Best-case input array: ";
    printArray(A, n);
    insertionSort(A, n);
    cout << "Output (sorted) array: ";
    printArray(A, n);
    cout << "Number of key-comparisons: " << COMPCOUNT << endl;
    cout << "------------------------------------------" << endl;

    // (3) Average-case data input: Random array
    srand(time(0));  // Seed random number generator
    for (int i = 0; i < n; i++) A[i] = rand() % 100 + 1;  // Random values between 1 and 100
    cout << "Average-case input array: ";
    printArray(A, n);
    insertionSort(A, n);
    cout << "Output (sorted) array: ";
    printArray(A, n);
    cout << "Number of key comparisons: " << COMPCOUNT << endl;
    cout << "***********************************************************" << endl;

    // 2. Increasing Array Sizes, n = 100, n = 1000, n = 10000
    cout << "2. INCREASING ARRAY SIZES, n = 100, n = 1000, n = 10000" << endl;
    // (1) n = 100
    n = 100;
    int B[n];
    for (int i = 0; i < n; i++) B[i] = rand() % 10000 + 1;  // Random values between 1 and 10000
    cout << "Case n = " << n << endl;
    insertionSort(B, n);
    cout << "Number of key comparisons: " << COMPCOUNT << endl;
    cout << "------------------------------------------" << endl;

    // (2) n = 1000
    n = 1000;
    int C[n];
    for (int i = 0; i < n; i++) C[i] = rand() % 10000 + 1;  // Random values between 1 and 10000
    cout << "Case n = " << n << endl;
    insertionSort(C, n);
    cout << "Number of key comparisons: " << COMPCOUNT << endl;
    cout << "------------------------------------------" << endl;

    // (3) n = 10000
    n = 10000;
    int D[n];
    for (int i = 0; i < n; i++) D[i] = rand() % 10000 + 1;  // Random values between 1 and 10000
    cout << "Case n = " << n << endl;
    insertionSort(D, n);
    cout << "Number of key comparisons: " << COMPCOUNT << endl;
    cout << "***********************************************************" << endl;

    return 0;
}
