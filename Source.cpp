#include "Header.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void fixMoney(Money& m) {
    if (m.kop >= 100 || m.kop < 0) {
        m.grn += m.kop / 100;
        m.kop %= 100;
        if (m.kop < 0) {
            m.kop += 100;
            m.grn--;
        }
    }
}

void addPayment(Money& total, Money bonus) {
    total.grn += bonus.grn;
    total.kop += bonus.kop;
    fixMoney(total);
}

void scaleMoney(Money& item, int count) {
    long long allKop = (item.grn * 100LL + item.kop) * count;
    item.grn = (int)(allKop / 100);
    item.kop = (short int)(allKop % 100);
}

void roundToNbu(Money& money) {
    int last = money.kop % 10;
    
    if (last >= 1 && last <= 3) {
        money.kop -= last;
    } 
    else if (last >= 4 && last <= 9) {
        money.kop += (10 - last);
    }
    
    fixMoney(money);
}

void printMoney(const Money& money) {
    cout << money.grn << " grn. " 
         << setfill('0') << setw(2) << money.kop << " kop." << endl;
}

void processFile(const char* fileName) {
    FILE* f;
    if (fopen_s(&f, fileName, "r") != 0) {
        cout << "File not found: " << fileName << endl;
        return;
    }

    Money totalSum = { 0, 0 };
    char line[256];

    while (fgets(line, sizeof(line), f)) {
        char name[128];
        int g, q;
        short int k;

        if (sscanf_s(line, "%s %d %hd %d", name, (unsigned)_countof(name), &g, &k, &q) == 4) {
            if (g < 0 || k < 0 || q < 0) continue;

            Money current = { g, k };
            scaleMoney(current, q);
            addPayment(totalSum, current);
        }
    }

    cout << "========================================" << endl;
    cout << "Amount Without Rounding: ";
    printMoney(totalSum);

    roundToNbu(totalSum);

    cout << "Amount to pay: ";
    printMoney(totalSum);
    cout << "========================================" << endl;

    fclose(f);
}