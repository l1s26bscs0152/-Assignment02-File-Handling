/*
 * Name       : husnain ali
 * Reg No     : L1S26BSCS0152
 * Assignment : 02 - File Handling
 * Question   : Q1 - Stock Report (Debugging)
 */


#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    ifstream inFile("parking.txt");

    if (!inFile) {
        cout << "parking.txt not found!" << endl;
        return 1;
    }

    int d, m, y;
    char slash;

    inFile >> d >> slash >> m >> slash >> y;
    inFile.ignore(100, '\n');
    inFile.ignore(100, '\n');

    ofstream outFile("receipts.txt");

    cout << "Parking report for " << d << "/" << m << "/" << y << endl;
    outFile << "Receipts for " << d << "/" << m << "/" << y << endl;

    char plate[15], longestPlate[15] = "";
    char type;
    int inHour, inMin, outHour, outMin;
    int vehicles = 0, cars = 0, bikes = 0;
    int totalCollected = 0, longestMinutes = -1;

    while (vehicles < 30 &&
           inFile >> plate >> type
                  >> inHour >> slash >> inMin
                  >> outHour >> slash >> outMin) {

        int start = inHour * 60 + inMin;
        int end = outHour * 60 + outMin;
        int minutes = end - start;

        int hours = (minutes + 59) / 60;

        if (hours == 0) {
            hours = 1;
        }

        int rate;
        char vehicleType[5];

        if (type == 'C') {
            rate = 100;
            strcpy(vehicleType, "Car");
            cars++;
        } else {
            rate = 40;
            strcpy(vehicleType, "Bike");
            bikes++;
        }

        int fee = hours * rate;

        cout << plate << " " << vehicleType << " "
             << minutes / 60 << " h "
             << minutes % 60 << " min Fee: "
             << fee << endl;

        outFile << plate << " " << fee << endl;

        vehicles++;
        totalCollected += fee;

        if (minutes > longestMinutes) {
            longestMinutes = minutes;
            strcpy(longestPlate, plate);
        }
    }

    inFile.close();
    outFile.close();

    if (vehicles == 0) {
        cout << "No vehicles found!" << endl;
        return 0;
    }

    cout << "Vehicles: " << vehicles << endl;
    cout << "Cars: " << cars << " Bikes: " << bikes << endl;
    cout << "Total collected: " << totalCollected << endl;
    cout << "Longest stay: " << longestPlate << " ("
         << longestMinutes / 60 << " h "
         << longestMinutes % 60 << " min)" << endl;

    return 0;
}
