#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

#include "storage.h"

int DB::updfsize() {
    if (fseek(this->fd, 0, SEEK_END) != 0) {
        fprintf(stderr, "Failed to seek end of file\n");
        return(-1);
    }
    if ((this->fsize = ftell(this->fd)) < 0) {
        fprintf(stderr, "Failed to get size of file\n");
        return(-1);
    }
    return 0;
}

int DB::mmap() {
    this->map = (dbmap*)::mmap(NULL, this->fsize, PROT_READ|PROT_WRITE, MAP_FILE|MAP_SHARED, fileno(this->fd), 0);
    if (this->map == MAP_FAILED) {
        fprintf(stderr, "Failed to mmap file\n");
        return(-1);
    }
    return 0;
}

int DB::munmap() {
    if (::munmap(this->map, this->fsize) != 0) {
        fprintf(stderr, "Failed to munmap file\n");
        return(-1);
    }
    return 0;
}

DB::DB() {
    this->fd = 0;
    this->map = 0;
}

DB::~DB() {
    if (this->map != 0) {
        this->munmap();
    }
    if (this->fd != 0) {
        fclose(fd);
    }
}

size_t DB::open(const char* path) {
    if (this->fd != 0) {
        fprintf(stderr, "There's opened database already\n");
        return(1);
    }

    if (access(path, R_OK|W_OK) !=0) {
        fprintf(stderr, "Can't access database file %s\n", path);
        return(2);
    }

    if ((this->fd=fopen(path, "w+"))==NULL) {
        fprintf(stderr, "Can't open file %s\n", path);
        return(2);
    }

    if (this->mmap() != 0) {
        return(3);
    }

    if (ntohl(this->map->signature) != SIGNATURE) {
        fprintf(stderr, "Invalid signature\n");
        return(4);
    }
    return 0;
}

ssize_t DB::write(record* rec) {
    if (this->munmap() != 0) {
        return(-1);
    }

    if(ftruncate(fileno(this->fd), this->fsize + sizeof(record)) < 0) {
        fprintf(stderr, "Failed to extend file\n");
        return(-1);
    }

    if (this->updfsize() != 0) {
        fprintf(stderr, "Failed to update file size\n");
        return(-1);
    }

    if (this->mmap() != 0) {
        return(-1);
    }

    memcpy(this->map-this->fsize, rec, sizeof(record));
    if (msync(this->map-this->fsize, sizeof(record), MS_SYNC) < 0) {
        fprintf(stderr, "Failed to msync data\n");
        return(-1);
    }
    return this->pos;
}


