#include "entrypoint.h"

int doOperation(int operation, AppContext* context, AppParams* params){
    switch(operation){
    case AddChar:
        return addChar(context, params);
    case DelChar:
        return delChar(context, params);
    case Calc:
        int ans;
        try{
            ans= digitToNums(context, params);
        }  catch (std::exception &ex ) {
            ans=Error;
            params->output=ex.what();
        }
        for(;params->stack.size();params->stack.pop_back());
        if(params->input[params->input.size()-1]=="?"){params->input.pop_back();}//удаляю "?")
        if(ans){return ans;}
        try {
            ans=calc(context, params);
        }  catch (std::exception &ex ) {
            ans=Error;
            params->output=ex.what();
        }
        for(;params->list.size();params->list.pop_back());
        return ans;
    case RevFunc:
        return revFunc(context, params);

}
}
