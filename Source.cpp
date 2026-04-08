#include "Header.h"
#include <iostream>
#include <cstdio> 
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
    item.grn *= count;
    item.kop *= count; 
    fixMoney(item);    
}

void roundToNbu(Money& money) {
    int last = money.kop % 10;
    
    if (last >= 1 && last <= 4) {
        money.kop -= last;
    } 
    else if (last >= 5) {
        money.kop += (10 - last);
    }
    
    fixMoney(money);
}

void printMoney(const Money& money) {
    cout << money.grn << " grn. " << setw(2) << setfill('0') <<
          money.kop << " kop." << endl;
}

void processFile(const char* fileName) {
    FILE* f = fopen(fileName, "r"); 
    if (!f) {
        cout << "File not found!" << endl;
        return;
    }

    Money totalSum = { 0, 0 };
    char line[256];

    while (fgets(line, sizeof(line), f)) {
        char name[128];
        int g, q;
        short int k;

        if (sscanf(line, "%s %d %hd %d", name, &g, &k, &q) == 4) {
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