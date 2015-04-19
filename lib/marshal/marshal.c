
/*
 * @desc: The function does the marshing. Function does all the allocation.
 *        It is caller's responsibility to free the memory allocated.
 * @data: Input, the function expecting this structure.
 * @ascii: Function returns this char.
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "marshal.h"

int 
gwkv_marshal_server(struct operation* data, int status, char** ascii)
{
        char* val = (char*)malloc(1000*sizeof(char));
        char comm_name[]="set ";
        char flag_exp[]=" 0 0 ";
        char v_len[20];
        char r_n[]="\r\n";
        char b1[] = "get ";
        char b2[] = "\r\n";
        switch(data->method_type) {
            case SET:
                strcat(val,comm_name);
                strcat(val,data->key);
                strcat(val,flag_exp);
                sprintf(v_len,"%d",(int)data->value_length);
                strcat(val,v_len);
                strcat(val,r_n);
                strcat(val,data->value);
                strcat(val,r_n);

                //Convert the status into a string like this:
                //
                break;
            case GET:
                //convert the struct value to like this:
                //VALUE <key> <flags> <bytes> \r\n
                //<data blcok> \r\n
                //END \r\n
                strcat(val,b1);
                strcat(val,data->key);
                strcat(val,b2);     
                break;
       }
       *ascii = val;
       return 0;
}

#define COMMAND_LENGTH 3
#define FLAG_LENGTH 1 //right now 0
#define EXP_TIME_LENGTH 1 //unix time format. Right now 0.
#define SPACE_LENGTH 1 
#define NEWLINE_LENGTH 2

int 
gwkv_marshal_client(struct operation* data, char** ascii)
{       
        char* final_marshed_value = NULL;
        char space = ' ';
        char zero = '0';
        size_t size = 0;
        char value_length[32] = {0};
        char* marshaled_value = 0;
       
        switch(data->method_type) {
            case SET:
                sprintf(value_length, "%d", data->value_length);
                
                size = COMMAND_LENGTH + 5*SPACE_LENGTH + 
                       FLAG_LENGTH +  EXP_TIME_LENGTH +
                       2* NEWLINE_LENGTH + 
                       data->key_length + 
                       strlen(value_length) + data->value_length; 

                //convert data to this format:
                //<command name> <key> <flags> ...
                marshaled_value = calloc(1, size);
                final_marshed_value = marshaled_value;

                snprintf(marshaled_value, COMMAND_LENGTH + 1,"%s", "set");
                marshaled_value += COMMAND_LENGTH; 
                snprintf(marshaled_value, SPACE_LENGTH + 1,"%c", space);
                marshaled_value += SPACE_LENGTH; 
                snprintf(marshaled_value, data->key_length +1 ,"%s", data->key);
                marshaled_value += data->key_length; 
                snprintf(marshaled_value, SPACE_LENGTH + 1,"%c", space);
                marshaled_value += SPACE_LENGTH; 
                snprintf(marshaled_value, FLAG_LENGTH + 1 ,"%c", zero);
                marshaled_value += FLAG_LENGTH; 
                snprintf(marshaled_value, SPACE_LENGTH + 1, "%c", space);
                marshaled_value += SPACE_LENGTH; 
                snprintf(marshaled_value, EXP_TIME_LENGTH + 1 ,"%c", zero);
                marshaled_value += EXP_TIME_LENGTH; 
                snprintf(marshaled_value, SPACE_LENGTH +1 ,"%c", space);
                marshaled_value += SPACE_LENGTH; 
                
                
                snprintf(marshaled_value, strlen(value_length) + 1 ,"%s", value_length);
                marshaled_value += strlen(value_length); 
                snprintf(marshaled_value, SPACE_LENGTH + 1,"%c", space);
                marshaled_value += SPACE_LENGTH; 
                snprintf(marshaled_value, NEWLINE_LENGTH + 1 ,"%s", "\r\n");
                marshaled_value += NEWLINE_LENGTH; 
                //snprintf(marshaled_value, SPACE_LENGTH ,"%s", space);
                //marshaled_value += SPACE_LENGTH; 
                snprintf(marshaled_value, data->value_length + 1 ,"%s", data->value);
                marshaled_value += data->value_length; 
                snprintf(marshaled_value, NEWLINE_LENGTH ,"%c", '\r');
                marshaled_value += 1; 
                snprintf(marshaled_value, NEWLINE_LENGTH ,"%c", '\n');
              
                break;
            
            case GET:
                //convert data to this format
                // get <key>* \r\n
                size = COMMAND_LENGTH + SPACE_LENGTH + NEWLINE_LENGTH +
                       data->key_length ;

                marshaled_value = calloc(1, size);
                final_marshed_value = marshaled_value;
                //fwrite("get", sizeof(char), COMMAND_LENGTH, marshaled_value);
                //marshaled_value += COMMAND_LENGTH; 
                //fwrite(marshaled_value, SPACE_LENGTH ,"%s", space);
                snprintf(marshaled_value, COMMAND_LENGTH + 1,"%s", "get");
                marshaled_value += COMMAND_LENGTH; 
                snprintf(marshaled_value, SPACE_LENGTH + 1,"%c", space);
                marshaled_value += SPACE_LENGTH; 
                snprintf(marshaled_value, data->key_length + 1,"%s", data->key);
                marshaled_value += data->key_length; 
                snprintf(marshaled_value, NEWLINE_LENGTH ,"%c", '\r');
                marshaled_value += 1; 
                snprintf(marshaled_value, NEWLINE_LENGTH ,"%c", '\n');

                
                break;
            default:
                assert(0);
        }
        *ascii = final_marshed_value;
        return 0;
}

int 
gwkv_demarshal_server(char* ascii, struct operation** data)
{
        /*switch(data->method_type) {
            case SET:
                //convert ascii to operation 
            case GET:
                //convert ascii to operation
        }*/
        return 0;
}

int 
gwkv_demarshal_client(char* ascii, struct operation** op, int* status)
{
	    char* val = (char*)malloc(1000*sizeof(char));
        switch(data->method) {
            case SET:
                //convert ascii to operation
                char** a = (char**)malloc(4*sizeof(char*));
                a[0]="STORED\r\n";
                a[1]="NOT_STORED\r\n";
                a[2]="EXISTS\r\n";
                a[3]="NOT_FOUND\r\n";
                int i = *status;
                strcat(val,a[i]);
            case GET:
                //convert ascii to status
                char space[]=" ";
                strcat(val,data->key);
                char flag[]=" 0 ";
                char v_len[10];
                sprintf((int)data->value_length,"%d",v_len);
                strcat(val,v_len);
                char cas_unique[] = " cas_unique\r\n";
                strcat(val,cas_unique);
                char r_n[]="\r\n";
                strcat(val,data->value);
                strcat(val,r_n);
                char end[]="END\r\n";
                strcat(val,end);
            default:
                break;
        }
        *ascii = val; 
        return 0;
}
