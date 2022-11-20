#include <stdio.h>
#include <stdlib.h>

#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

enum code_ops {
    HALT, STORE, JMP_FALSE, GOTO,
    DATA, LD_INT, LD_VAR,
    READ_INT, WRITE_INT,
    LT, EQ, GT, ADD, SUB, MULT, DIV
};

char *op_name[] = {
    "halt", "store", "jmp_false", "goto",
    "data", "ld_int", "ld_var",
    "read_int", "write_int",
    "lt", "eq", "gt", "add", "sub", "mult", "div"
};

struct instruction {
    enum code_ops op;
    int arg;
}instruction;

struct instruction code[999];
int stack[999];
int variableArray[999];

int pc = 0;
struct instruction ir;
int top = 0;

void fetch_execute_cycle() {
    int temp = 0;
    printf("\n");
    do {
        ir = code[pc++];
        switch(ir.op) {
        case HALT:
            printf("halt\n");
            break;
        case READ_INT:
            printf("Input: ");
            scanf("%d", &variableArray[ir.arg]);
            // printf("  in %d\n", ir.arg);
            break;
        case WRITE_INT:
            printf("Output: %d\n", stack[top--]);
            break;
        case STORE:
            variableArray[ir.arg] = stack[top--];
            // printf("STORE - %d\n", variableArray[ir.arg]);
            break;
        case JMP_FALSE:
            if (stack[top--] == 0) {
                pc = ir.arg;
                // printf("JMP_FALSE - PC:%3d\n", pc);
            }
            else {
                // printf("!JMP_FALSE\n");
            }
            break;
        case GOTO:
            pc = ir.arg;
            // printf("GOTO - PC:%3d\n", pc);
            break;
        case DATA:
            top = top + ir.arg;
            // printf("DATA - TOP:%3d\n", top);
            break;
        case LD_INT:
            stack[++top] = ir.arg;
            // printf("LD_INT - %d in %d\n", ir.arg, top-1);
            break;
        case LD_VAR:
            stack[++top] = variableArray[ir.arg];
            // printf("LD_VAR - %d in %d\n", variableArray[ir.arg], stack[top-1]);
            break;
        case LT:
            if (stack[top-1] < stack[top]) {
                stack[--top] = 1;
            }
            else {
                stack[--top] = 0;
            }
            // printf("LT - %d\n", stack[top]);
            break;
        case GT:
            if(stack[top-1] > stack[top]) {
                stack[--top] = 1;
            }
            else {
                stack[--top] = 0;
            }
            // printf("GT - %d\n", stack[top]);
            break;
        case EQ:
            if (stack[top-1] == stack[top]) {
                stack[--top] = 1;
            }
            else {
                stack[--top] = 0;
            }
            // printf("GT - %d\n", stack[top]);
            break;
        case ADD:
            // printf("ADD - %d + %d = ", stack[top-1], stack[top]);
            stack[top-1] = stack[top-1] + stack[top];
            top--;
            // printf("%d\n", stack[top]);
            break;
        case SUB:
            // printf("SUB - %d - %d = ", stack[top-1], stack[top]);
            stack[top-1] = stack[top-1] - stack[top];
            top--;
            // printf("%d\n", stack[top]);
            break;
        case MULT:
            // printf("MULT - %d * %d = ", stack[top-1], stack[top]);
            stack[top-1] = stack[top-1] * stack[top];
            top--;
            // printf("%d\n", stack[top]);
            break;
        case DIV:
            // printf("DIV - %d / %d = ", stack[top-1], stack[top]);
            stack[top-1] = stack[top-1] / stack[top];
            top--;
            // printf("%d\n", stack[top]);
            break;
        default:
            printf("Internal Error: Memory Dump\n");
            break;
        }
/*
        printf("%3d-\tIR.op:%3d\tIR.arg:%3d\tTOP:%3d,%3d\n", pc-1, ir.op, ir.arg, top, stack[top]);
        int temp = top;
        while (temp > 0) {
            temp--;
            printf("%47d,%3d\n", temp, stack[temp]);
        }
*/
    } while (ir.op != HALT);
}

#endif