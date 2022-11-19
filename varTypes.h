#define UNDEF 0
#define INT_TYPE 1
#define REAL_TYPE 2
#define ARRAY_TYPE 3
#define FUNCTION_TYPE 4
#define VOID_TYPE 5

#define NONE 0
#define ARITHM_OP 1
#define INCR_OP 2
#define BOOL_OP 3
#define NOT_OP 4
#define REL_OP 5
#define EQU_OP 6

int get_result_type(int type1, int type2, int op_type);
void type_error(int type1, int type2, int op_type);