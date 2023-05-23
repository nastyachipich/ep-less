#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "other_headers.h"
#include "structura.h"

void read_file(){
    int file_lines = 0;
    if(!(file_lines=filenlines("forest.db"))) return;

    FILE *in = fopen(main_file, "r");
    FILE *in_tmp = fopen(temp_file, "w");

    char str[100];
    for(int i=0; i<file_lines; i++){
        fgets(str, sizeof(str), in);
        fprintf(in_tmp, "%s", str);
    }

    fclose(in); fclose(in_tmp);
    printf("File '%s' opened!\nPress ENTER to go back...\n", main_file);
    getcharLock(2);
}

void close_file(){
    if (remove(temp_file) == 0) printf("The file is closed successfully.");
    else printf("The file is not closed.");
    getcharLock(2);
}

void save_file(){
    int file_lines = 0;
    if(!(file_lines=filenlines(temp_file))) {
        printf("Open File first!");
        return;
    }

    FILE *in = fopen(main_file, "w");
    FILE *in_tmp = fopen(temp_file, "r");

    char str[100];
    for(int i=0; i<file_lines; i++){
        fgets(str, sizeof(str), in_tmp);
        fprintf(in, "%s", str);
    }

    fclose(in); fclose(in_tmp);
    printf("File '%s' saved!\nPress ENTER to go back...\n", main_file);
    getcharLock(2);
}

void add_note(){
    int file_lines = 0;
    forest* forest_array = get_temp_structure(&file_lines);
    int newID = forest_array[file_lines - 1].id + 1;
    free(forest_array);

    printf("New ID: %d\n", newID);
    char uchastok[40];
    printf("Sowing uchastok: ");
    scanf("%s", uchastok);
    int fio_idID = 0;
    printf("fio_id ID: ");
    scanf("%d", &fio_idID);
    int doljn_idID = 0;
    printf("doljn_id ID: ");
    scanf("%d", &doljn_idID);
    float plojad = 0;
    printf("plojad: ");
    scanf("%f", &plojad);

    FILE *tmp = fopen(temp_file, "a");
    fprintf(tmp, "%d;%s;%d;%d;%.2f;\n", newID, uchastok, fio_idID, doljn_idID, plojad);
    fclose(tmp);
    printf("\nPress ENTER to go back...");
    getcharLock(2);

}

void delete_note(){
    int file_lines = 0;
    forest* forest_array = get_temp_structure(&file_lines);
    file_print(forest_array, file_lines);
    printf("\nChoose index to remove: ");
    int id_to_remove = 0;
    scanf("%d", &id_to_remove);
    int index = 0;
    if((index = _get_note_index(forest_array, file_lines, id_to_remove))==-1) return;
    FILE *tmp = fopen(temp_file, "w");
    int i;
    for(i = 0; forest_array[i].id != id_to_remove; i++)
        fprintf(tmp, "%d;%s;%d;%d;%.2f;\n",
                forest_array[i].id,
                forest_array[i].uchastok,
                forest_array[i].fio_id,
                forest_array[i].doljn_id,
                forest_array[i].plojad
                );
    for(i++;  i < file_lines; i++)
        fprintf(tmp, "%d;%s;%d;%d;%.2f;\n",
                forest_array[i].id,
                forest_array[i].uchastok,
                forest_array[i].fio_id,
                forest_array[i].doljn_id,
                forest_array[i].plojad
                );
    fclose(tmp);
    printf("\nPress ENTER to go back...");
    getcharLock(2);
}


void edit_note(){
    int file_lines = 0;
    forest* forest_array = get_temp_structure(&file_lines);
    file_print(forest_array, file_lines);
    printf("\nChoose index to edit: ");
    int id_to_edit = 0;
    scanf("%d", &id_to_edit);
    int index = 0;
    if((index = _get_note_index(forest_array, file_lines, id_to_edit))==-1) return;
    printf("\n\nEditing ID: %d\n", index);

    printf("New Type ID: ");
    scanf("%s", forest_array[index].uchastok);

    printf("New Sort ID: ");
    scanf("%d", &forest_array[index].fio_id);

    printf("New Sowing season: ");
    scanf("%d", &forest_array[index].doljn_id);

    printf("New Price: ");
    scanf("%f", &forest_array[index].plojad);


    FILE *tmp = fopen(temp_file, "w");
    for(int i=0; i<file_lines; i++){
    fprintf(tmp, "%d;%s;%d;%d;%.2f;\n",
            forest_array[i].id,
            forest_array[i].uchastok,
            forest_array[i].fio_id,
            forest_array[i].doljn_id,
            forest_array[i].plojad
            );
    }
    fclose(tmp);
    printf("\nPress ENTER to go back...");
    getcharLock(2);

}

void display_dictionary(const char* filename){
    print_dict(filename);
    printf("\nPress ENTER to go back...");
    getcharLock(2);
}

void edit_dictionary(const char* filename){
    int dict_lines=-1;
    print_dict(filename);
    dictionary* dict_array = read_dictionary_(filename, &dict_lines);
    printf("\nChoose index to edit: ");
    int id_to_edit = 0;
    scanf("%d", &id_to_edit);
    int index = 0;
    if((index = _get_dictionary_index(dict_array, dict_lines, id_to_edit, 1))==-1) return;
    printf("\nEditing ID: %d\n", id_to_edit);
    printf("New value: ");
    char str[1001]; char temp;
    scanf("%c",&temp); scanf("%[^\n]",str);
    strcpy(dict_array[index].value, str);
    FILE *in = fopen(filename, "w");
    for(int i=0; i<dict_lines; i++){
    fprintf(in, "%d;%s;\n",
            dict_array[i].id,
            dict_array[i].value
            );
    }
    fclose(in);
    printf("\nPress ENTER to go back...");
    getcharLock(2);
}



void add_note_dictionary(const char* filename){
    int file_lines = 0;
    dictionary* dictionary_ = read_dictionary_(filename, &file_lines);
    int newID = dictionary_[file_lines - 1].id + 1;
    free(dictionary_);

    printf("New ID: %d\n", newID);
    char value[50];
    printf("New value: ");
    scanf("%s", value);

    FILE *tmp = fopen(filename, "a");
    fprintf(tmp, "%d;%s;\n", newID, value);
    fclose(tmp);
    printf("\nPress ENTER to go back...");
    getcharLock(2);
}


void delete_element_dictionary(const char* filename){
    int dict_lines=-1;
    print_dict(filename);
    dictionary* dict_array = read_dictionary_(filename, &dict_lines);
    printf("\nChoose index to remove: ");
    int id_to_remove = 0;
    scanf("%d", &id_to_remove);
    int index = 0;
    if((index = _get_dictionary_index(dict_array, dict_lines, id_to_remove, 1))==-1) return;
    FILE *tmp = fopen(filename, "w");
    int i;
    for(i = 0; dict_array[i].id != id_to_remove; i++)
        fprintf(tmp, "%d;%s;\n",
                dict_array[i].id,
                dict_array[i].value
                );
    for(i++;  i < dict_lines; i++)
        fprintf(tmp, "%d;%s;\n",
                dict_array[i].id,
                dict_array[i].value
                );
    fclose(tmp);
    printf("\nPress ENTER to go back...");
    getcharLock(2);

}

void file_display(){
    int file_lines = 0;
    forest* forest_array = get_temp_structure(&file_lines);
    file_print(forest_array, file_lines);
    printf("\nPress ENTER to go back...");
    getcharLock(2);
}

void export_txt(){
    int file_lines = 0;
    forest* forest_array = get_temp_structure(&file_lines);
    FILE *out = fopen("out.txt", "w");
    int doljn_id_lines=-1, fio_id_lines=-1;
    dictionary* fio_id_array = read_dictionary_(name_file, &fio_id_lines);
    dictionary* doljn_id_array = read_dictionary_(rank_file, &doljn_id_lines);

    for(int i=0; i<file_lines; i++){
        char tmp_fio_id[100] = "*!?no_value\0";
        char tmp_doljn_id[100] = "*!?no_value\0";
        int fio_id_ind = _get_dictionary_index(fio_id_array, fio_id_lines, forest_array[i].fio_id, 0);
        int doljn_id_ind = _get_dictionary_index(doljn_id_array, doljn_id_lines,forest_array[i].doljn_id, 0);
        if(fio_id_ind != -1) strcpy(tmp_fio_id, fio_id_array[fio_id_ind].value);
        if(doljn_id_ind != -1) strcpy(tmp_doljn_id, doljn_id_array[doljn_id_ind].value);
        fprintf(out,"%3d\t%-15s\t\t%-20s\t%-12s\t\t%.2f\n",
               forest_array[i].id,
               tmp_fio_id, tmp_doljn_id,
               forest_array[i].uchastok,
               forest_array[i].plojad);
    }
    fclose(out);
    printf("\nData exported to 'out.txt'\n");
    printf("Press ENTER to go back...\n");
    getcharLock(2);
}


void about(){
    printf("Programm is made for processing data from files and writing the results back");
    printf("\nPress ENTER to go back...\n");
    getcharLock(2);
}
