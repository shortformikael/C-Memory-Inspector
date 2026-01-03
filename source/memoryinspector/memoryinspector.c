#include "memoryinspector.h"
#include "../logger/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STATUS_SIZE 16
#define ADDRESS_SIZE 16

// Storing information on memalloc?
// Start with storing in heap, then file
// Lifecycle of memory

typedef struct {
    char address[ADDRESS_SIZE];
    int size;
    char status[STATUS_SIZE];
} MemoryEntry;

MemoryEntry *entries = NULL;
size_t entries_size = 0;

MemoryEntry entry_init(char *TYPE, Vector *v) {
    MemoryEntry r_var;

    sprintf(r_var.address, "%p", (void *) v);
    r_var.size = (int) sizeof(*v);
    sprintf(r_var.status, "%s",TYPE);

    return r_var;
}

void minsp_add_entry(char *TYPE, Vector *v){
    entries_size++;

    MemoryEntry *temp_entries = entries;
    free(entries);
    entries = malloc(entries_size * sizeof(MemoryEntry));
    if (entries_size > 1) {
        for (int i = 0; i < (int) entries_size; i++) {
            entries[i] = temp_entries[i];
        }
    }
    free(temp_entries);
    
    entries[entries_size - 1] = entry_init(TYPE, v);
}

void minsp_log_vec_entry(char *TYPE, Vector *v) {
    // printf("Vector info being logged - Address: %p, status: %s, size: %d\n", (void*) v, TYPE,(int) sizeof(*v));

    if (entries_size == 0) {
        minsp_add_entry(TYPE, v);
    }

    // Check if exist, true: update | false: add
}

void minsp_log_vec(char *TYPE, Vector *v) {
    minsp_log_vec_entry(TYPE, v);

    char type_buffer[256];
    sprintf(type_buffer, "[MINSP] [%s]", TYPE);
    log_info(type_buffer);
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

void minsp_free(){

    minsp_print();

    free(entries);
    entries = NULL;
    entries_size = 0;

}
