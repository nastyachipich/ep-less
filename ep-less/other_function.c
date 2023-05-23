#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "structura.h"


void getcharLock(int loops){
    for(int i = 0; i < loops; i++ ) getchar();
}

void clearscreen(){
    printf("\n"); system("cls");
}

int filenlines(const char *filename)
{
    FILE *in = fopen(filename, "r");
    if(!in) {
        printf("Error... File '%s' not found!\nPress any key to continue...\n", filename);
        getcharLock(2); return 0;
    }
    int file_lines=0;
    char str[100];
    do {
        fgets(str, sizeof(str), in);
    } while(!feof(in) && ++file_lines);
    return file_lines+1;
}


forest* get_temp_structure(int* file_lines_){
    int file_lines = 0;
    if(!(file_lines=filenlines(temp_file))) return 0;

    FILE *in = fopen(temp_file, "r");
    forest* forest_array = (forest*)malloc(sizeof(forest) * file_lines);

    char str[100];
    for(int i=0; i<file_lines; i++){
        fgets(str, sizeof(str), in);
        forest_array[i].id = atoi(strtok(str, ";"));
        strcpy(forest_array[i].uchastok, strtok(NULL, ";"));
        forest_array[i].fio_id = atoi(strtok(NULL, ";"));
        forest_array[i].doljn_id = atoi(strtok(NULL, ";"));
        forest_array[i].plojad = atof(strtok(NULL, ";"));
    }
    fclose(in);
    *file_lines_ = file_lines;
    return forest_array;
}

dictionary* read_dictionary_(const char *filename, int *lines){
    int file_lines = 0;
    if(!(file_lines = filenlines(filename))) return 0;
    FILE *in = fopen(filename, "r");

    char str[100];
    dictionary* dictionary_array = (dictionary*)malloc(sizeof(dictionary) * file_lines);
    for(int i=0; i<file_lines; i++){
        fgets(str, sizeof(str), in);
        dictionary_array[i].id = atoi(strtok(str, ";"));
        strcpy(dictionary_array[i].value, strtok(NULL, ";"));
    }
    *lines = file_lines;
    return dictionary_array;
}

int _get_dictionary_index(dictionary* dictionary_, int lines, int id, int mode){
    for(int i=0; i<lines; i++){
        if(dictionary_[i].id == id) return i;
    }
    if(mode){
        clearscreen();
        printf("Error... dictionary note id %d does not exist!\nPress ENTER to go back...", id);
        getcharLock(2);
    }
    return -1;
}

void file_print(forest* forest_array, int length){
    int doljn_id_lines=-1, fio_id_lines=-1;
    dictionary* fio_id_array = read_dictionary_(name_file, &fio_id_lines);
    dictionary* doljn_id_array = read_dictionary_(rank_file, &doljn_id_lines);

    printf(" id\t  fio_id\t\t doljnost\t\t uchastok\t\t plojad\n\n");
    for(int i=0; i<length; i++){
        char tmp_fio_id[100] = "*!?no_value\0";
        char tmp_doljn_id[100] = "*!?no_value\0";
        int fio_id_ind = _get_dictionary_index(fio_id_array, fio_id_lines, forest_array[i].fio_id, 0);
        int doljn_id_ind = _get_dictionary_index(doljn_id_array, doljn_id_lines,forest_array[i].doljn_id, 0);
        if(fio_id_ind != -1) strcpy(tmp_fio_id, fio_id_array[fio_id_ind].value);
        if(doljn_id_ind != -1) strcpy(tmp_doljn_id, doljn_id_array[doljn_id_ind].value);
        printf("%3d\t%-15s\t%-20s\t  %-12s\t\t%.2f\n",
               forest_array[i].id,
               tmp_fio_id, tmp_doljn_id,
               forest_array[i].uchastok,
               forest_array[i].plojad);
    }
}

void print_dict(const char* filename){
    int dict_lines=-1;
    dictionary* dict_array = read_dictionary_(filename, &dict_lines);
    printf("Dictionary %s\n\n", filename);
    printf(" id  value\n\n");
    for(int i=0; i<dict_lines; i++){
        printf(" %-4d%s\n",
               dict_array[i].id,
               dict_array[i].value
               );
    }
}

int _get_note_index(forest* forest_array, int file_length, int id){
    for(int i=0; i<file_length; i++)
        if(forest_array[i].id == id) return i;
    clearscreen();
    printf("Error... Note id %d does not exist!\nPress ENTER to go back...", id);
    getcharLock(2);
    return -1;
}
