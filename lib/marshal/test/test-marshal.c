#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../marshal.h"
#define MAX_KEY_SIZE 250
#define MAX_VALUE_SIZE 1024	
struct operation *create_request(method op, char *key, char *value);

int
main()
{

        struct operation *get_request, *set_request;
        char *ascii;
        char *key = "test_key";
        char *value = "test_value";
        char *set_cmd = "set test_key 0 0 10 \r\ntest_value\r\n";
        char *get_cmd = "get test_key\r\n";
        int status = 0;

        printf("Create get and set request with key %s and value %s\n", key, value);
        get_request = create_request(GET, key, value);
        set_request = create_request(SET, key, value);
        printf("Test gwkv_marshal_client...\n");
        assert(gwkv_marshal_client(get_request, &ascii) == 0);
        printf("	Get Result: %s\n", ascii);
        assert(ascii != NULL);
        assert(strcmp(ascii, get_cmd) == 0);
        free(ascii);
        assert(gwkv_marshal_client(set_request, &ascii) == 0);
        printf("	Set Result: %s\n", ascii);
        assert(ascii != NULL);
        assert(strcmp(ascii, set_cmd) == 0);
        free(ascii);
	
        printf("Test gwkv_marshal_server...\n");
        assert(gwkv_marshal_server(get_request, status, &ascii) == 0);
        printf("- Get Result:\n%s\n", ascii);
        assert(ascii != NULL);
        assert(strcmp(ascii, get_cmd) == 0);
        ascii = 0;
        free(ascii);
        assert(gwkv_marshal_server(set_request, status, &ascii) == 0);
        printf("- Set Result:\n%s\n", ascii);
        assert(ascii != NULL);
        assert(strcmp(ascii, set_cmd) == 0);
        ascii = 0;
        free(ascii);
        
        printf("All marshal tests passed\n\n");


	
        return 0;
}

struct operation *
create_request(method op, char *key, char *value)
{
        struct operation *query;
        query = malloc(sizeof(struct operation));
        query->method_type = op;
        query->key = key;
        query->key_length = strlen(query->key);
        query->value = value;
        query->value_length = strlen(query->value);
        return query;
}
