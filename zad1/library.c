#include <string.h>
#include "library.h"
#include <stdlib.h>
#include <stdio.h>


void invoke_diff(char* files[], int size){
    int i;
    if(size % 2 != 0){
        printf("Undifined files diff");
        exit(0);
    }
    system("touch tmp");
    
    for(i = 0; i < size-1; i+=2){
        char tmp[12 + strlen(files[i]) + strlen(files[i+1])];
        strcpy(tmp, "diff ");
        strcat(tmp, files[i]);
        strcat(tmp, " ");
        strcat(tmp, files[i+1]);
        strcat(tmp, " >> tmp");
        system(tmp);
        if(i != size-2){
            system("echo  '\n=' >> tmp");
        }
    } 
    system("echo  '$' >> tmp");
}

void delete_block(int index){
    int size = (int)sizeof(master_tab);
    if(index >= size){
        printf("cannot delete element at index %d from array of size %d\n", index, size);
    }
    else{
        int i = 0;
        while(master_tab[index] -> ops_num - i > 0){
            if(master_tab[index] -> ops[i] == NULL) i++;
            else{
                delete_op(i, index);
                i++;
            }
        }
        free(master_tab[index]);
        master_tab[index] = NULL;
    }
}

void delete_op(int op_index,int bl_index){
    struct block* bl = master_tab[bl_index];
    if(op_index >= bl->ops_num){
        printf("cannot delete element at index %d from array of size %d\n", op_index, bl->ops_num);
    }
    else{
        free(bl->ops[op_index]);
        bl->ops_num--;
        bl->ops[op_index] = NULL;
    }
}

int get_op_num(int index, struct block** tab){
    return tab[index]->ops_num;
}

void create_block_tab(char* file, int size){
    int i;
    char** tmp = (char**) calloc(size, sizeof(char*));
    FILE* fp;
//    size_t len=0;

    fp = fopen(file, "r");
    if(fp == NULL){
        exit(EXIT_FAILURE);
    }

    i = 0;
    tmp[i] = (char*) calloc(10000, sizeof(char));
    strcpy(tmp[i], "");
    //while (fgets(line, 100, fp) != NULL) {
    //    if(strcmp(line, " next \n") == 0){
    //        i++;
    //        tmp[i] = (char*) calloc(1000000, sizeof(char));
    //        strcpy(tmp[i], "");
    //    }
    //    else{
    //        strcat(tmp[i], line);
    //    } 
    //}
    
    int c;
    while((c = getc(fp)) != '$'){
        if(c == '='){
            c = getc(fp);
            i++;
            tmp[i] = (char*)calloc(1000, sizeof(char));
            strcpy(tmp[i], "");
        }
        else{
            char jd[1];
            jd[0] = c;
            strcat(tmp[i], jd);
        }
    }
    fclose(fp);

    master_tab = (struct block**)calloc(i, sizeof(struct block*));
    int j;
    for(j = 0; j <= i; j++){
        int x;
        int counter = 0;
        for(x = 0; x < (int)strlen(tmp[j]); x++){
            if((tmp[j][x] >= '0' && tmp[j][x] <= '9' && x == 0 )|| ( tmp[j][x] >= '0' && tmp[j][x] <= '9' && tmp[j][x-1] == '\n')){
                master_tab[j] = (struct block*)calloc(1, sizeof(struct block));
                counter++;
            }
        }
        master_tab[j] -> ops_num = counter;
        master_tab[j] -> ops = (char**)calloc(counter, sizeof(char*));
        counter = 0;
        int y = 0;
        for(x = 0; x < (int)strlen(tmp[j]); x++){
            if(x == (int)strlen(tmp[j]) - 1 || ( tmp[j][x] >= '0' && tmp[j][x] <= '9' && tmp[j][x-1] == '\n')){
                master_tab[j] -> ops[counter] = (char*)calloc(x-y, sizeof(char));
                strncpy(master_tab[j] -> ops[counter], tmp[j] + y, x-y);
                y = x;
                counter++;
            }
        }
    }
    
    system("rm tmp");
}
