//
// Created by armandouv on 31/03/22.
//

#include <memory>
#include <cstring>

typedef unsigned long long ull;

constexpr ull INITIAL_SIZE = 10;
constexpr ull GROW_FACTOR = 2;

template<typename T>
class resizing_array {
    ull real_size = INITIAL_SIZE;
    ull v_size = 0;
    std::unique_ptr<T> elements;
public:
    // Ordinary constructor
    resizing_array(std::initializer_list<T> list)
            : elements{new T[list.size() * GROW_FACTOR]},
              v_size{list.size()},
              real_size{list.size() * GROW_FACTOR} {
        for (ull i = 0; i < v_size; i++) {
            elements[i] = list[i];
        }
    }

    // Default constructor
    resizing_array() : elements{new T[INITIAL_SIZE]} {
    }

    // Copy constructor
    resizing_array(const resizing_array<T> &base_arr)
            : elements{new T[base_arr.size() * GROW_FACTOR]},
              v_size{base_arr.size()},
              real_size{base_arr.size() * GROW_FACTOR} {
        for (ull i = 0; i < v_size; i++) {
            elements[i] = base_arr[i];
        }
    }

    // Move constructor
    resizing_array(resizing_array<T> &&base_arr) noexcept
            : elements{base_arr.elements},
              v_size{base_arr.v_size},
              real_size{base_arr.real_size} {
        base_arr.elements = nullptr;
        base_arr.v_size = 0;
        base_arr.real_size = 0;
    }

    // Copy assignment
    resizing_array<T> &operator=(const resizing_array<T> &base_arr) {
        v_size = base_arr.v_size;
        real_size = base_arr.real_size;
        elements = new T[real_size];

        for (ull i = 0; i < v_size; i++) {
            elements[i] = base_arr[i];
        }
        return *this;
    }


    // Move assignment
    resizing_array<T> &operator=(resizing_array<T> &&base_arr) noexcept {
        v_size = base_arr.v_size;
        real_size = base_arr.real_size;
        elements = base_arr.elements;

        base_arr.v_size = 0;
        base_arr.real_size = 0;
        base_arr.elements = nullptr;

        return *this;
    }


    ull size() { return v_size; }

    T &operator[](ull i) {
        if (i < 0 || i >= v_size)
            throw std::out_of_range("Index " + std::to_string(i) + " out of bounds\n");
        return elements[i];
    }

    void push_back(T &el) {
        if (v_size == real_size) {
            real_size *= GROW_FACTOR;
            auto new_elements = new T[real_size];
            std::memcpy(new_elements, elements, v_size * sizeof(T));
            elements = new_elements;
        }

        elements[v_size] = el;
        v_size++;
    }

    T &pop_back() {
        if (v_size == (real_size / GROW_FACTOR / 2)) {
            real_size /= GROW_FACTOR;
            auto new_elements = new T[real_size];
            std::memcpy(new_elements, elements, v_size * sizeof(T));
            elements = new_elements;
        }

        return elements[--v_size];
    }
};