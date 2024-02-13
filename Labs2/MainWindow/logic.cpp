#include "logic.h"
#include<QDebug>
#include<QClipboard>
#include<QApplication>

string binNum="01";
string decNum="-0123456789";
string hexNum="0123456789ABCDEF";
int copy(Data* data, NewData* newData){
    QClipboard *clipboard=QGuiApplication::clipboard();
    clipboard->setText(data->val.c_str());
    return 0;
}

int validation(Data* data, NewData* newData){
    char* sysNat;
    switch(newData->notationIn){
    case 2:
        sysNat=(char*)binNum.c_str();
        break;
    case 10:
        sysNat=(char*)decNum.c_str();
        break;
    default:
        sysNat=(char*)hexNum.substr(0, newData->notationIn-1).c_str();
        break;
    }
    for(int i=0;i<newData->num.length();++i){
        qDebug("%c %s", (char)newData->num[i],sysNat);
        if (!charInSyms(newData->num[i], sysNat)){
            data->mes="Число не соответсвует системе счиления";
            return 1;
        }
    }
    return 0;
}
int counting(Data* data, NewData* newData){
    if (data->mes!=""){return 1;}
    data->val="";
    if(data->setNum(newData->num.c_str(), newData)){
        data->mes="Число больше 4 байт";
        return 1;
    }
    switch(newData->notationOut){
    case 2:
        data->val=data->getBin();
        break;
    case 10:
        data->val=data->getDec();
        break;
    default:
        data->val=data->getOther();
        break;
    }
    return 0;
}
int changing(Data* data, NewData* newData){
    newData->notationIn+=newData->notationOut;
    newData->notationOut=newData->notationIn-newData->notationOut;
    newData->notationIn-=newData->notationOut;
    newData->num=data->getNum(newData->notationIn);
    switch(newData->notationOut){
    case 2:
        data->val=data->getBin();
        break;
    case 10:
        data->val=data->getDec();
        break;
    default:
        data->val=data->getOther();
        break;
    }
    return 0;
}
