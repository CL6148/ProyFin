#include <stdio.h>
#include <stdlib.h>

#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

enum code_ops {
    HALT, STORE, JMP_FALSE, GOTO,
    LD_INT, LD_VAR, READ_INT, WRITE_INT,
    AND, OR, EQ, NOT,
    LT, LTE, GT, GTE,
    ADD, SUB, MULT, DIV
};

char *op_name[] = {
    "halt", "store", "jmp_false", "goto",
    "ld_int", "ld_var", "read_int", "write_int",
    "and", "or", "eq", "not",
    "lt", "lte", "gt", "gte",
    "add", "sub", "mult", "div"
};

struct instruction {
    enum code_ops op;
    int arg;
}instruction;

struct instruction code[999];
int stack[999];
int varArr[999];


int tempArr[999];

int pc = 0;
struct instruction ir;
int top = 0;

void fetch_execute_cycle() {
    printf("\n");
    do {
        ir = code[pc++];
        switch(ir.op) {
        case HALT:
            printf("halt\n");
            break;
        case READ_INT:
            printf("Input: ");
            scanf("%d", &varArr[ir.arg]);
            // printf("  in offset %d\n", ir.arg);
            break;
        case WRITE_INT:
            printf("Output: %d\n", stack[top--]);
            break;
        case STORE:
            varArr[ir.arg] = stack[top--];
            // printf("STORE - %d\t%d\n", varArr[ir.arg], ir.arg);
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
        case LD_INT:
            stack[++top] = ir.arg;
            // printf("LD_INT - %d in %d\n", ir.arg, top-1);
            break;
        case LD_VAR:
            stack[++top] = varArr[ir.arg];
            // printf("LD_VAR - %d in %d\n", varArr[ir.arg], stack[top-1]);
            break;
        case AND:
            if (stack[top-1] && stack[top]) {
                stack[--top] = 1;
            }
            else {
                stack[--top] = 0;
            }
            break;
        case OR:
            if (stack[top-1] || stack[top]) {
                stack[--top] = 1;
            }
            else {
                stack[--top] = 0;
            }
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
        case LTE:
            // printf("LTE - %d <= %d : ", stack[top-1], stack[top]);
            if (stack[top-1] <= stack[top]) {
                stack[--top] = 1;
            }
            else {
                stack[--top] = 0;
            }
            // printf("%d\n", stack[top]);
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
        case GTE:
            // printf("GTE - %d >= %d : ", stack[top-1], stack[top]);
            if (stack[top-1] >= stack[top]) {
                stack[--top] = 1;
            }
            else {
                stack[--top] = 0;
            }
            // printf("%d\n", stack[top]);
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
        case NOT:
            if (stack[top-1] != stack[top]) {
                stack[--top] = 1;
            }
            else {
                stack[--top] = 0;
            }
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