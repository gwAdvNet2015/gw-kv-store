#ifndef __COMMON_H__
#define __COMMON_H__

volatile int verbose_print = 0;

#define eprintf(format, ...) do {                 \
        fprintf(stderr, format, ##__VA_ARGS__);   \
} while(0)

#define kvprintf(format, ...) do {                        \
        if (verbose_print)                                \
                fprintf(stderr, format, ##__VA_ARGS__);   \
} while(0)

#endif
