#include "data.h"
#include <libraries/mystring.h>
#include"QtDebug"

char* unsignedFromDec(long long int num, int notation){
    if(num<notation){return createNewString(1,'0'+num);}
    int h = log(num)/log(notation)+1;
    char* newNum=createNewString(h, '+'), *base=(char*)"0123456789ABCDEF";
    while (num){
        newNum[--h]=base[num%notation];
        //newNum=addChar((char*)reallocList(newNum, lenStr(newNum)+2, sizeof(char)), 0,base[num%notation]);
        num/=notation;
        if(h<0){
            qDebug("значит недостаточно памяти выделено");
            free((char*)"");}//значит недостаточно памяти выделено
    }
    //replace(newNum, (char*)"+", (char*)"", -1);
    //reverse(newNum.begin(), newNum.end());
    return newNum;
}

long long int toUnsignedDec(char* binaryNum, int notation){
    long long int num=0;
    for(int c=0; c<lenStr(binaryNum); ++c){
        qDebug("%i", binaryNum[c]-'0');
        num+=(long long int)(binaryNum[c]-'0')*pow(notation, lenStr(binaryNum)-c-1);
    }
    return num;//>pow(2, 32)?-1:num;
    //return num;
}




int checkNumBin(AppParams* params, char* num){
    return params->memSize*8<lenStr(num);
}
long int checkNum(AppParams* params, long int num){
    return abs(num)>pow(2, 8*params->memSize-1);
}


int setNum(AppParams* params, AppContext* notation){
    switch(notation->notationIn){
    case 2:
        if(checkNumBin(params, notation->num)){
            return ValueExceded;
        }
        qDebug("freeStr 12");
        freeStr(params->binaryNum);
        params->binaryNum=createNewString(params->memSize*8-lenStr(notation->num), '0');
        params->binaryNum=addStr((char*)reallocList(params->binaryNum, (lenStr(params->binaryNum)+lenStr(notation->num)+1),sizeof(char)),notation->num);
        if (binToDec(params)){ return SmallError; }
        return binToOther(params, notation->notationOut)?SmallError:OK;
    case 10:
        if (checkNum(params, strToLongInt(notation->num))){
            return ValueExceded; }
        params->decimalNum=strToLongInt(notation->num);
        if(decToBin(params)){ return SmallError;}
        return binToOther(params, notation->notationOut)?SmallError:OK;
    default:
        qDebug("freeStr 13");
        freeStr(params->otherNum);
        params->otherNum=copyStr(notation->num);
        if (otherToBin(params, notation->notationIn)){ return SmallError; }
        if(checkNumBin(params, notation->num)){
            return ValueExceded;
        }
        if (binToOther(params, notation->notationOut)){ return SmallError; }
        return binToDec(params)?SmallError:OK;
    }
    return OK;
}

long int decToBin(AppParams* params){ //10->2
    qDebug("freeStr 14 %s",params->binaryNum);
    freeStr(params->binaryNum);
    params->binaryNum=unsignedFromDec((long int)abs(params->decimalNum),2);
    /*long int c= params->decimalNum;
    while (c){
        params->binaryNum+='0'+c%2;
        c/=2;
    }*/
    char* s;
    if (params->decimalNum < 0){
        s=createNewString(params->memSize*8-lenStr(params->binaryNum), '0');
        s=addStr((char*)reallocList(s, (lenStr(s)+lenStr(params->binaryNum)+1),sizeof(char)),params->binaryNum);
        qDebug("freeStr 15");
        freeStr(params->binaryNum);
        params->binaryNum=s;
        params->binaryNum=replace((char*)params->binaryNum, (char*)"0", (char*)"2", -1);
        params->binaryNum=replace((char*)params->binaryNum, (char*)"1", (char*)"0", -1);
        params->binaryNum=replace((char*)params->binaryNum, (char*)"2", (char*)"1", -1);
        long long int h=(long long int)toUnsignedDec(params->binaryNum, 2)+1;
        if(h<1 || h>=pow(2, params->memSize*8-1)){return !OK;}
        qDebug("freeStr 16");
        freeStr(params->binaryNum);
        params->binaryNum=unsignedFromDec(h, 2);
    }
    s=createNewString(params->memSize*8-lenStr(params->binaryNum), '0');
    s=addStr((char*)reallocList(s, (lenStr(s)+lenStr(params->binaryNum)+1),sizeof(char)),params->binaryNum);
    qDebug("freeStr 17");
    freeStr(params->binaryNum);
    params->binaryNum=s;
    return OK;
}

int binToDec(AppParams* params){ //2->10
    if(params->binaryNum[0]=='1'){
        long long int h=(long long int)toUnsignedDec(params->binaryNum, 2)-1;
        if(h<-1 || h>=pow(2, params->memSize*8-1)-2){return !OK;}
        char* n = unsignedFromDec(h, 2);
        qDebug("len %i", params->memSize*8-lenStr(params->binaryNum));
        char*s=createNewString(params->memSize*8-lenStr(params->binaryNum), '0');
        s=addStr((char*)reallocList(s, (lenStr(s)+lenStr(params->binaryNum)+1),sizeof(char)),n);
        qDebug("freeStr 5");
        freeStr(n);
        s=replace(s, (char*)"0", (char*)"2", -1);
        s=replace(s, (char*)"1", (char*)"0", -1);
        s=replace(s, (char*)"2", (char*)"1", -1);
        params->decimalNum=(int)-toUnsignedDec(s, 2);
        if(params->decimalNum>0 || params->decimalNum>=-pow(2, params->memSize*8-1)){return !OK;}
        qDebug("freeStr 6");
        freeStr(s);
    }else{
        params->decimalNum=(int)toUnsignedDec(params->binaryNum, 2);}
        if(params->decimalNum<0 || params->decimalNum>=pow(2, params->memSize*8-1)){return !OK;}
    return OK;
}

long int binToOther(AppParams* params, int notation){ //2->16
    qDebug("freeStr 7");
    freeStr(params->otherNum);
    if (lenStr(params->binaryNum)> params->memSize*8){return ValueExceded;}
    long long int h=(long long int)toUnsignedDec(params->binaryNum, 2);
    if(h<0 || h>=pow(2, params->memSize*8-1)){return !OK;}
    params->otherNum=unsignedFromDec(h, notation);
    int c=0;
    for(;pow(2, c+1)<= notation; ++c);
    char*s=createNewString(params->memSize*(8+c-1)/c-lenStr(params->otherNum), '0');
    s=addStr((char*)reallocList(s, (lenStr(s)+lenStr(params->otherNum)+1),sizeof(char)),params->otherNum);
    qDebug("freeStr 8 %s", params->otherNum);
    freeStr(params->otherNum);
    params->otherNum=s;
    return OK;
}

long int otherToBin(AppParams* params, int notation){ //16->2
    qDebug("freeStr 9");
    freeStr(params->binaryNum);
    long long int h=(long long int)toUnsignedDec(params->otherNum, notation);
    if(h<0 || h>=pow(2, params->memSize*8-1)){return !OK;}
    params->binaryNum=unsignedFromDec(h, 2);
    if (lenStr(params->binaryNum)> params->memSize*8){return ValueExceded;}
    char*s=createNewString(params->memSize*8-lenStr(params->binaryNum), '0');
    s=addStr((char*)reallocList(s, (lenStr(s)+lenStr(params->binaryNum)+1),sizeof(char)),params->binaryNum);
    qDebug("freeStr 10");
    freeStr(params->binaryNum);
    params->binaryNum=s;
    return OK;
}

char* getNum(AppParams* params, int notation){
    switch(notation){
        case 2:
        return getBin(params);
        case 10:
        return getDec(params);
        default:
        return getOther(params);
    }
}
char* getBin(AppParams* params){return params->binaryNum;}
char* getDec(AppParams* params){return longIntToStr(params->decimalNum);}
char* getOther(AppParams* params){return params->otherNum;}
