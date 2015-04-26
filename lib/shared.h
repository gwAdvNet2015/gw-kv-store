#ifndef SHARED_H
#define SHARED_H

/* Operations the table supports */
typedef enum {
        GET,
        SET
} method;

/* Defines for result codes */
#define STORED 0
#define NOT_STORED 1
#define EXISTS 2
#define NOT_FOUND 3

/* Datatype for wrapping datastore values */
struct operation {
        method method_type;
        const char* key;
        size_t key_length;
        const char* value;
        size_t value_length;
};
#endif

