#ifndef STRUCTURA_H
#define STRUCTURA_H

#define main_file "forest.db"
#define temp_file "forest_tmp.db"
#define name_file "name.db"
#define rank_file "rank.db"

typedef struct{
    int id;
    char uchastok[40];
    int fio_id;
    int doljn_id;
    float plojad;
} forest;

typedef struct{
    int id;
    char value[50];
} dictionary;

#endif // STRUCTURA_H
