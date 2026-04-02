#ifndef OOP1_H
#define OOP1_H

struct Money {
    int grn;     
    short int kop; 
};

void addPayment(Money& total, Money bonus);
void scaleMoney(Money& item, int count);
void roundToNbu(Money& money);
void printMoney(const Money& money);
void processFile(const char* fileName);

#endif