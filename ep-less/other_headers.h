#ifndef OTHER_HEADERS_H
#define OTHER_HEADERS_H

#include "structura.h"

void getcharLock(int);
void clearscreen();

int filenlines(const char*);
forest* get_temp_structure(int*);
dictionary* read_dictionary_(const char*, int*);
void print_dict(const char*);
int _get_dictionary_index(dictionary*, int, int, int);
void file_print(forest*, int);
int _get_note_index(forest*, int, int );

#endif // OTHER_HEADERS_H
