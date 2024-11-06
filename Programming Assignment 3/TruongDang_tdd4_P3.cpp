#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void castString2Char(vector<char> &subS, string str) {
    for (int i = 0; i < str.size(); i++) subS[i] = str[i];
    for (int i = str.size(); i < subS.size(); i++) subS[i] = ' ';
}

string getString(vector<char> subS) {
    string res;
    for (int i = 0; i < subS.size() && subS[i] != ' '; i++) res += subS[i];
    return res;
}

void radixSort(vector<vector<char> > &S, int k, int n) {
    vector<int> charCounter(27); // Frequency count for characters blank, A-Z
    vector<string> output(n); // Temporary sorted S

    // Sort from Least Significant (k-1) to Most (0)
    for (int pos = k - 1; pos >= 0; pos--) {
        fill(charCounter.begin(), charCounter.end(), 0); // Reset frequency

        for (int i = 0; i < n; i++) {
            char ch = S[i][pos];
            if (ch != ' ') charCounter[ch - 'A' + 1]++;
            else charCounter[0]++;
        }

        // Cumulative frequencies
        for (int i = 1; i < 27; i++) charCounter[i] += charCounter[i - 1];

        // Arrange pointers based on cumulative counts
        for (int i = n - 1; i >= 0; i--) {
            char ch = S[i][pos];
            if (ch != ' ') {
                output[charCounter[ch - 'A' + 1] - 1] = getString(S[i]);
                charCounter[ch - 'A' + 1]--;
            } else {
                output[charCounter[0] - 1] = getString(S[i]);
                charCounter[0]--;
            }
        }

        // Update S with sorted order
        for (int i = 0; i < n; i++) castString2Char(S[i], output[i]);
    }
}

int main() {
    string inputFile = "f.txt", outputFile = "g.txt", temp;

    cout << "Please specify the input file (default = f.txt): ";
    getline(cin, temp);
    if (!temp.empty()) inputFile = temp;

    cout << "Please specify the output file (default = g.txt): ";
    getline(cin, temp);
    if (!temp.empty()) outputFile = temp;

    ifstream inFile(inputFile);
    if (!inFile) {
        cerr << "Error: Cannot open input file " << inputFile << endl;
        return 1;
    }

    int n = 0, k = 21;
    vector<vector<char> > S(1000, vector<char>(k, ' '));
    string line;
    while (getline(inFile, line)) {
        if (!line.empty()) {
            castString2Char(S[n], line);
            n++;
        }
    }
    inFile.close();

    radixSort(S, k, n);

    ofstream outFile(outputFile);
    if (!outFile) {
        cerr << "Error: Cannot open output file " << outputFile << endl;
        return 1;
    }

    for (int i = 0; i < n; i++) outFile << getString(S[i]) << endl;
    outFile.close();

    cout << "Sorting complete. Sorted data written to " << outputFile << endl;
    return 0;
}
