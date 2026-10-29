
/*
 * Name       : husnain ali
 * Reg No     : L1S26BSCS0152
 * Assignment : 02 - File Handling
 * Question   : Q1 - Stock Report (Debugging)
 */

#include <iostream>
// FIX 1: The fstream header is required for ifstream and ofstream.
#include <fstream>
using namespace std;

int main() {
    ifstream inFile("stock.txt");
    // FIX 2: The condition was reversed; report an error if the file fails to open.
    if (!inFile) {
        cout << "stock.txt not found!" << endl;
        return 1;
    }

    // FIX 3: App mode preserves existing contents and adds new entries at the end.
    ofstream reorder("reorder.txt", ios::app);

    char code[10];
    int qty, count = 0, low = 0;
    double price;
    // FIX 4: Use double to preserve decimal values in the total stock value.
    double total = 0;

    // FIX 5: Skip the first line because it contains the header, not an item.
    inFile.ignore(1000, '\n');

    while (count < 50 && inFile >> code >> qty >> price) {
        count++;
        total = total + qty * price;
        if (qty < 10) {
            // FIX 6: Add a newline after each item so every reorder entry is on its own line.
            reorder << code << " " << qty << '\n';
            low++;
        }
    }
    inFile.close();
    reorder.close();

    cout << "Items: " << count << endl;
    cout << "Total stock value: " << total << endl;
    cout << "Low stock items: " << low << endl;
    return 0;
}
