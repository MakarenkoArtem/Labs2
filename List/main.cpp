#include <iostream>
#include "list.h"

int comp(const int &a, const int &b){
    return a>b?-1:a!=b;
}
int main() {
    list<int> h({-6, -35, 6, 7, -54654, -6, 6, -94654645});
    for(auto it:h){
        std::cout << it<<" ";
    }
    std::cout<<std::endl;
    list<int>g({45, 6, 9, 3, -6});
    h.add_range(g);
    h.sort(comp);
    for(auto it:h){
        std::cout << it<<" ";
    }
    std::cout<<std::endl;
    list<int> t;
    t.add(5);
    t.add(46);
    std::cout << (++h.cbegin()).value();
    t.add_range(h);
    t.set_elem(1, -99999);
    std::cout << t[0] << " " << t[1]<<" "<<t.get_elem(1) <<" "<<t[2]<<" "<<(t.begin()+3).value();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
