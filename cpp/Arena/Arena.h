#pragma once
#include <algorithm>
#include <utility>
#include <cassert>
#include <tbb/task_arena.h>


using ARENA_POSITION = size_t;

template<size_t SIZE>
class Arena {
using byte = unsigned char;
byte* pool = nullptr;
size_t position = 0;

public:
    Arena() : pool(new byte[SIZE]){
    }

    ~Arena() {
        delete[] pool;
    }

    #ifdef COPYABLE_ARENA
    Arena(const Arena& arena) {
       std::copy(arena.pool, arena.pool + SIZE, this->pool);
    }

    Arena(Arena&& arena) noexcept : pool(std::exchange(arena.pool, nullptr)), position(arena.position) {
    }

    Arena& operator=(Arena&& arena) noexcept {
        Arena temp (std::move(arena));
        std::swap(pool, temp.pool);
        return *this;
    }

    Arena& operator=(const Arena& other) {
        if (this == &other) {
            return *this;
        }

        Arena temp(other);
        std::swap(pool, temp.pool);
        return *this;
    }
    #else
        Arena(const Arena& arena) =delete;
        Arena& operator=(Arena& arena) noexcept = delete;

        Arena(const Arena&& arena) =delete;
        Arena& operator=(Arena&& arena) noexcept = delete;
    #endif

    template<class T, typename... Args>
    inline ARENA_POSITION addElement(Args&& ... args) {
        assert(position + sizeof(T) <= SIZE);
        const auto currentPosition = position;
        operator[]<T>(currentPosition) = {std::forward<Args>(args)...};
        position += sizeof(T);
        return currentPosition;
    }

    template<class T>
    T& getElementAt(ARENA_POSITION position) const {
        assert(position < this->position && position + sizeof(T) <= SIZE);
        return reinterpret_cast<T&>(this->pool[position]);
    }

    template<class T>
    T& operator[](ARENA_POSITION position) {
        return reinterpret_cast<T&>(this->pool[position]);
    }

    void clear() {
      position = 0;
    }

    template<size_t _SIZE>
    friend std::ostream& operator<<(std::ostream& os, const Arena<_SIZE>& arena);

};

template<size_t SIZE>
std::ostream& operator<<(std::ostream& os, const Arena<SIZE>& arena) {
    size_t index = 0;
    std::for_each(arena.pool, arena.pool + SIZE, [&os, &index](const typename Arena<SIZE>::byte& byte) {
        // bigendian
        os << std::hex << static_cast<unsigned int>(byte);
        ++index;
        if (index % 8 == 0) {
            os << '\n';
        }
    });

    return os;
}