/*
 * Name       : husnain ali
 * Reg No     : L1S26BSCS0152
 * Assignment : 02 - File Handling
 * Question   : Q1 - Stock Report (Debugging)
 */

 
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

int main() {
    char path[100];

    cout << "Enter the file name: ";
    cin.getline(path, 100);

    ifstream inFile(path);

    if (!inFile.is_open()) {
        cout << "Could not open " << path << "!" << endl;
        return 1;
    }

    int n;
    inFile >> n;

    if (n > 30) {
        cout << "Too many students!" << endl;
        inFile.close();
        return 1;
    }

    inFile.ignore(100, '\n');

    ofstream outFile("scholarship.txt");

    char name[30], topName[30] = "";
    double cgpa, total = 0, topCGPA = -1;
    int count = 0, eligible = 0;

    for (int i = 0; i < n; i++) {
        if (!inFile.getline(name, 30, ',')) {
            break;
        }

        if (!(inFile >> cgpa)) {
            break;
        }

        inFile.ignore(100, '\n');

        cout << "[" << name << "] CGPA: " << cgpa << endl;

        count++;
        total += cgpa;

        if (cgpa >= 3.50) {
            outFile << name << "," << cgpa << endl;
            eligible++;
        }

        if (cgpa > topCGPA) {
            topCGPA = cgpa;
            strcpy(topName, name);
        }
    }

    inFile.close();
    outFile.close();

    if (count < n) {
        cout << "Warning: only " << count << " of " << n
             << " records found." << endl;
    }

    if (count == 0) {
        cout << "No students found!" << endl;
        return 0;
    }

    cout << "Students: " << count << endl;
    cout << "Average CGPA: " << total / count << endl;
    cout << "Eligible for scholarship: " << eligible << endl;
    cout << "Top student: " << topName << " (" << topCGPA << ")" << endl;

    return 0;
}
