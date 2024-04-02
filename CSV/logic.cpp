#include "logic.h"

#define ErrorStrFromFile -1

void freeMatrix(void** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

int initialization(AppContext* context, AppParams* params){
    context->maxYear=0;
    context->minYear=0;
    context->file=createNewString(0, ' ');
    context->activeRegions.titles=(char**)malloc(0);
    context->activeRegions.count=0;
    //context->region=createNewString(0, ' ');
    params->regions.titles=split((char*)"", (char*)"/", &params->regions.count);
    params->titles.titles=split((char*)"", (char*)"/", &params->titles.count);
    params->queue=initQueue();
    params->DArray.size=0;
    params->DArray.rows=(Row*)malloc(0);
    params->data=(DataForGrap*)malloc(sizeof(void*));
    params->data->vals=(CounteredList*)malloc(sizeof(void*)*0);
    params->data->count=0;
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
    clearListString(&params->titles);
    params->titles.titles = split(line, (char*)",", &params->titles.count);
    freeStr(line);
    line = getStrFromFile(f);
    context->minYear==NULL;
    int count, i=0, errors=0,allCheks;
    Row row;//!feof(f) &&
    char* base;
    clearListString(&params->regions);
    params->regions.titles=split((char*)"", (char*)"/", &params->regions.count);
    params->regions.count=0;
    while (*line != (char)ErrorStrFromFile){
        ++i;
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
        if(context->minYear==NULL){
            context->minYear=row.year;
            context->maxYear=row.year;
        }else if(context->minYear> row.year){
            context->minYear=row.year;
        }else if(context->maxYear<row.year){
            context->maxYear=row.year;
        }
        if (strInListStr(params->regions.titles, params->regions.count, row.region)==-1){
            params->regions.titles=(char**)realloc(params->regions.titles, ++params->regions.count*sizeof(char*));
            params->regions.titles[params->regions.count-1]=row.region;
        }
    };
    if(context->minYear==NULL){
        context->minYear=0;
        context->maxYear=0;}
    context->dynamMaxYear=context->maxYear;
    context->dynamMinYear=context->minYear;
    fclose(f);
    clearListString(&context->activeRegions);
    context->activeRegions.titles=(char**)malloc(0);
    context->activeRegions.count=0;
    return errors;
}

int sortData(AppContext* context, AppParams* params){
    DataForGrap* data=(DataForGrap*)malloc(sizeof(DataForGrap));//&params->data;
    data->count=0;
    data->vals=(CounteredList*)malloc(sizeof(CounteredList)*(data->count));
    Node* curVal= params->queue.head;
    int ind;
    CounteredList* list;
    for(;curVal!=NULL;curVal=curVal->next){
        ind=0;
        for (;ind<data->count;++ind){
            if (compareStr(curVal->data.region, data->vals[ind].region)){
                break;
            }}
        list=data->vals+ind;
        if (ind==data->count){
            data->vals=(CounteredList*)realloc(data->vals, sizeof(CounteredList)*(++data->count));
            list=data->vals+ind;
            list->count=0;
            list->region=copyStr(curVal->data.region);
            list->compation=16;
            list->vals=(NumInList*)malloc(sizeof(NumInList)*list->compation);
        }
        if(list->count==list->compation){
            list->compation*=2;
            list->vals=(NumInList*)realloc(list->vals, sizeof(NumInList)*list->compation);
        }
        list=data->vals+ind;
        switch(context->column){
        case Year:{
            list->vals[list->count].val=(float)curVal->data.year;
            break;
        }
        case Region:
            break;
        case Npg:{
            list->vals[list->count].val=curVal->data.npg;
            break;
        }
        case Birth_rate:{
            list->vals[list->count].val=curVal->data.birth_rate;
            break;
        }
        case Death_rate:{
            list->vals[list->count].val=curVal->data.death_rate;
            break;
        }
        case Gdw:{
            list->vals[list->count].val=curVal->data.gdw;
            break;
        }
        case Urbanization:{
            list->vals[list->count].val=curVal->data.urbanization;
            break;
        }
        define:{
            list->vals[list->count].val=0;
            break;
        }}
        list->vals[list->count++].key=curVal->data.year;

    }
    params->data=data;
    return OK;
}

int displayData(AppContext* context, AppParams* params){
    int first=1;
    float curVal=0;
    params->vals.averageVal=0.0;
    params->vals.maxVal=0.0;
    params->vals.minVal=0.0;
    List* l=init(curVal);
    for(int i=0;i<params->DArray.size;++i){
        if(context->dynamMinYear <= params->DArray.rows[i].year && context->dynamMaxYear >= params->DArray.rows[i].year && (context->activeRegions.count==0 || -1!=strInListStr(context->activeRegions.titles, context->activeRegions.count, params->DArray.rows[i].region))){
            push(&params->queue, params->DArray.rows[i]);
            switch(context->column){
                case Year:{
                    curVal=(float)params->DArray.rows[i].year;
                    break;
                }
                case Region:
                    break;
                case Npg:{
                    curVal=params->DArray.rows[i].npg;
                    break;
                }
                case Birth_rate:{
                    curVal=params->DArray.rows[i].birth_rate;
                    break;
                }
                case Death_rate:{
                    curVal=params->DArray.rows[i].death_rate;
                    break;
                }
                case Gdw:{
                    curVal=params->DArray.rows[i].gdw;
                    break;
                }
                case Urbanization:{
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

int addRegion(AppContext* context, AppParams* params){
    if (!(-1==strInListStr(context->activeRegions.titles, context->activeRegions.count, context->addRegion) //уже есть в отображаемом списке
            && -1!=strInListStr(params->regions.titles, params->regions.count, context->addRegion)))  {    //нет такого региона
        return Error;}
    context->activeRegions.titles=(char**)realloc(context->activeRegions.titles, ++context->activeRegions.count*sizeof(char*));
    context->activeRegions.titles[context->activeRegions.count-1]=context->addRegion;
    return OK;
}

int delRegion(AppContext* context, AppParams* params){
    if(context->curRegion<0){return Error;}
    delStrInList(context->activeRegions.titles, context->curRegion, context->activeRegions.count--);
    return OK;
}
