#include "memoryinspector.h"
#include "../logger/logger.h"
#include <stdio.h>
#include <string.h>

#define ADDRESS_SIZE 16
#define FILE_SIZE 16
#define LINE_SIZE 16
#define STATUS_SIZE 8

static void* (*real_malloc)(size_t) = malloc;
static void (*real_free)(void *) = free;


// Storing information on memalloc?
// Start with storing in heap, then file
// Lifecycle of memory

typedef struct {
    char address[ADDRESS_SIZE];
    char file[FILE_SIZE];
    char line[LINE_SIZE];
    char status[STATUS_SIZE];
    int size; //Bytes
} MemoryEntry;

MemoryEntry *entries = NULL;
size_t entries_size = 0;

void minsp_record_entry(void *ptr, int size, char *status, const char *file, int line) {
    if (ptr == NULL) { return; }

    char entry[256];
    // Address | Size | Status | File | Line    
    sprintf(entry, ">%p|%d|%s|%s|%d\n", ptr, size, status, file, line);
    printf("Entry: %s", entry); //Works
    // Record into a file
}

void* minsp_malloc(size_t size, const char *file, int line) {
    void *ptr = real_malloc(size);
    minsp_record_entry(ptr, (int) size, "MALLOC", file, line);
    return ptr;
}

void minsp_free(void *ptr, const char *file, int line) {
    // update entry
    minsp_record_entry(ptr, 0, "FREE", file, line);
    real_free(ptr);
}

void priv_insert_into_string(char *s, char *c, int o) {
    // s = string
    // c = string to insert
    // o = offset

    int size = (int) strlen(c);
    for (int i = 0; i < size; i++) {
        s[o] = c[i];
        o++;
    }
}

void minsp_print() {
    log_info("Printing entries info...");
    // Table Header
    int SIZE_SIZE = 6;
    int table_width = 1+ ADDRESS_SIZE +1+ SIZE_SIZE +1+ STATUS_SIZE +1;
    int column_1 = (int) (1 + ADDRESS_SIZE);
    int column_2 = (int) (2 + ADDRESS_SIZE + SIZE_SIZE);
    
    char tmp_break[table_width+1];
    for (int i = 0; i < table_width; i++) {
        tmp_break[i] = '-';
    }
    tmp_break[table_width] = '\0';

    char tmp_line[table_width+1];
    for (int i = 0; i < table_width; i++) {
        if (i == 0 || i == table_width-1 || i == column_1 || i == column_2) {
            tmp_line[i] = '|';
            continue;
        }
        tmp_line[i] = ' ';
    }
    tmp_line[table_width] = '\0';

    char headers[table_width+1];
    for (int i = 0; i < table_width+1; i++) {
        headers[i] = tmp_line[i];
    }
    priv_insert_into_string(headers, "     ADDRESS", 1);
    priv_insert_into_string(headers, " SIZE", column_1+1);
    priv_insert_into_string(headers, "     STATUS", column_2+1);

    printf("%s\n", tmp_break);
    printf("%s\n", headers);
    printf("%s\n", tmp_break);
    // Print entries
    char line[table_width+1];
    for (int i = 0; i < (int) entries_size; i++) {
        for(int j = 0; j < table_width+1; j++) {
            line[j] = tmp_line[j];
        }

        priv_insert_into_string(line, entries[i].address, 1);
        char str_size[SIZE_SIZE];
        sprintf(str_size, "%d", entries[i].size);
        priv_insert_into_string(line, str_size, column_1+1);
        priv_insert_into_string(line, entries[i].status, column_2+1);

        printf("%s\n", line);
    }
    printf("%s\n", tmp_line);
    printf("%s\n", tmp_break);
}

void minsp_free_all(){

    minsp_print();
    // free(entries);
    entries = NULL;
    entries_size = 0;

}
