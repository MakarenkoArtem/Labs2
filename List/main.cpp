#include <iostream>
#include "list.h"
#include<vector>

int main() {
    std::vector<int> f({1, 64});
    std::cout << f[0] << " " << f[1];
    list<double> h({6.1, 35});
    list<int> t;
    t.add(5);
    t.add(46);
    std::cout << t[0] << " " << t[1];
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
