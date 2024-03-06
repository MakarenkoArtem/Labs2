#include "logic.h"

#define Error -1
void freeMatrix(void** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

int initialization(AppContext* context, AppParams* params){
    context->file=createNewString(0, ' ');
    params->queue=initQueue();
    params->DArray.size=0;
    params->DArray.rows=(Row*)malloc(0);
    return OK;
}

int openFile(AppContext* context, AppParams* params){
    dynamicClearList(&params->DArray);
    FILE* f = fopen(context->file, "r");
    if(!f){
        return FileNotFound;
    }
    char** values, *line = getStrFromFile(f);
    if(line==(char*)Error){
        fclose(f);
        return FileNotFound;}
    freeStr(line);
    line = getStrFromFile(f);
    int count, i=0, errors=0,allCheks;
    Row row;//!feof(f) &&
    char* base;
    while (*line != (char)Error){
        qDebug("%i",++i);
        values = split(line, (char*)",", &count);
        freeStr(line);
        line = getStrFromFile(f);
        allCheks = count==7;
        for(int i=0;i<7;++i){
            if(!allCheks){break;}
            if(compareStr(values[i], (char*)"")){
                allCheks=0;
                break;
            }
            if(i==1){continue;}
            switch(i){
            case 0:
                base = (char*)"0123456789";
                break;
            default:
                base=(char*)"-.0123456789";
            }
            for(int j=0;values[i][j];++j){
                if(!charInSyms(values[i][j], base)){
                    allCheks=0;
                    break;
            }}
        }
        if(!allCheks){
            ++errors;
            continue;}
        row.year=strToInt(values[0]);
        row.region=copyStr(values[1]);
        row.npg=strToFloat(values[2]);
        row.birth_rate=strToFloat(values[3]);
        row.death_rate=strToFloat(values[4]);
        row.gdw=strToFloat(values[5]);
        row.urbanization=strToFloat(values[6]);
        dynamicAddRow(&params->DArray, row, params->DArray.size);
        freeMatrix((void**)values, count);
    };
    fclose(f);
    return errors;
}


int displayData(AppContext* context, AppParams* params){
    int first=1;
    float curVal=0;
    params->vals.averageVal=0.0;
    params->vals.maxVal=0.0;
    params->vals.minVal=0.0;
    List* l=init(curVal);
    for(int i=0;i<params->DArray.size;++i){
        if(compareStr(context->region, (char*)"") || compareStr(context->region, params->DArray.rows[i].region)){
            push(&params->queue, params->DArray.rows[i]);
            switch(context->column){
                case 1:{
                    curVal=(float)params->DArray.rows[i].year;
                    break;
                }
                case 2:
                    break;
                case 3:{
                    curVal=params->DArray.rows[i].npg;
                    break;
                }
                case 4:{
                    curVal=params->DArray.rows[i].birth_rate;
                    break;
                }
                case 5:{
                    curVal=params->DArray.rows[i].death_rate;
                    break;
                }
                case 6:{
                    curVal=params->DArray.rows[i].gdw;
                    break;
                }
                case 7:{
                    curVal=params->DArray.rows[i].urbanization;
                    break;
                }
            }
            if(first || params->vals.maxVal< curVal){
                params->vals.maxVal= curVal;
            }
            if(first || params->vals.minVal> curVal){
                params->vals.minVal= curVal;
            }
            if(first){
                first=0;
                l->first->data=curVal;
            }else{
                push(l, curVal);
            }
    }
    }
    params->vals.averageVal=getOnIndex(l, l->size/2)->data;
    deleteList(l);
    return OK;
}
