#include "logic.h"

#define Error -1
void freeMatrix(void** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

int openFile(char* file, DBookList* DArray, Queue* queue){
    dynamicClearList(DArray);
    FILE* f = fopen(file, "r");
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
    Book b;//!feof(f) &&
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
        //b=(Book*)mallocList(1, sizeof(Book));
        b.year=strToInt(values[0]);
        b.region=copyStr(values[1]);
        b.npg=strToFloat(values[2]);
        b.birth_rate=strToFloat(values[3]);
        b.death_rate=strToFloat(values[4]);
        b.gdw=strToFloat(values[5]);
        b.urbanization=strToFloat(values[6]);
        dynamicAddBook(DArray, b, DArray->size);
        freeMatrix((void**)values, count);
    };
    fclose(f);
    return errors;
}


int displayData(DBookList* DArray, Queue* queue, char* region, int column, MyData* vals){
    int first=1;
    float curVal=0;
    vals->averageVal=0.0;
    vals->maxVal=0.0;
    vals->minVal=0.0;
    List* l=init(curVal);
    for(int i=0;i<DArray->size;++i){
        if(compareStr(region, (char*)"") || compareStr(region, DArray->books[i].region)){
            push(queue, DArray->books[i]);
            switch(column){
                case 1:{
                    curVal=(float)DArray->books[i].year;
                    break;
                }
                case 2:
                    break;
                case 3:{
                    curVal=DArray->books[i].npg;
                    break;
                }
                case 4:{
                    curVal=DArray->books[i].birth_rate;
                    break;
                }
                case 5:{
                    curVal=DArray->books[i].death_rate;
                    break;
                }
                case 6:{
                    curVal=DArray->books[i].gdw;
                    break;
                }
                case 7:{
                    curVal=DArray->books[i].urbanization;
                    break;
                }
            }
            if(first || vals->maxVal< curVal){
                vals->maxVal= curVal;
            }
            if(first || vals->minVal> curVal){
                vals->minVal= curVal;
            }
            if(first){
                first=0;
                l->first->data=curVal;
            }else{
                push(l, curVal);
            }
    }
    }
    vals->averageVal=getOnIndex(l, l->size/2)->data;
    deleteList(l);
    return OK;
}
