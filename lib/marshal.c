
/*
 * @desc: The function does the marshing. Function does all the allocation.
 *        It is caller's responsibility to free the memory allocated.
 * @data: Input, the function expecting this structure.
 * @ascii: Function returns this char.
 */

int 
gwkv_marshal_server(struct operation* data, int status, char** ascii)
{
	char* val = (char*)malloc(1000*sizeof(char));
       switch(data->method) {
            case SET:
		char command_name[]="set ";
		strcat(val,command_name);
		char flag_exp[]=" 0 0 ";
		strcat(val,data->key);
		strcat(val,flag_exp);
		char v_len[10];
		sprintf((int)data->value_length,"%d",v_len);
		strcat(val,v_len);
		char r_n[]="\r\n";
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
		char b1[]="get ";
	       	char b2[]="\r\n";
		strcat(val,a);
		strcat(val,data->key);
		strcat(val,b);		
                break;
	*ascii = val;
            default: assert(0);    
       }
}


int 
gwkv_marshal_client(structu operation* data, char** ascii)
{
        switch(data->method) {
            case SET:
                //convert data to this format:
                //<command name> <key> <flags> ...
                break;
            case GET:
                //convert data to this format
                // get <key>* \r\n
                break;
        }
}

int 
gwkv_demarshal_server(char* ascii, struct** op)
{
        switch(data->method) {
            case SET:
                //convert ascii to operation 
            case GET:
                //convert ascii to operation
        }
}

int 
gwkv_demarshal_client(char* ascii, struct** op, int* status)
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
}
