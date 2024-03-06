#include "logic.h"
#include<QDebug>
#include<QClipboard>
#include<QApplication>


char* hexNum=(char*)"0123456789ABCDEF";
/*int copy(params* params, context* context){
    QClipboard *clipboard=QGuiApplication::clipboard();
    clipboard->setText(params->val);
    return OK;
}*/

int initialization(AppParams* params, AppContext* context){
    int n;
    char** filePath=split(params->filePath, (char*)"/", &n);
    free(params->filePath);
    free(filePath[n-1]);
    filePath[n-1]=copyStr((char*)"MainWindow");
    params->filePath=join(filePath, n, (char*)"/");
    freeListStr(filePath, n);

    params->val=createNewString(1,'0');
    params->binaryNum=createNewString(0,'0');
    params->otherNum=createNewString(0,'0');
    //context->num=createNewString(0,'0');
    params->error=OK;
}

int validation(AppParams* params, AppContext* context){
    int result = OK, i=(*context->num=='-')&&(context->notationIn==10);
    char* sysNat=subStr(hexNum, 0, context->notationIn);
    for(;i<lenStr(context->num);++i){
        if (!charInSyms(context->num[i], sysNat)){
            result= NumberSystemEerror;
            break;
        }
    }
    freeStr(sysNat);
    freeStr(context->num);
    return result;
}


int counting(AppParams* params, AppContext* context){
    if (params->error!=OK){return params->error;}
    if(setNum(params, context)){
        return ValueExceded;
    }
    freeStr(params->val);
    switch(context->notationOut){
    case 2:
        params->val=copyStr(getBin(params));
        break;
    case 10:
        params->val=copyStr(getDec(params));
        break;
    default:
        params->val=copyStr(getOther(params));
        break;
    }
    return OK;
}
/*int changing(AppParams* params, AppContext* context){
    context->notationIn+=context->notationOut;
    context->notationOut=context->notationIn-context->notationOut;
    context->notationIn-=context->notationOut;
    /*switch(context->notationIn){
    case 2:
        params->val=getBin(params);
        break;
    case 10:
        params->val=getDec(params);
        break;
    default:
        params->val=getOther(params);
        break;
    }/
    return 0;
}*/
