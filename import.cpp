#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "import.h"
#include "storage.h"

int main(int argc, char * const argv[]) {
    int opt = 0;
    DB* db = new(DB);
    record r;
    uint8_t optcheck = 0;

    while( (opt = getopt(argc, argv, "jy:n:A:a:")) != -1 ) {
        switch( opt ) {
            case 'j':
                if (strlen(optarg)>JOURNAL_LEN) {
                    fprintf(stderr, "Journal name is too long (max %d)\n", JOURNAL_LEN );
                    exit (10);
                }
                if (strncpy(optarg, r.journal, JOURNAL_LEN)==0) {
                    fprintf(stderr, "Unknown error\n");
                    exit (1);
                }
                optcheck |= (1<<0);
                break;

            case 'y':
                if ((r.year = atoi(optarg)) == 0) {
                    fprintf(stderr, "Invalid year");
                    exit(11);
                }
                optcheck |= (1<<1);
                break;

            case 'n':
                if ((r.number = atoi(optarg)) == 0) {
                    fprintf(stderr, "Invalid number");
                    exit(12);
                }
                optcheck |= 1<<2;
                break;

            case 'A':
                if (strlen(optarg)>AUTHOR_LEN) {
                    fprintf(stderr, "Author name is too long (max %d)\n", AUTHOR_LEN );
                    exit (13);
                }
                if (strncpy(optarg, r.author, AUTHOR_LEN)==0) {
                    fprintf(stderr, "Unknown error\n");
                    exit (1);
                }
                optcheck |= 1<<3;
                break;

            case 'a':
                if (strlen(optarg)>ARTICLE_LEN) {
                    fprintf(stderr, "Article name is too long (max %d)\n", ARTICLE_LEN );
                    exit (14);
                }
                if (strncpy(optarg, r.article, ARTICLE_LEN)==0) {
                    fprintf(stderr, "Unknown error\n");
                    exit (1);
                }
                optcheck |= (1<<4);
                break;

            case '?':
                fprintf(stderr,"-j <journal> – journal title\n");
                fprintf(stderr,"-y <year> – year of issue\n");
                fprintf(stderr,"-n <number> – number of issue\n");
                fprintf(stderr,"-A <author> – author's name\n");
                fprintf(stderr,"-a <article> – article title\n");
                fprintf(stderr,"-? – this help\n");
                exit(2);
            default:
                fprintf(stderr, "Unknown option: %c\n", opt);
                break;
        }

    }

    if ((optcheck&0x1f)!=0x1f) {
        fprintf(stderr,"Not all data defined: %x\n", optcheck);
        exit(20);
    }

    if ((argc-optind)<1) {
        fprintf(stderr, "No database defined\n");
        exit(21);
    } else if ((argc-optind)>1) {
        fprintf(stderr, "More than one database defined\n");
        exit(22);
    }

    const char* dbpath = argv[optind];

    if (db->open(dbpath) != 0) {
        exit(10);
    }

    delete(db);
    exit(0);

}



