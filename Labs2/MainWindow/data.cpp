#include "data.h"
#include <libraries/mystring.h>
#include"QtDebug"
string unsignedFromDec(long int num, long int notation){
    string newNum="", base="0123456789ABCDEF";
    while (num){
        newNum+=base[num%notation];
        num/=notation;
    }
    reverse(newNum.begin(), newNum.end());
    return newNum;
}

long int toUnsignedDec(string binaryNum, long int notation){
    long int num=0;
    for(int c=0; c<binaryNum.length(); ++c){
        num+=(int)(binaryNum[c]-'0')*pow(notation, binaryNum.length()-c-1);
    }
    return num;
}

long int toDec(string binaryNum, long int notation){
    long int num=0;

}

Data::Data(){

}

int Data::checkNumBin(string num){
    return this->memSize*8<num.length();
}
long int Data::checkNum(long int num){
    return abs(num)>pow(2, 8*this->memSize-1);
}


long int Data::setNum(string num, NewData* notation){
    switch(notation->notationIn){
    case 2:
        if(checkNumBin(num)){
            this->mes="Число больше 4 байт";
            return 1;
        }
        this->binaryNum=createNewString(this->memSize*8-num.length(), '0')+num;
        if (binToDec()){ return 1; }
        binToOther(notation->notationOut);
        break;
    case 10:
        if (checkNum(atol(num.c_str()))){
            this->mes="Число больше 4 байт";
            return 1; }
        this->decimalNum=atol(num.c_str());
        if(decToBin()){ return 1;}
        return binToOther(notation->notationOut);
    default:
        this->otherNum=num;
        if (otherToBin(notation->notationIn)){ return 1; }
        if(checkNumBin(num)){
            this->mes="Число больше 4 байт";
            return 1;
        }
        return binToDec();
    }
    return 0;
}

long int Data::decToBin(){ //10->2
    this->binaryNum=unsignedFromDec(abs(this->decimalNum), 2);
    /*long int c= this->decimalNum;
    while (c){
        this->binaryNum+='0'+c%2;
        c/=2;
    }*/
    if (this->decimalNum < 0){
        this->binaryNum=createNewString(this->memSize*8-this->binaryNum.length(), '0')+this->binaryNum;
        this->binaryNum=replace((char*)this->binaryNum.c_str(), (char*)"0", (char*)"2", -1);
        this->binaryNum=replace((char*)this->binaryNum.c_str(), (char*)"1", (char*)"0", -1);
        this->binaryNum=replace((char*)this->binaryNum.c_str(), (char*)"2", (char*)"1", -1);
        this->binaryNum=unsignedFromDec(toUnsignedDec(this->binaryNum, 2)+1, 2);
    }
    this->binaryNum=string(createNewString(this->memSize*8-this->binaryNum.length(), '0'))+this->binaryNum;
    //this->binaryNum=this->binaryNum.substr(0, memSize*8);
    return 0;
}

long int Data::binToDec(){ //2->10
    this->decimalNum=1;
    if(this->binaryNum[0]=='1'){
        this->binaryNum=unsignedFromDec(toUnsignedDec(this->binaryNum, 2)-1, 2);
        this->binaryNum=(createNewString(this->memSize*8, '0')+this->binaryNum).substr(memSize*8);
        this->binaryNum=replace((char*)&this->binaryNum, (char*)"0", (char*)"2", -1);
        this->binaryNum=replace((char*)&this->binaryNum, (char*)"1", (char*)"0", -1);
        this->binaryNum=replace((char*)&this->binaryNum, (char*)"2", (char*)"1", -1);
        this->decimalNum=-1;
    }
    this->decimalNum*=toUnsignedDec(this->binaryNum, 2);

    return 0;
}

long int Data::binToOther(int notation){ //2->16
    if (this->binaryNum.length()> this->memSize*8){return 1;}
    this->otherNum=unsignedFromDec(toUnsignedDec(this->binaryNum, 2), notation);
    int c=0;
    for(;pow(2, c+1)<= notation; ++c);
    this->otherNum=string(createNewString(this->memSize*(8+c-1)/c-this->otherNum.length(), '0'))+this->otherNum;
    return 0;
}

long int Data::otherToBin(int notation){ //16->2
    this->binaryNum=unsignedFromDec(toUnsignedDec(this->otherNum, notation), 2);
    if (this->binaryNum.length()> this->memSize*8){return 1;}
    this->binaryNum=string(createNewString(this->memSize*8-this->binaryNum.length(), '0'))+this->binaryNum;
    return 0;
}
string Data::getNum(int notation){
    switch(notation){
        case 2:
        return getBin();
        case 10:
        return getDec();
        default:
        return getOther();
    }
}
string Data::getBin(){return this->binaryNum;}
string Data::getDec(){return to_string(this->decimalNum);}
string Data::getOther(){return this->otherNum;}
