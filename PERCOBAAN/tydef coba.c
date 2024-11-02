#include <stdio.h>

struct Laptop
typedef struct Laptop {
    char* merk;
    char* cpu;
    int* memory;
};

struct Phone {
    char* merk;
    char* cpu;
    int memory;
};

typedef struct Laptop lenovo = {
    .name = "Yoga",
    .cpu = "Intel",
    .memory = 16
}

struct Phone samsung = {
    .name = "Samsung A55",
    .cpu = "Snapdragon",
    .memory = 8
};

