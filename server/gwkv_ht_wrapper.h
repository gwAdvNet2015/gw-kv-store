#ifndef GWKV_HT_WRAPPER
#define GWKV_HT_WRAPPER

#include <stdlib.h>

typedef enum {
        GET,
        SET
} method;

struct {
        method method_type,
        const char* key,
        size_t key_length,
        const char* value,
        size_t value_length
} operation;

#endif
