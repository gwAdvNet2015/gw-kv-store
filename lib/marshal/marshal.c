
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
        char space[] = " ";
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
                strcat(val,space);
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
        struct operation *data = (struct operation*)malloc(sizeof(struct operation));
        *op = data;
        char s0[]="STORED\r\n";
        char s1[]="NOT_STORED\r\n";
        char s2[]="EXISTS\r\n";
        char s3[]="NOT_FOUND\r\n";
        if(strcmp(ascii,s0)==0){
                data->method_type=SET;
                *status=0;
                return 0;
        }
        else if(strcmp(ascii,s1)==0){
                data->method_type=SET;
                *status=1;
                return 0;
        }
        else if(strcmp(ascii,s2)==0){
                data->method_type=SET;
                *status=2;
                return 0;
        }
        else if(strcmp(ascii,s3)==0){
                data->method_type=SET;
                *status=3;
                return 0;
        }
        
        int i=0;
        int offset = 0;
        char *a=ascii;
        i=0;
        char b[50];
        while(b[i]!=' '&&b[i]!='\0'){
                b[i]=a[i];
                i++;
        }       
        b[i]='\0';
        offset += i+1;
        char c1[]="VALUE";
        if(strcmp(b,c1)!=0){
                return -1;
        }
        //key
        i=0;
        while(b[i]!=' '&&b[i]!='\0'){
                b[i]=a[i];
                i++;
        }       
        b[i]='\0';
        offset += i+1;
        char *b1 = (char*)malloc(50*sizeof(char));
        strcat(b1,b);
        data->key = b1;
        data->key_length = strlen(data->key);
        //flag
        i=0;
        while(b[i]!=' '&&b[i]!='\0'){
                b[i]=a[i];
                i++;
        }       
        b[i]='\0';
        offset += i+1;
        //length
        i=0;
        while(b[i]!=' '&&b[i]!='\0'){
                b[i]=a[i];
                i++;
        }       
        b[i]='\0';
        offset += i+1;
        data->value_length = atoi(b);
        //\r\n
        offset += 2;
        //data_value
        i=0;
        while(b[i]!='\r'&&b[i]!='\0'){
                b[i]=a[i];
                i++;
        }       
        b[i]='\0';
        offset += i+1;
        char *b2 = (char*)malloc(50*sizeof(char));
        strcat(b2,b);
        data->value = b1;
        return 0;
}
