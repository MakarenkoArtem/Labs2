#ifndef DATA_H
#define DATA_H
#include<math.h>
#include <string>
using namespace std;

struct NewData{
    string num;
    int notationIn;
    int notationOut;
};

class Data{
private:
    string binaryNum, otherNum;
    long int decimalNum;
    long int const memSize=4;
    long int decToBin();
    long int checkNum(long int num);
    long int binToOther(int notation);
    long int otherToBin(int notation);
    long int binToDec();
    int checkNumBin(string num);
public:
    string val;
    string mes;
    Data();
    long int setDecNum(long int num);
    string getDecNum();
    long int setNum(long int num);
    long int setNum(string num, NewData* notation);
    string getBin();
    string getDec();
    string getOther();
    string getNum(int notation);
};

#endif // DATA_H
