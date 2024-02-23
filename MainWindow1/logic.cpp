#include "logic.h"
#include<QDebug>
#include<QClipboard>
#include<QApplication>


char* hexNum=(char*)"0123456789ABCDEF";
int copy(Data* data, NewData* newData){
    QClipboard *clipboard=QGuiApplication::clipboard();
    clipboard->setText(data->val);
    return OK;
}

int validation(Data* data, NewData* newData){
    int result = OK, i=(*newData->num=='-')&&(newData->notationIn==10);
    char* sysNat=subStr(hexNum,0, newData->notationIn);
    for(;i<lenStr(newData->num);++i){
        if (!charInSyms(newData->num[i], sysNat)){
            result= NumberSystemEerror;
            break;
        }
    }
    freeStr(sysNat);
    return result;
}
int counting(Data* data, NewData* newData){
    if (data->error){return data->error;}
    if(setNum(data, newData)){
        return ValueEexceded;
    }
    freeStr(data->val);
    switch(newData->notationOut){
    case 2:
        data->val=getBin(data);
        break;
    case 10:
        data->val=getDec(data);
        break;
    default:
        data->val=getOther(data);
        break;
    }
    return OK;
}
int changing(Data* data, NewData* newData){
    char* s=newData->num;
    newData->num=data->val;
    data->val=s;
   // newData->num=getNum(data, newData->notationOut);
    newData->notationIn+=newData->notationOut;
    newData->notationOut=newData->notationIn-newData->notationOut;
    newData->notationIn-=newData->notationOut;
    /*switch(newData->notationIn){
    case 2:
        data->val=getBin(data);
        break;
    case 10:
        data->val=getDec(data);
        break;
    default:
        data->val=getOther(data);
        break;
    }*/
    return 0;
}
