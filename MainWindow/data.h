#pragma once
#ifndef params_H
#define params_H
#include<math.h>
#include <string>
using namespace std;

enum Errors{
    OK,
    ValueExceded,
    NumberSystemEerror,
    SmallError

};

struct AppContext{
    char* num;
    int notationIn;
    int notationOut;
};

struct AppParams{
    char* filePath;
    char* binaryNum;
    char* otherNum;
    long int decimalNum;
    long int const memSize=4;
    char* val;
    int error;
};
    long int decToBin(AppParams* params);
    long int checkNum(AppParams* params, long int num);
    long int binToOther(AppParams* params, int notation);
    long int otherToBin(AppParams* params, int notation);
    int binToDec(AppParams* params);
    int checkNumBin(AppParams* params, char* num);

    //Data();
    long int setDecNum(AppParams* params, long int num);
    char* getDecNum(AppParams* params);
    int setNum(AppParams* params, long int num);
    int setNum(AppParams* params, AppContext* notation);
    char* getBin(AppParams* params);
    char* getDec(AppParams* params);
    char* getOther(AppParams* params);
    char* getNum(AppParams* params, int notation);

    char* unsignedFromDec(long long int num, int notation);
/*
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
    params();
    long int setDecNum(long int num);
    string getDecNum();
    long int setNum(long int num);
    long int setNum(string num, Newparams* notation);
    string getBin();
    string getDec();
    string getOther();
    string getNum(int notation);
};
*/
#endif // params_H
