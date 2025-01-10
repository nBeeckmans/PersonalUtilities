#include <iostream>

#define CAPACITY_DOUBLE_ARROW_OP
#include "UnorderedVector.h"

void testRemove() {
    UnorderedVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.remove_at(1);
    std::cout << v << std::endl;
}

void testOutput() {
    UnorderedVector<int> uv;
    uv.push_back(1);
    uv.push_back(2);
    uv.push_back(3);
    std::cout << uv << std::endl;
}

int main() {
    testOutput();
    testRemove();
}
