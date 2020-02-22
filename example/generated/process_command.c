#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "interfaces.h"



typedef int (*enter_int_return_int)(int);
typedef int (*enter_void_return_int)(void);
typedef void (*enter_int_return_void)(int);
typedef int (*enter_float_return_int)(float);
typedef void (*void_function)(void);


typedef void (* command_function_type)(const char * command, int length);


static int process_enter_int_return_int(const char * msg, int len, enter_int_return_int function);

static int process_enter_int_return_void(const char * msg, int len, enter_int_return_void function);

static int process_enter_float_return_int(const char * msg, int len, enter_float_return_int function);


static void process_get(const char * command, int length);

static void process_giet_value1(const char * command, int length);

static void process_reset(const char * command, int length);

static void process_set(const char * command, int length);

static void process_set_value_1(const char * command, int length);


static struct commands_struct{
    int length;
    const char * command;
    command_function_type function;
    int has_subcommand;
} commands_available[] = {
{ 3, "get", &process_get, 1},
{ 11, "giet_value1", &process_giet_value1, 0},
{ 5, "reset", &process_reset, 0},
{ 3, "set", &process_set, 1},
{ 11, "set_value_1", &process_set_value_1, 0},
};

static const int number_of_commands = sizeof(commands_available) / sizeof (struct commands_struct);


static int process_enter_int_return_int(const char * msg, int len, enter_int_return_int function)
{
    int retval = -1;
    int variable_1 = 0;
    if (len != 0) {
        int retvalue = sscanf(msg, " %d", &variable_1);
        if (retvalue == 1) {
            int result = function(variable_1);
            retval = 0;
        }
        else {
            printf("ERROR Expected: %d params, parsed: %d for  %%d\r\n",1,retvalue);
        }
    }
    else {
        printf("ERROR Please specify params matching  %%d\r\n");
    }

    return retval;
}



static int process_enter_int_return_void(const char * msg, int len, enter_int_return_void function)
{
    int retval = -1;
    int variable_1 = 0;
    if (len != 0) {
        int retvalue = sscanf(msg, " %d", &variable_1);
        if (retvalue == 1) {
            function(variable_1);
            retval = 0;
        }
        else {
            printf("ERROR Expected: %d params, parsed: %d for  %%d\r\n",1,retvalue);
        }
    }
    else {
        printf("ERROR Please specify params matching  %%d\r\n");
    }

    return retval;
}


static int process_enter_float_return_int(const char * msg, int len, enter_float_return_int function)
{
    int retval = -1;
    float variable_1 = 0;
    if (len != 0) {
        int retvalue = sscanf(msg, " %f", &variable_1);
        if (retvalue == 1) {
            int result = function(variable_1);
            retval = 0;
        }
        else {
            printf("ERROR Expected: %d params, parsed: %d for  %%f\r\n",1,retvalue);
        }
    }
    else {
        printf("ERROR Please specify params matching  %%f\r\n");
    }

    return retval;
}






static void process_get(const char * command, int length)
{
    int parent_len = 3;
    const char * available_commands = " value1\r\n";
    if (length < (parent_len + 1)) {
        printf("ERROR get needs a subcommand, availables are:\r\n");
        printf("%s", available_commands);
    } else {
        int subcommand_found = 0;
        
        const struct subcommands_enter_void_return_int_s{
            int len;
            const char * name;
            enter_void_return_int function;
        } list_enter_void_return_int[] = {
            { 7," value1", &function_get_value1},
            
        };

        const int list_enter_void_return_int_size = 1;
        
        for (int i = 0; (i < list_enter_void_return_int_size) && (subcommand_found == 0); i++) {
            int size_subcommand = list_enter_void_return_int[i].len;
            if ((length - parent_len) >= size_subcommand) {
                if (strncmp( &command[parent_len], list_enter_void_return_int[i].name, size_subcommand) == 0) {
                    int value_pos = size_subcommand + parent_len;
                    list_enter_void_return_int[i].function();
                    printf("OK!\r\n");
                    subcommand_found = 1;
                    break;
                }
            }
        }
        

        if (subcommand_found != 1) {
            printf("ERROR command not found, availables are:\r\n");
            printf("%s", available_commands);
        }
    }
}


static void process_giet_value1(const char * command, int length)
{
    int parent_len = 11;
    if (length == parent_len) {
        int result = function_get_value1();
        printf("%d\r\n", result);
    } else {
        printf("ERROR giet_value1 doesn't accept values\r\n");
    }
}


static void process_reset(const char * command, int length)
{
    int parent_len = 5;
    if (length == parent_len) {
        reset_function();
        printf("OK!\r\n");
        
    } else {
        printf("ERROR reset doesn't accept values\r\n");
    }
}


static void process_set(const char * command, int length)
{
    int parent_len = 3;
    const char * available_commands = " value1 value2 value3\r\n";
    if (length < (parent_len + 1)) {
        printf("ERROR set needs a subcommand, availables are:\r\n");
        printf("%s", available_commands);
    } else {
        int subcommand_found = 0;
        
        const struct subcommands_enter_float_return_int_s{
            int len;
            const char * name;
            enter_float_return_int function;
        } list_enter_float_return_int[] = {
            { 7," value2", &function_set_value2},
            
        };

        const int list_enter_float_return_int_size = 1;
        
        const struct subcommands_enter_int_return_int_s{
            int len;
            const char * name;
            enter_int_return_int function;
        } list_enter_int_return_int[] = {
            { 7," value1", &function_set_value1},
            { 7," value3", &function_set_value3},
            
        };

        const int list_enter_int_return_int_size = 2;
        
        for (int i = 0; (i < list_enter_float_return_int_size) && (subcommand_found == 0); i++) {
            int size_subcommand = list_enter_float_return_int[i].len;
            if ((length - parent_len) >= size_subcommand) {
                if (strncmp( &command[parent_len], list_enter_float_return_int[i].name, size_subcommand) == 0) {
                    int value_pos = size_subcommand + parent_len;
                    int result_process = process_enter_float_return_int(&command[value_pos], length - value_pos, list_enter_float_return_int[i].function);
                    if (result_process == 0) {
                        printf("OK!\r\n");
                    }
                    subcommand_found = 1;
                    break;
                }
            }
        }
        
        for (int i = 0; (i < list_enter_int_return_int_size) && (subcommand_found == 0); i++) {
            int size_subcommand = list_enter_int_return_int[i].len;
            if ((length - parent_len) >= size_subcommand) {
                if (strncmp( &command[parent_len], list_enter_int_return_int[i].name, size_subcommand) == 0) {
                    int value_pos = size_subcommand + parent_len;
                    int result_process = process_enter_int_return_int(&command[value_pos], length - value_pos, list_enter_int_return_int[i].function);
                    if (result_process == 0) {
                        printf("OK!\r\n");
                    }
                    subcommand_found = 1;
                    break;
                }
            }
        }
        

        if (subcommand_found != 1) {
            printf("ERROR command not found, availables are:\r\n");
            printf("%s", available_commands);
        }
    }
}


static void process_set_value_1(const char * command, int length)
{
    int parent_len = 11;
    int result_process = process_enter_int_return_int(&command[parent_len], length - parent_len, &function_set_value1);
    if (result_process == 0) {
        printf("OK!\r\n");
    }
    
}


void process_command(const char * command, int command_len)
{
    int command_found = -1;
    for(int i = 0; (i < number_of_commands); i++) {
        int comp_len = commands_available[i].length;
        if (command_len >= comp_len) {
            if (strncmp(command, commands_available[i].command, comp_len) == 0) {
                if ((command_len == comp_len) || (command[comp_len] == ' ')) {
                    commands_available[i].function(command, command_len);
                    command_found = i;
                    break;
                }
            }
        }
    }

    if (command_found == -1) {
        
    }
}