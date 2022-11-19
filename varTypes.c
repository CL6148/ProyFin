#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "varTypes.h"

int get_result_type(int type1, int type2, int op_type) {
    switch(op_type) {
    case NONE:
        if (type1 == INT_TYPE) {
            if (type2 == INT_TYPE) {
                return 1;
            }
            else {
                type_error(type1, type2, op_type);
            }
        }
        else if (type1 == REAL_TYPE) {
            if (type2 == INT_TYPE || type2 == REAL_TYPE) {
                return 1;
            }
            else {
                type_error(type1, type2, op_type);
            }
        }
        break;
    case ARITHM_OP:
        if (type1 == INT_TYPE) {
            if (type2 == INT_TYPE) {
                return INT_TYPE;
            }
            else if (type2 == REAL_TYPE) {
                return REAL_TYPE;
            }
            else {
                type_error(type1, type2, op_type);
            }
        }
        else if (type1 == REAL_TYPE) {
            if (type2 == INT_TYPE || type2 == REAL_TYPE) {
                return REAL_TYPE;
            }
            else {
                type_error(type1, type2, op_type);
            }
        }
        else {
            type_error(type1, type2, op_type);
        }
        break;
    case INCR_OP:
        if (type1 == INT_TYPE) {
            return INT_TYPE;
        }
        else if (type1 == REAL_TYPE) {
            return REAL_TYPE;
        }
        else {
            type_error(type1, type2, op_type);
        }
        break;
    case BOOL_OP:
        if (type1 == INT_TYPE) {
            if (type2 == INT_TYPE) {
                return INT_TYPE;
            }
            else {
                type_error(type1, type2, op_type);
            }
        }
        else {
            type_error(type1, type2, op_type);
        }
        break;
    case NOT_OP:
        if (type1 == INT_TYPE) {
            return INT_TYPE;
        }
        else {
            type_error(type1, type2, op_type);
        }
        break;
    case REL_OP:
        if (type1 == INT_TYPE) {
            if (type2 == INT_TYPE || type2 == REAL_TYPE) {
                return INT_TYPE;
            }
            else {
                type_error(type1, type2, op_type);
            }
        }
        else if (type1 == REAL_TYPE) {
            if (type2 == INT_TYPE || type2 == REAL_TYPE) {
                return INT_TYPE;
            }
            else {
                type_error(type1, type2, op_type);
            }
        }
        else {
            type_error(type1, type2, op_type);
        }
        break;
    case EQU_OP:
        if (type1 == INT_TYPE) {
            if (type2 == INT_TYPE) {
                return INT_TYPE;
            }
            else {
                type_error(type1, type2, op_type);
            }
        }
        else if (type1 == REAL_TYPE) {
            if (type2 == REAL_TYPE) {
                return INT_TYPE;
            }
            else {
                type_error(type1, type2, op_type);
            }
        }
        else {
            type_error(type1, type2, op_type);
        }
        break;
    default:
        fprintf(stderr, "Error in operator selection\n");
        exit(1);
    }
}

void type_error(int type1, int type2, int op_type) {
    fprintf(stderr, "Type conflict between %d and %d using operator type %d\n", type1, type2, op_type);
    exit(1);
}