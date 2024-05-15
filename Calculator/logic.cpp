#include "logic.h"
#include "iostream"

LogOperator Sum(1,"+", summ);
LogOperator Minus(1,"-", minu, false, true);
LogOperator UnoMinus(2,"-", minu, true, false);
LogOperator Multiplication(2,"*", mult);
LogOperator Division(2,"/", divi);
LogOperator Sqrt(3, "sqrt", sqrtFunc, true, false);
LogOperator Sin(3, "sin", sinFunc, true, false);
LogOperator Cos(3, "cos", cosFunc, true, false);
LogOperator Tg(3, "tg", tgFunc, true, false);
LogOperator Ctg(3, "ctg", ctgFunc, true, false);
LogOperator Stub(-1, "?", stub);
LogOperator BracketOpen(0, "(", stub);
LogOperator BracketClose(0, ")", stub);



int addChar(AppContext* context, AppParams* params){
    params->input.push_back(context->but);
    return OK;
}
int delChar(AppContext* context, AppParams* params){
    if (params->input.size()){
        params->input.pop_back();}
    return OK;
}
bool isDigit(string str){
    return 0<=str[0]-'0' && str[0]-'0'<10;
}

int digitToNums(AppContext* context, AppParams* params){
    bool num=false;
    int ind,point =-1;
    double val;//long int val;
    string str;
    params->input.push_back("?");//добавляю элемент чтобы в конце выгурзить все операторы
    LogOperator* operat;
    Node node;
    for(int i=0; i!=params->input.size();++i){
        str=params->input[i];
        //=============add num===================
        if(isDigit(str)){
            if(num){
                val=val*10+(str.c_str()[0]-'0');
                point+=point!=-1;
            }else{
                num=true;
                val=str.c_str()[0]-'0';
            }
        }else if(str=="."){
            if(!num){            //params->input[i-1]=std::to_string(val/pow(10, point==-1?0:point));
                throw std::invalid_argument("у числа нет целой части");
            }
            if(point!=-1){
                throw std::invalid_argument("у числа несколько дробных частей");
            }
            point=0;
        }else {
            if(num){
                node.typeOper=false;
                node.value.val=val/pow(10, point==-1?0:point);
                if(std::isinf(node.value.val)){
                    throw std::out_of_range("Число слишком большое");
                }
                params->list.push_back(node);
                point=-1;}
            //============end add num==============
            //============add operator=================
            if(str=="?"){
                operat=&Stub;
            }else if(str=="+"){
                operat=&Sum;
            }else if(str=="-"){
                if(num || (i && params->input[i-1]!="(")){
                    //если перед минусом есть число или оператор но не "("
                    operat=&Minus;
                }else{operat=&UnoMinus;}
            }else if(str=="*"){
                operat=&Multiplication;
            }else if(str=="/"){
                operat=&Division;
            }else if(str=="("){
                operat=&BracketOpen;
            }else if(str==")"){
                operat=&BracketClose;
            }else if(str=="sqrt"){
                operat=&Sqrt;
            }else if(str=="sin"){
                operat=&Sin;
            }else if(str=="сos"){
                operat=&Cos;
            }else if(str=="tg"){
                operat=&Tg;
            }else if(str=="ctg"){
                operat=&Ctg;
            }else{throw std::invalid_argument("Не реализованный оператор");}
            num=false;
            //==============filling list=============
            int j, indSet = params->list.size();//вставляем операторы на этот индекс и дальше
            for(j=params->stack.size()-1; j!=-1;--j){
                if(params->stack[j]==&BracketOpen){
                    if(operat==&BracketClose){
                        params->stack.erase(params->stack.begin()+j);
                    }else if(operat==&Stub){//если при винальном проходе осталась скобка
                        throw std::logic_error("Есть не закрытая скобка");
                    }
                    break;
                }
                if(operat==&BracketOpen){break;}//если открывающая скобка, то ничего не записываем в лист
                if(operat==&BracketClose || params->stack[j]->priority>=operat->priority){
                    if(params->stack[j]==&BracketOpen){//если дошли до открывающей скобки
                        if(operat==&BracketClose){//если текущий опертор закрывающая скобка
                            params->stack.erase(params->stack.begin()+j);
                        }
                        break;}
                    node.typeOper=true;
                    node.value.oper=params->stack[j];
                    ind =indSet;
                    for(;ind!=params->list.size() && params->list[ind].value.oper->priority>=operat->priority;++ind);// нахожу куда ставить оператор по порядку и приоритету
                    params->list.insert(params->list.begin()+ind, node);
                    params->stack.erase(params->stack.begin()+j);
                }
            }
            if(j==-1 && operat==&BracketClose){throw std::invalid_argument("Нет открывающей скобки");}
            if(operat!=&BracketClose){params->stack.push_back(operat);}
        }
    }
    string s="";
    for(auto it:params->list){
        if(it.typeOper){
            s+=it.value.oper->symbol+" ";
        }else{
            s+=std::to_string(it.value.val)+" ";
        }
    }
    qDebug(s.c_str());
    return OK;
}

int calc(AppContext* context, AppParams* params){
    if(params->list.size()==0 ||(params->list.size()>1 && params->list[params->list.size()-1].typeOper==false)){//если нет элементов или если их больше одного и последний не оператор (1,2,+,6)
        throw std::invalid_argument("Не хватает чисел");
    }
    for(int i=0;i!=params->list.size();++i){
        if(params->list[i].typeOper){
            if(i==1 || (i>1 && params->list[i-2].typeOper) || (i>0 && params->list[i].value.oper->haveOnlyOneArgFunc)){//если перед оператором только один элемент /
                //..operator, num, operator.. / оператор принимает только один аргумент
                params->list[i].value.val=params->list[i].value.oper->calc(params->list[i-1].value.val);
                params->list[i].typeOper=false;
                params->list.erase(params->list.begin()+--i);
            }else if(i>1){
                params->list[i].value.val=params->list[i].value.oper->calc(params->list[i-2].value.val, params->list[i-1].value.val);
                params->list[i].typeOper=false;
                params->list.erase(params->list.begin()+--i);
                params->list.erase(params->list.begin()+--i);
            }else{
                throw std::invalid_argument("Ошибка в операторах");
            }
            qDebug(std::to_string(params->list[i].value.val).c_str());
        }
    }
    params->output=std::to_string(params->list[params->list.size()-1].value.val);
    return OK;
}


int revFunc(AppContext* context, AppParams* params){
    params->input.insert(params->input.begin(), "(");
    params->input.insert(params->input.begin(), "/");
    params->input.insert(params->input.begin(), "1");
    params->input.push_back(")");
    return OK;
}
