#include <stdio.h>
#include <string.h>

#include "generated/process_command.h"

#define PROCESS(x) do {\
    printf("Sending "x"\r\n");\
    process_command(x, strlen(x));\
    printf("\r\n");\
    }while(0)


void reset_function(void) {
    printf("Reset called\r\n");
}

int function_get_value1(void) {
    printf("get_value1 called\r\n");
    return 1;
}

int function_set_value1(int param) {
    printf("set value 1 %d\r\n", param);
    return 0;
}

int function_set_value2(float param) {
    printf("set value 2 called %f\r\n", param);
    return 0;
}

int function_set_value3(int param) {
    printf("set value 3 called %d\r\n", param);
    return 1;
}

int main(void) {
    PROCESS("get value1");
    PROCESS("set value1 1234");
    PROCESS("set_value_1 1234");
    PROCESS("set");
    PROCESS("set value2");
    PROCESS("set value2 aaa");
    PROCESS("reset");
    PROCESS("reset ew");
    PROCESS("oqiwiejhweq");
    PROCESS("giet_value1");
}