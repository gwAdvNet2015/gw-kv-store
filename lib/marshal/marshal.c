
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
#include "../../common.h"

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
                eprintf("ERR000: gwkv_marshal_client, improper data->method_type.\n");
                return -1;
        }
        *ascii = final_marshed_value;
        return 0;
}

int 
gwkv_demarshal_server(char* ascii, struct operation** op)
{
        /*switch(data->method_type) {
            case SET:
                //convert ascii to operation 
            case GET:
                //convert ascii to operation
        }*/
        //char s0[] = "VALUE";
        char* traverse = ascii;
        struct operation *data = (struct operation*)malloc(sizeof(struct operation));
        char s1[] = "set";
        char s2[] = "get";

        /*if (strcmp(ascii, s0) >= strlen(s0)) {
        
        } else*/ 
        if ( 0 == strncmp(ascii, s1, strlen(s1))) {
                data->method_type = SET;
                traverse += strlen(s1) + 1;
                
                //next charcater is space
                if (traverse[-1] != ' ') {
                        eprintf("ERR001: gwkv_demarshal_server, improper ascii syntax; expected ' '\n");
                        return -1;
                }


                char* temp = strchr(traverse, ' ');    
                if ( NULL != temp) {
                        data->key_length = temp - traverse;
                        data->key = malloc(data->key_length + 1);
                        strncpy(data->key, traverse, data->key_length);
                        //data->key[data->key_length] = '\0'; 
                } else {
                        eprintf("ERR002: gwkv_demarshal_server, improper ascii syntax; did not find deliminator of ' '\n");
                        return -1;
                }
                
                traverse = temp + 1;
                
                if (traverse[0] != '0') { // flags
                        eprintf("ERR003: gwkv_demarshal_server, improper ascii syntax; expected flag of '0'\n");
                        return -1;
                }
                if (traverse[1] != ' ') {
                        eprintf("ERR004: gwkv_demarshal_server, improper ascii syntax; expected ' '\n");
                        return -1;
                }
                if (traverse[2] != '0') {
                        eprintf("ERR005: gwkv_demarshal_server, improper ascii syntax; expected expiration time of '0'\n");
                        return -1;
                }
                if (traverse[3] != ' ') {
                        eprintf("ERR006: gwkv_demarshal_server, improper ascii syntax; expected ' '\n");
                        return -1;
                }

                traverse += 4;//pointing to <bytes> i.e. length.

                temp = strchr(traverse, ' ');
                if( NULL != temp) {
                        sscanf(traverse, "%d", &data->value_length);
                } else {
                        eprintf("ERR007: gwkv_demarshal_server, improper ascii syntax; did not find deliminator of ' '\n");
                        return -1;
                }
                
                traverse = temp + 1;//pointing to \r\n.
                
                /*temp = strchr(traverse, ' ');
                if (NULL != temp) {
                        traverse = temp + 1;
                        assert(traverse[0] == '\r');
                        assert(traverse[1] == '\n');
                } else {
                        assert(0);
                }*/
                if (traverse[0] != '\r' || traverse[1] != '\n') {
                        eprintf("ERR008: gwkv_demarshal_server, improper ascii syntax; expected carriage return and new line.\n");
                        return -1;
                }
                
                traverse += 2; // pointing to data

                temp = strchr(traverse, '\r');
                if ( NULL != temp) {
                        //verify the length
                        if (data->value_length != temp - traverse) {
                                eprintf("ERR009: gwkv_demarshal_server, specified data length does not match ascii length.\n");
                                return -1;
                        }
                        data->value = malloc(data->value_length + 1);
                        strncpy(data->value, traverse, data->value_length);
                         
                } else {
                        eprintf("ERR010: gwkv_demarshal_server, improper ascii syntax; did not find deliminator of carriage return\n");
                        return -1;
                }
                traverse = temp;
                if (traverse[1] != '\n') {
                        eprintf("ERR011: gwkv_demarshal_server, improper ascii syntax; expected newline\n");
                        return -1;
                }
                


        } else if (0 == strncmp(ascii, s2, strlen(s2))) {
                data->method_type = GET;
                traverse += strlen(s2) + 1;//pointing key
                char* temp = strchr(traverse, '\r');
                
                //Found the newline
                if (NULL != temp) {
                        data->key_length = temp - traverse;
                        data->key = malloc(data->key_length + 1);
                        strncpy(data->key, traverse, data->key_length);
                } else {
                        eprintf("ERR012: gwkv_demarshal_server, improper ascii syntax; did not find deliminator of newline\n");
                        return -1;
                }
        } else {
                eprintf("ERR013: gwkv_demarshal_server, improper method_type in ascii.\n");
                return -1;
        }

        *op = data; 
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
       
        char *value = "VALUE";
        char* traverse = ascii;
        if( 0 != strncmp(traverse, value, strlen(value))) {
                eprintf("ERR014: gwkv_demarshal_client, expected string of 'VALUE'.\n");
                return -1;
        }    
        
        data->method_type  = GET;
        traverse +=  strlen(value) + 1; // points to key now.
        
        char* temp = strchr(traverse, ' ');
        if ( NULL != temp) {
                data->key_length = temp - traverse;
                data->key = malloc(data->key_length + 1);
                strncpy(data->key, traverse, data->key_length);
        } else {
                eprintf("ERR015: gwkv_demarshal_client, improper ascii syntax; did not find deliminator of newline.\n");
                return -1;
        }
        
        if (temp[1] != '0') { // flags
                eprintf("ERR016: gwkv_demarshal_client, improper ascii syntax; expected flag of '0'\n");
                return -1;
        }
        if (temp[2] != ' ') {
                eprintf("ERR017: gwkv_demarshal_client, improper ascii syntax; expected ' '\n");
                return -1;
        }
        traverse = temp + 3; //pointing to <bytes> now
        
        temp = strchr(traverse, ' ');
        if (NULL != temp) {
                sscanf(traverse, "%d", &data->value_length);
                data->value = malloc(data->value_length);
        }

        if (temp[1] != '\r') {
                eprintf("ERR018: gwkv_demarshal_client, improper ascii syntax; expected carriage return\n");
                return -1;
        }
        if (temp[2] != '\n') {
                eprintf("ERR019: gwkv_demarshal_client, improper ascii syntax; expected new line\n");
                return -1;
        }


        traverse = temp + 3;//pointing to value now.
        temp = strchr(traverse, '\r');
        if( temp != NULL) {
                //verify the length
                if (data->value_length != temp - traverse) {
                        eprintf("ERR020: gwkv_demarshal_client, specified data length does not match ascii length.\n");
                        return -1;
                }
                strncpy(data->value, traverse, data->value_length);
        }
        return 0;

/*
        int i=0;
        int offset = 0;
        char *a=ascii;
        i=0;
        char b[50];
        while(a[i]!=' ' && a[i]!='\0'){
                b[i]=a[i];
                i++;
        }       
        b[i]='\0';
        
        offset += i+1;
        char c1[]="VALUE";
        if(strcmp(b,c1)!=0){
                return -1;
        }
        data->method_type  = GET;
        
        //key
        a = ascii + offset;
        i=0;
        
        while(a[i]!=' '&& a[i]!='\0'){
                b[i]=a[i];
                i++;
        }       
        b[i]='\0';
        offset += i+1;
        data->key_length = i + 1;
        data->key = malloc(data->key_length);
        strcpy(data->key,  b);
        
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
        data->value = b1;*/
}
