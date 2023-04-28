//
// Created by Maksym Pasichnyk on 26.04.2023.
//

module;

#include <cstdio>
#include <cstdlib>

export module cpp_script:ir;

export enum OpCode {
    OP_HALT,
    OP_GET_LOCAL,
    OP_SET_LOCAL,
    OP_GET_GLOBAL,
    OP_SET_GLOBAL,
    OP_PUSH,
    OP_CALL,
    OP_RET,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_NEG,
    OP_PRINT,
};

export void disassemble(const int* code, size_t len) {
    static constexpr const char* opcodes[] = {
        "HALT",
        "GET_LOCAL",
        "SET_LOCAL",
        "GET_GLOBAL",
        "SET_GLOBAL",
        "PUSH",
        "CALL",
        "RET",
        "ADD",
        "SUB",
        "MUL",
        "DIV",
        "NEG",
        "PRINT"
    };

    for (size_t ip = 0; ip < len; ++ip) {
        auto opcode = code[ip];
        fprintf(stdout, "%04zu %s", ip, opcodes[opcode]);
        if (opcode == OP_GET_GLOBAL || opcode == OP_SET_GLOBAL ||
            opcode == OP_GET_LOCAL || opcode == OP_SET_LOCAL ||
            opcode == OP_PUSH || opcode == OP_PRINT ||
            opcode == OP_CALL || opcode == OP_RET) {
            fprintf(stdout, " %d", code[++ip]);
        }
        fprintf(stdout, "\n");
    }
}

export void execute(const int* code, size_t ip) {
    static constexpr void* jumps[] = {
        &&JUMP_OP_HALT,
        &&JUMP_OP_GET_LOCAL,
        &&JUMP_OP_SET_LOCAL,
        &&JUMP_OP_GET_GLOBAL,
        &&JUMP_OP_SET_GLOBAL,
        &&JUMP_OP_PUSH,
        &&JUMP_OP_CALL,
        &&JUMP_OP_RET,
        &&JUMP_OP_ADD,
        &&JUMP_OP_SUB,
        &&JUMP_OP_MUL,
        &&JUMP_OP_DIV,
        &&JUMP_OP_NEG,
        &&JUMP_OP_PRINT,
    };

    size_t sp = 0;
    size_t fp = 0;

    int stack[256] = {};
    int globals[256] = {};

    goto *jumps[code[ip++]];

JUMP_OP_HALT:
    {
        goto JUMP_EXIT;
    }
JUMP_OP_GET_LOCAL:
    {
        auto arg = code[ip++];
        stack[sp++] = globals[fp + arg];
        goto *jumps[code[ip++]];
    }
JUMP_OP_SET_LOCAL:
    {
        auto arg = code[ip++];
        globals[fp + arg] = stack[--sp];
        goto *jumps[code[ip++]];
    }
JUMP_OP_GET_GLOBAL:
    {
        auto arg = code[ip++];
        globals[arg] = stack[--sp];
        goto *jumps[code[ip++]];
    }
JUMP_OP_SET_GLOBAL:
    {
        auto arg = code[ip++];
        stack[sp++] = globals[arg];
        goto *jumps[code[ip++]];
    }
JUMP_OP_PUSH:
    {
        auto value = code[ip++];
        stack[sp++] = value;
        goto *jumps[code[ip++]];
    }
JUMP_OP_CALL:
    {
        abort();
        goto *jumps[code[ip++]];
    }
JUMP_OP_RET:
    {
        abort();
        goto *jumps[code[ip++]];
    }
JUMP_OP_ADD:
    {
        auto rhs = stack[--sp];
        auto lhs = stack[--sp];
        stack[sp++] = lhs + rhs;
        goto *jumps[code[ip++]];
    }
JUMP_OP_SUB:
    {
        auto rhs = stack[--sp];
        auto lhs = stack[--sp];
        stack[sp++] = lhs - rhs;
        goto *jumps[code[ip++]];
    }
JUMP_OP_MUL:
    {
        auto rhs = stack[--sp];
        auto lhs = stack[--sp];
        stack[sp++] = lhs * rhs;
        goto *jumps[code[ip++]];
    }
JUMP_OP_DIV:
    {
        auto rhs = stack[--sp];
        auto lhs = stack[--sp];
        stack[sp++] = lhs / rhs;
        goto *jumps[code[ip++]];
    }
JUMP_OP_NEG:
    {
        auto rhs = stack[--sp];
        stack[sp++] = -rhs;
        goto *jumps[code[ip++]];
    }
JUMP_OP_PRINT:
    {
        auto argc = code[ip++];
        for (int i = 0; i < argc; i++) {
            fprintf(stdout, "%d ", stack[sp - argc + i]);
        }
        sp -= argc;
        goto *jumps[code[ip++]];
    }
JUMP_EXIT:
}