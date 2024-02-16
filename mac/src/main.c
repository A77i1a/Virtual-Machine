#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define sp (registers[SP])
#define ip (registers[IP])
bool running = true;
int stack[256];


typedef enum {
    PSH,
    ADD,
    POP,
    SET,
    HLT
} InstructionSet;

const int program[] = {
    PSH, 5,
    PSH, 6,
    ADD,
    POP,
    HLT
};

int fetch() {
    return program[ip];
}

void eval(int instr) {
    switch (instr) {
        case HLT: {
            running = false;
            break;
        }
        case PSH: {
            sp++;
            stack[sp] = program[++ip];
            break;
        }
        case POP: {
            int val_popped = stack[sp--];
            printf("popped %d\n", val_popped);
            break;
        }
        case ADD: {
            int a = stack[sp--];
            int b = stack[sp--];
            int result = b + a;
            sp++;
            stack[sp] = result;
            break;
        }
    }
}

typedef enum {
   A, B, C, D, E, F, SP, IP,
   NUM_OF_REGISTERS
} Registers;

int registers[NUM_OF_REGISTERS];

int main() {
    registers[SP] = -1;
    registers[IP] = 0;

    while (running) {
       eval(fetch());
       ip++;
    }
}
