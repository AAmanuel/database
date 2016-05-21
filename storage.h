#ifndef STORAGE_H
#define STORAGE_H

#define JOURNAL_LEN 64
#define AUTHOR_LEN 32
#define ARTICLE_LEN 128

#define SIGNATURE htonl(0x42444141)

#include <stdlib.h>

typedef struct {
    char journal[JOURNAL_LEN];
    uint16_t year;
    uint16_t number;
    char author[AUTHOR_LEN];
    char article[ARTICLE_LEN];
} __attribute__((__packed__)) record;


typedef struct {
    uint32_t signature;
    uint32_t lenght;
    record *records;
} __attribute__((__packed__)) database;

#endif // STORAGE_H
