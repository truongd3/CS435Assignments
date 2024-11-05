#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int COMPCOUNT; // To count key-comparisons

void SWAP(int A[], int i, int j) {
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

int COMPARE(int X, int Y) {
    COMPCOUNT++; // Increase key-comparisons count
    if (X < Y) return -1;
    else if (X == Y) return 0;
    else return 1;
}

void printArray(int A[], int n) {
    for (int i = 0; i < n; i++) cout << A[i] << " ";
    cout << endl;
}

void Merge(int A[], int m, int B[], int n, int C[]) {
    int i = 0, j = 0, k = 0; // Index into A, B, C

    while (m >= i + 1 && n >= j + 1) {
        if (COMPARE(A[i], B[j]) < 1) { // A[i] <= B[j]
            C[k] = A[i];
            i++;
        } else {
            C[k] = B[j];
            j++;
        }
        k++;
    }

    while (m >= i + 1) { // empty remaining of array A
        C[k] = A[i];
        i++;
        k++;
    }
    while (n >= j + 1) {
        C[k] = B[j];
        j++;
        k++;
    }
}

void mergeSort(int A[], int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(A, left, mid);
    mergeSort(A, mid + 1, right);

    int *leftArr = A + left; // Beginning of left half
    int leftSize = mid - left + 1;

    int *rightArr = A + mid + 1; // Beginning of right half
    int rightSize = right - mid;

    int C[right - left + 1];
    Merge(leftArr, leftSize, rightArr, rightSize, C);

    for (int i = 0; i < right - left + 1; i++) A[left + i] = C[i];
}

void PushDown(int A[], int n, int r) { // For HEAPSORT
    int largest = r; // Find idx of largest of subtree

    if (2*r + 1 >= n) return; // already a leaf

    if (2*r + 1 < n && COMPARE(A[2*r + 1], A[largest]) == 1) largest = 2*r + 1; // A[2*r + 1] > A[largest]
    if (2*r + 2 < n && COMPARE(A[2*r + 2], A[largest]) == 1) largest = 2*r + 2; // A[2*r + 2] > A[largest]

    if (largest != r) {
        SWAP(A, r, largest);
        PushDown(A, n, largest);
    }
}

void BuildHeap(int A[], int n) { // For HEAPSORT
    for (int i = n/2 - 1; i >= 0; i--) PushDown(A, n, i);
}

void Insert(int A[], int& n, int newkey) { // For HEAPSORT
    n++;
    A[n - 1] = newkey;
    int p = n - 1;
    int parent = (p - 1) / 2;
    while (p > 0 && A[p] < A[parent]) {
        SWAP(A, p, parent);
        p = parent;
        parent = (p - 1) / 2;
    }
}

int DeleteMin(int A[], int& n) { // For HEAPSORT
    int temp = A[0];
    A[0] = A[n - 1];
    n--;
    PushDown(A, n, 0);
    return temp;
}

void heapSort(int A[], int n) { // For HEAPSORT
    BuildHeap(A, n);
    for (int i = n - 1; i >= 1; i--) {
        SWAP(A, 0, i);
        PushDown(A, i, 0);
    }
}

void quickSort (int A[], int left, int right) { //Left and Right indices
    if (left >= right) return;
    int k = left + rand() % (right - left + 1); // Pick random index between left and right
    int V = A[k]; // Get pivot
    SWAP(A, left, k); // Put pivot in leftmost spot

    int l = left + 1, r = right;
    while (l <= r) { //Continue scan if pointers have not crossed
        while (l <= r && COMPARE(A[l], V) < 1) l = l + 1; // Advance left-to-right scan
        while (l <= r && COMPARE(A[r], V) == 1) r = r - 1; // Advance right-to-left scan
        if (l < r) { // swap if the pair of pointers did not cross
            SWAP(A, l, r);
            l = l + 1;
            r = r - 1;
        }
    }

    SWAP(A, left, r);
    quickSort(A, left, r - 1);
    quickSort(A, r + 1, right);
}

int main() {
    cout << "1. SMALL-SIZE ARRAY, n = 32" << endl;
    int n = 32;
    int A[n];

    int* random_array = new int[n];
    srand(time(0));
    for (int i = 0; i < n; i++) random_array[i] = rand() % 100 + 1;

    cout << "A. Mergesort Algorithm" << endl;
    // (1) Sorted data
    for (int i = 0; i < n; i++) A[i] = i + 1;
    cout << "Sorted input array: ";
    printArray(A, n);
    auto start = high_resolution_clock::now();
    mergeSort(A, 0, n - 1);
    auto stop = high_resolution_clock::now();
    cout << "Output (sorted) array: ";
    printArray(A, n);
    cout << "Number of key-comparisons: " << COMPCOUNT << endl;
    cout << "Time spent on sorting: " << duration_cast<microseconds>(stop - start).count() << " (microseconds)" << endl;
    cout << endl;
    COMPCOUNT = 0;

    // (2) Reverse sorted data
    for (int i = 0; i < n; i++) A[i] = n - i;
    cout << "Reverse sorted input array: ";
    printArray(A, n);
    start = high_resolution_clock::now();
    mergeSort(A, 0, n - 1);
    stop = high_resolution_clock::now();
    cout << "Output (sorted) array: ";
    printArray(A, n);
    cout << "Number of key-comparisons: " << COMPCOUNT << endl;
    cout << "Time spent on sorting: " << duration_cast<microseconds>(stop - start).count() << " (microseconds)" << endl;
    cout << endl;
    COMPCOUNT = 0;

    // (3) Random generated data
    for (int i = 0; i < n; i++) A[i] = random_array[i];
    cout << "Random generated input array: ";
    printArray(A, n);
    start = high_resolution_clock::now();
    mergeSort(A, 0, n - 1);
    stop = high_resolution_clock::now();
    cout << "Output (sorted) array: ";
    printArray(A, n);
    cout << "Number of key comparisons: " << COMPCOUNT << endl;
    cout << "Time spent on sorting: " << duration_cast<microseconds>(stop - start).count() << " (microseconds)" << endl;
    cout << "----------------------------------------" << endl;
    COMPCOUNT = 0;

    cout << "\nB. Heapsort Algorithm" << endl;
    // // (1) Sorted data
    for (int i = 0; i < n; i++) A[i] = i + 1;
    cout << "Sorted input array: ";
    printArray(A, n);
    start = high_resolution_clock::now();
    heapSort(A, n);
    stop = high_resolution_clock::now();
    cout << "Output (sorted) array: ";
    printArray(A, n);
    cout << "Number of key-comparisons: " << COMPCOUNT << endl;
    cout << "Time spent on sorting: " << duration_cast<microseconds>(stop - start).count() << " (microseconds)" << endl;
    cout << endl;
    COMPCOUNT = 0;

    // (2) Reverse sorted data
    for (int i = 0; i < n; i++) A[i] = n - i;
    cout << "Reverse sorted input array: ";
    printArray(A, n);
    start = high_resolution_clock::now();
    heapSort(A, n);
    stop = high_resolution_clock::now();
    cout << "Output (sorted) array: ";
    printArray(A, n);
    cout << "Number of key-comparisons: " << COMPCOUNT << endl;
    cout << "Time spent on sorting: " << duration_cast<microseconds>(stop - start).count() << " (microseconds)" << endl;
    cout << endl;
    COMPCOUNT = 0;

    // (3) Random generated data
    for (int i = 0; i < n; i++) A[i] = random_array[i];
    cout << "Random generated input array: "; printArray(A, n);
    start = high_resolution_clock::now();
    heapSort(A, n);
    stop = high_resolution_clock::now();
    cout << "Output (sorted) array: "; printArray(A, n);
    cout << "Number of key comparisons: " << COMPCOUNT << endl;
    cout << "Time spent on sorting: " << duration_cast<microseconds>(stop - start).count() << " (microseconds)" << endl;
    cout << "----------------------------------------" << endl;
    COMPCOUNT = 0;

    cout << "\nC. Quicksort Algorithm" << endl;
    // (1) Sorted data
    for (int i = 0; i < n; i++) A[i] = i + 1;
    cout << "Sorted input array: "; printArray(A, n);
    start = high_resolution_clock::now();
    quickSort(A, 0, n - 1);
    stop = high_resolution_clock::now();
    cout << "Output (sorted) array: "; printArray(A, n);
    cout << "Number of key-comparisons: " << COMPCOUNT << endl;
    cout << "Time spent on sorting: " << duration_cast<microseconds>(stop - start).count() << " (microseconds)" << endl;
    cout << endl;
    COMPCOUNT = 0;

    // (2) Reverse sorted data
    for (int i = 0; i < n; i++) A[i] = n - i;
    cout << "Reverse sorted input array: "; printArray(A, n);
    start = high_resolution_clock::now();
    quickSort(A, 0, n - 1);
    stop = high_resolution_clock::now();
    cout << "Output (sorted) array: "; printArray(A, n);
    cout << "Number of key-comparisons: " << COMPCOUNT << endl;
    cout << "Time spent on sorting: " << duration_cast<microseconds>(stop - start).count() << " (microseconds)" << endl;
    cout << endl;
    COMPCOUNT = 0;

    // (3) Random generated data
    for (int i = 0; i < n; i++) A[i] = random_array[i];
    cout << "Random generated input array: "; printArray(A, n);
    start = high_resolution_clock::now();
    quickSort(A, 0, n - 1);
    stop = high_resolution_clock::now();
    cout << "Output (sorted) array: "; printArray(A, n);
    cout << "Number of key comparisons: " << COMPCOUNT << endl;
    cout << "Time spent on sorting: " << duration_cast<microseconds>(stop - start).count() << " (microseconds)" << endl;
    cout << "***********************************************************\n" << endl;
    COMPCOUNT = 0;


    cout << "\n2. INCREASING ARRAY SIZES, n = 2^10, n = 2^15, n = 2^20" << endl;
    n = 1024;
    cout << "*) Case n = 2^10" << endl;
    int* original_array = new int[n]; 
    for (int i = 0; i < n; i++) original_array[i] = rand() % 10000 + 1;
    int* B = new int[n];

    cout << "A. Mergesort Algorithm" << endl;
    for (int i = 0; i < n; i++) B[i] = original_array[i];
    start = high_resolution_clock::now();
    mergeSort(B, 0, n - 1);
    stop = high_resolution_clock::now();
    cout << "Number of key comparisons: " << COMPCOUNT << endl;
    cout << "Time spent on sorting: " << duration_cast<microseconds>(stop - start).count() << " (microseconds)" << endl;
    cout << endl;
    COMPCOUNT = 0;

    cout << "\nB. Heapsort Algorithm" << endl;
    for (int i = 0; i < n; i++) B[i] = original_array[i];
    start = high_resolution_clock::now();
    heapSort(B, n);
    stop = high_resolution_clock::now();
    cout << "Number of key comparisons: " << COMPCOUNT << endl;
    cout << "Time spent on sorting: " << duration_cast<microseconds>(stop - start).count() << " (microseconds)" << endl;
    cout << endl;
    COMPCOUNT = 0;

    cout << "\nC. Quicksort Algorithm" << endl;
    for (int i = 0; i < n; i++) B[i] = original_array[i];
    start = high_resolution_clock::now();
    quickSort(B, 0, n - 1);
    stop = high_resolution_clock::now();
    cout << "Number of key comparisons: " << COMPCOUNT << endl;
    cout << "Time spent on sorting: " << duration_cast<microseconds>(stop - start).count() << " (microseconds)" << endl;
    cout << "----------------------------------------" << endl;
    COMPCOUNT = 0;

    delete[] original_array;
    delete[] B;

    n = 32768;
    cout << "\n*) Case n = 2^15" << endl;
    original_array = new int[n];
    for (int i = 0; i < n; i++) original_array[i] = rand() % 100000 + 1;
    B = new int[n];
    
    cout << "\nA. Mergesort Algorithm" << endl;
    for (int i = 0; i < n; i++) B[i] = original_array[i];
    start = high_resolution_clock::now();
    mergeSort(B, 0, n - 1);
    stop = high_resolution_clock::now();
    cout << "Number of key comparisons: " << COMPCOUNT << endl;
    cout << "Time spent on sorting: " << duration_cast<microseconds>(stop - start).count() << " (microseconds)" << endl;
    cout << endl;
    COMPCOUNT = 0;

    cout << "\nB. Heapsort Algorithm" << endl;
    for (int i = 0; i < n; i++) B[i] = original_array[i];
    start = high_resolution_clock::now();
    heapSort(B, n);
    stop = high_resolution_clock::now();
    cout << "Number of key comparisons: " << COMPCOUNT << endl;
    cout << "Time spent on sorting: " << duration_cast<microseconds>(stop - start).count() << " (microseconds)" << endl;
    cout << endl;
    COMPCOUNT = 0;

    cout << "\nC. Quicksort Algorithm" << endl;
    for (int i = 0; i < n; i++) B[i] = original_array[i];
    start = high_resolution_clock::now();
    quickSort(B, 0, n - 1);
    stop = high_resolution_clock::now();
    cout << "Number of key comparisons: " << COMPCOUNT << endl;
    cout << "Time spent on sorting: " << duration_cast<microseconds>(stop - start).count() << " (microseconds)" << endl;
    cout << "------------------------------------------" << endl;
    COMPCOUNT = 0;

    delete[] original_array;
    delete[] B;

    n = 1048576;
    cout << "\n*) Case n = 2^20" << endl;
    original_array = new int[n];
    for (int i = 0; i < n; i++) original_array[i] = rand() % 10000 + 1;
    B = new int[n];

    cout << "A. Mergesort Algorithm" << endl;
    for (int i = 0; i < n; i++) B[i] = original_array[i];
    start = high_resolution_clock::now();
    mergeSort(B, 0, n - 1);
    stop = high_resolution_clock::now();
    cout << "Number of key comparisons: " << COMPCOUNT << endl;
    cout << "Time spent on sorting: " << duration_cast<microseconds>(stop - start).count() << " (microseconds)" << endl;
    cout << endl;
    COMPCOUNT = 0;

    cout << "\nB. Heapsort Algorithm" << endl;
    for (int i = 0; i < n; i++) B[i] = original_array[i];
    start = high_resolution_clock::now();
    heapSort(B, n);
    stop = high_resolution_clock::now();
    cout << "Number of key comparisons: " << COMPCOUNT << endl;
    cout << "Time spent on sorting: " << duration_cast<microseconds>(stop - start).count() << " (microseconds)" << endl;
    cout << endl;
    COMPCOUNT = 0;

    cout << "\nC. Quicksort Algorithm" << endl;
    for (int i = 0; i < n; i++) B[i] = original_array[i];
    start = high_resolution_clock::now();
    quickSort(B, 0, n - 1);
    stop = high_resolution_clock::now();
    cout << "Number of key comparisons: " << COMPCOUNT << endl;
    cout << "Time spent on sorting: " << duration_cast<microseconds>(stop - start).count() << " (microseconds)" << endl;
    COMPCOUNT = 0;

    delete[] original_array;
    delete[] B;
    
    return 0;
}