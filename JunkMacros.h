/*
----------------------------------------------
JunkMacros.h
Created July 2021
Author tostring#1337
Edited December 2024
Editor Bartam0us

----------------------------------------------
*/

#ifndef JUNK_MACROS_H
#define JUNK_MACROS_H

#include <cstdint>
#include <cstdlib>
#include <ctime>

// Random number generation based on compile time
constexpr uint32_t fshiftrandom(uint32_t input) {
    return (input >> 1) ^ (-(input & 1u) & 0xA300FDE7);
}

constexpr uint32_t compiledrand = fshiftrandom(__TIME__[0] + __TIME__[1] * 60 + __TIME__[2] * 3600);
constexpr uint32_t compiledrand2 = fshiftrandom(compiledrand);
constexpr uint32_t compiledrandMAX = compiledrand2 % 1000 + 1; // Maximum iteration range

// Junk functions
void junkcallme() {
    // Empty function for junk calls
}

float junkcallme2() {
    return 3.402823466e+38F + 1; // Return a very large float
}

// NOPCOMPILE: Generates "nop" instructions
template<int iterations>
struct NOPCOMPILE {
    inline __attribute__((always_inline)) void operator()() {
        __asm__ __volatile__("nop");
        NOPCOMPILE<iterations - 1>()();
    }
};

template<>
struct NOPCOMPILE<0> {
    inline __attribute__((always_inline)) void operator()() {}
};

// MOVCOMPILE: Generates random mov instructions
template<int iterations>
struct MOVCOMPILE {
    inline __attribute__((always_inline)) void operator()() {
        volatile int temp = compiledrand;
        __asm__ __volatile__("mov %%eax, %0" : : "r"(temp) : "eax");
        MOVCOMPILE<iterations - 1>()();
    }
};

template<>
struct MOVCOMPILE<0> {
    inline __attribute__((always_inline)) void operator()() {}
};

// NULLSUBCOMPILE: Generates calls to junkcallme
template<int iterations>
struct NULLSUBCOMPILE {
    inline __attribute__((always_inline)) void operator()() {
        junkcallme();
        NULLSUBCOMPILE<iterations - 1>()();
    }
};

template<>
struct NULLSUBCOMPILE<0> {
    inline __attribute__((always_inline)) void operator()() {}
};

// IFCOMPILE: Adds conditional junk instructions
template<int iterations>
struct IFCOMPILE {
    inline __attribute__((always_inline)) void operator()() {
        if (compiledrand % 2) {
            junkcallme();
        } else {
            junkcallme2();
        }
        IFCOMPILE<iterations - 1>()();
    }
};

template<>
struct IFCOMPILE<0> {
    inline __attribute__((always_inline)) void operator()() {}
};

// JMPCOMPILE: Generates jump instructions
template<int iterations>
struct JMPCOMPILE {
    inline __attribute__((always_inline)) void operator()() {
        __asm__ __volatile__("jmp .label_%=\n"
                ".label_%=:");
        JMPCOMPILE<iterations - 1>()();
    }
};

template<>
struct JMPCOMPILE<0> {
    inline __attribute__((always_inline)) void operator()() {}
};

// Macros
#define NOP_JUNK(am) NOPCOMPILE<(am == 0 ? compiledrandMAX : am)>()()
#define MOV_JUNK(am) MOVCOMPILE<(am == 0 ? compiledrandMAX : am)>()()
#define NULLSUB_JUNK(am) NULLSUBCOMPILE<(am == 0 ? compiledrandMAX : am)>()()
#define IF_JUNK(am) IFCOMPILE<(am == 0 ? compiledrandMAX : am)>()()
#define JMP_JUNK(am) JMPCOMPILE<(am == 0 ? compiledrandMAX : am)>()()

#endif
