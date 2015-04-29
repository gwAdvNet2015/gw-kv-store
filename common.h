#ifndef __COMMON_H__
#define __COMMON_H__

extern volatile int verbose_print;

#define eprintf(format, ...) do {                         \
        if (verbose_print)                                \
                fprintf(stderr, format, ##__VA_ARGS__);   \
} while(0)

#define kvprintf(format, ...) do {                        \
        if (verbose_print)                                \
                printf(format, ##__VA_ARGS__);            \
} while(0)

#endif /* __COMMON_H__ */
