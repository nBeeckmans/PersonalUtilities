#define COPYABLE_ARENA
#include <format>
#include <iostream>
#include <memory>
#include <ostream>

#include "Arena.h"

void complexArenaCreation() {
    struct LongStruct {
        double numbers[15];
        char characters[100];
    };

    Arena<sizeof(LongStruct) * 2> arena;
    auto addedStruct =
        arena.addElement<LongStruct>((struct LongStruct){ .numbers=1.0, .characters="Hello world"});

    std::cout << arena;
}

void simpleArenaCreation() {
    Arena<sizeof(long int)> arena;

    const auto element = arena.addElement<long int>(123456789);
    std::cout << arena;
    std::cout << std::format("{:} was added to the arena at position {}\n",
        arena.getElementAt<long int>(element),
        element);
}

int main() {
    simpleArenaCreation();
    complexArenaCreation();
}