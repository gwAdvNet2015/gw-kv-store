
/*
 * @desc: The function does the marshing. Function does all the allocation.
 *        It is caller's responsibility to free the memory allocated.
 * @data: Input, the function expecting this structure.
 * @ascii: Function returns this char.
 */

int gwkv_marshal_server(struct operation* data, int status, char** ascii)
{
       switch(data->method) {
            case SET:
                //Convert the status into a string like this:
                //
                break;
            case GET:
                //convert the struct value to like this:
                //VALUE <key> <flags> <bytes> \r\n
                //<data blcok> \r\n
                //END \r\n
                break;
            default: assert(0);    
       }
}

int gwkv_marshal_client(structu operation* data, char** ascii)
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

int gwkv_demarshal_server(char* ascii, struct** op, int* status)
{
        switch(data->method) {
            case SET:
                //convert ascii to status
            case GET:
                //convert ascii to operation
        }
}

int gwkv_demarshal_client(char* ascii, struct** op, int* status)
{
        switch(data->method) {
            case SET:
                //convert ascii to operation
            case GET:
                //convert ascii to status
            default:
                break;
        }
}
