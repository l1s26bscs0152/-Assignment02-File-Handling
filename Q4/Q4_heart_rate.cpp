/*
 * Name       : husnain ali
 * Reg No     : L1S26BSCS0152
 * Assignment : 02 - File Handling
 * Question   : Q1 - Stock Report (Debugging)
 */

 
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream inFile("heart_rate.txt");
    if (!inFile) {
        cout << "heart_rate.txt not found!" << endl;
        return 1;
    }

    int rate[100];
    int count = 0;      // number of valid readings stored in rate[]
    int bad = 0;        // number of junk words skipped
    int x;
    char junk[50];
    int reason = 0;     // 1 = sentinel found, 2 = end of file, 3 = array full

    while (true) {
        if (count >= 100) {          // (1) array is full
            reason = 3;
            break;
        }

        if (inFile >> x) {           // a number was read
            if (x == -1) {            // (2) sentinel value
                reason = 1;
                break;
            }

            rate[count] = x;
            count++;                  // (3) increment valid reading count
        }
        else if (inFile.eof()) {      // (4) nothing left in the file
            reason = 2;
            break;
        }
        else {                        // a junk word
            inFile.clear();           // (5) clear failed stream state
            inFile >> junk;
            bad++;
        }
    }

    inFile.close();

    // TODO 1: Write every valid reading to clean_heart_rate.txt.
    ofstream outFile("clean_heart_rate.txt");

    for (int i = 0; i < count; i++) {
        outFile << rate[i] << endl;
    }

    outFile.close();

    // TODO 2: Display the reading and junk counts.
    cout << "Valid readings: " << count << endl;
    cout << "Junk skipped: " << bad << endl;

    // TODO 3: Display statistics if valid readings exist.
    if (count == 0) {
        cout << "No valid readings!" << endl;
    }
    else {
        int total = 0;
        int highest = rate[0];
        int aboveAverage = 0;
        int alerts = 0;

        for (int i = 0; i < count; i++) {
            total += rate[i];

            if (rate[i] > highest) {
                highest = rate[i];
            }

            if (rate[i] > 100) {
                alerts++;
            }
        }

        double average = (double)total / count;

        for (int i = 0; i < count; i++) {
            if (rate[i] > average) {
                aboveAverage++;
            }
        }

        cout << "Average: " << average << endl;
        cout << "Highest: " << highest << endl;
        cout << "Above average: " << aboveAverage << endl;
        cout << "Alerts (above 100): " << alerts << endl;
    }

    // TODO 4: Display why reading stopped.
    cout << "Stopped because: ";

    if (reason == 1) {
        cout << "sentinel found";
    }
    else if (reason == 2) {
        cout << "end of file";
    }
    else if (reason == 3) {
        cout << "array full";
    }

    cout << endl;

    return 0;
}
