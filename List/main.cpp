#include <iostream>
#include "list.h"
#include<vector>

int main() {
    std::vector<int> f({1, 64});
    std::cout << f[0] << " " << f[1];
    list<int> h({-6, -35});
    list<int> t;
    t.add(5);
    t.add(46);
    t.add_range(h);
    t.set_elem(1, -99999);
    std::cout << t[0] << " " << t[1]<<" "<<t.get_elem(1) <<" "<<t[2]<<" "<<(t.begin()+3).value();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
