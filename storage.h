#ifndef STORAGE_H
#define STORAGE_H

#define JOURNAL_LEN 64
#define AUTHOR_LEN 32
#define ARTICLE_LEN 128

#define SIGNATURE 0x41414442

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
    uint32_t length;
    record* records;
} __attribute__((__packed__)) dbmap;

class DB {
    FILE* fd;
    uint32_t pos;
    dbmap* map;
    long fsize;

    int updfsize();
    int mmap();
    int munmap();

public:
    DB();
    ~DB();
    size_t open(const char*);
    ssize_t len();
    record* read(size_t);
    record* read();
    ssize_t tell();\
    ssize_t seek(size_t);
    ssize_t write(record*);
};

#endif // STORAGE_H
