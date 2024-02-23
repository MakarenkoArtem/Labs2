#include "data.h"
#include <libraries/mystring.h>
#include"QtDebug"
char* unsignedFromDec(long int num, int notation){
    char* newNum=createNewString(0, ' '), *base=(char*)"0123456789ABCDEF";
    while (num){
        newNum=addChar((char*)reallocList(newNum, lenStr(newNum)+2, sizeof(char)), 0,base[num%notation]);
        //newNum+=base[num%notation];
        num/=notation;
    }
    //reverse(newNum.begin(), newNum.end());
    return newNum;
}

long int toUnsignedDec(char* binaryNum, int notation){
    long int num=0;

    for(int c=0; c<lenStr(binaryNum); ++c){
        num+=(int)(binaryNum[c]-'0')*pow(notation, lenStr(binaryNum)-c-1);
    }
    return num;
}




int checkNumBin(Data* data, char* num){
    return data->memSize*8<lenStr(num);
}
long int checkNum(Data* data, long int num){
    return abs(num)>pow(2, 8*data->memSize-1);
}


int setNum(Data* data, NewData* notation){
    switch(notation->notationIn){
    case 2:
        if(checkNumBin(data, notation->num)){
            return ValueEexceded;
        }
        qDebug("freeStr 12");
        freeStr(data->binaryNum);
        data->binaryNum=createNewString(data->memSize*8-lenStr(notation->num), '0');
        data->binaryNum=addStr((char*)reallocList(data->binaryNum, (lenStr(data->binaryNum)+lenStr(notation->num)+1),sizeof(char)),notation->num);
        if (binToDec(data)){ return SmallError; }
        return binToOther(data, notation->notationOut)?SmallError:OK;
    case 10:
        if (checkNum(data, strToLongInt(notation->num))){
            return ValueEexceded; }
        data->decimalNum=strToLongInt(notation->num);
        if(decToBin(data)){ return SmallError;}
        return binToOther(data, notation->notationOut)?SmallError:OK;
    default:
        qDebug("freeStr 13");
        freeStr(data->otherNum);
        data->otherNum=copyStr(notation->num);
        if (otherToBin(data, notation->notationIn)){ return SmallError; }
        if(checkNumBin(data, notation->num)){
            return ValueEexceded;
        }
        if (binToOther(data, notation->notationOut)){ return SmallError; }
        return binToDec(data)?SmallError:OK;
    }
    return OK;
}

long int decToBin(Data* data){ //10->2
    qDebug("freeStr 14 %s",data->binaryNum);
    freeStr(data->binaryNum);
    data->binaryNum=unsignedFromDec((long int)abs(data->decimalNum),2);
    /*long int c= data->decimalNum;
    while (c){
        data->binaryNum+='0'+c%2;
        c/=2;
    }*/
    char* s;
    if (data->decimalNum < 0){
        s=createNewString(data->memSize*8-lenStr(data->binaryNum), '0');
        s=addStr((char*)reallocList(s, (lenStr(s)+lenStr(data->binaryNum)+1),sizeof(char)),data->binaryNum);
        qDebug("freeStr 15");
        freeStr(data->binaryNum);
        data->binaryNum=s;
        data->binaryNum=replace((char*)data->binaryNum, (char*)"0", (char*)"2", -1);
        data->binaryNum=replace((char*)data->binaryNum, (char*)"1", (char*)"0", -1);
        data->binaryNum=replace((char*)data->binaryNum, (char*)"2", (char*)"1", -1);
        long int h=(long int)toUnsignedDec(data->binaryNum, 2)+1;
        qDebug("freeStr 16");
        freeStr(data->binaryNum);
        data->binaryNum=unsignedFromDec(h, 2);
    }
    s=createNewString(data->memSize*8-lenStr(data->binaryNum), '0');
    s=addStr((char*)reallocList(s, (lenStr(s)+lenStr(data->binaryNum)+1),sizeof(char)),data->binaryNum);
    qDebug("freeStr 17");
    freeStr(data->binaryNum);
    data->binaryNum=s;
    return OK;
}

int binToDec(Data* data){ //2->10
    if(data->binaryNum[0]=='1'){
        long int h=(long int)toUnsignedDec(data->binaryNum, 2)-1;
        char* n = unsignedFromDec(h, 2);
        qDebug("len %i", data->memSize*8-lenStr(data->binaryNum));
        char*s=createNewString(data->memSize*8-lenStr(data->binaryNum), '0');
        s=addStr((char*)reallocList(s, (lenStr(s)+lenStr(data->binaryNum)+1),sizeof(char)),n);
        qDebug("freeStr 5");
        freeStr(n);
        s=replace(s, (char*)"0", (char*)"2", -1);
        s=replace(s, (char*)"1", (char*)"0", -1);
        s=replace(s, (char*)"2", (char*)"1", -1);
        data->decimalNum=-toUnsignedDec(s, 2);
        qDebug("freeStr 6");
        freeStr(s);
    }else{
        data->decimalNum=toUnsignedDec(data->binaryNum, 2);}
    return OK;
}

long int binToOther(Data* data, int notation){ //2->16
    qDebug("freeStr 7");
    freeStr(data->otherNum);
    if (lenStr(data->binaryNum)> data->memSize*8){return ValueEexceded;}
    data->otherNum=unsignedFromDec((long int)toUnsignedDec(data->binaryNum, 2), notation);
    int c=0;
    for(;pow(2, c+1)<= notation; ++c);
    char*s=createNewString(data->memSize*(8+c-1)/c-lenStr(data->otherNum), '0');
    s=addStr((char*)reallocList(s, (lenStr(s)+lenStr(data->otherNum)+1),sizeof(char)),data->otherNum);
    qDebug("freeStr 8 %s", data->otherNum);
    freeStr(data->otherNum);
    data->otherNum=s;
    return OK;
}

long int otherToBin(Data* data, int notation){ //16->2
    qDebug("freeStr 9");
    freeStr(data->binaryNum);
    data->binaryNum=unsignedFromDec(toUnsignedDec(data->otherNum, notation), 2);
    if (lenStr(data->binaryNum)> data->memSize*8){return ValueEexceded;}
    char*s=createNewString(data->memSize*8-lenStr(data->binaryNum), '0');
    s=addStr((char*)reallocList(s, (lenStr(s)+lenStr(data->binaryNum)+1),sizeof(char)),data->binaryNum);
    qDebug("freeStr 10");
    freeStr(data->binaryNum);
    data->binaryNum=s;
    return OK;
}

char* getNum(Data* data, int notation){
    switch(notation){
        case 2:
        return getBin(data);
        case 10:
        return getDec(data);
        default:
        return getOther(data);
    }
}
char* getBin(Data* data){return data->binaryNum;}
char* getDec(Data* data){return longIntToStr(data->decimalNum);}
char* getOther(Data* data){return data->otherNum;}
