#ifndef SYSYOPY_LIB_H
#define SYSYOPY_LIB_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct block{
    int ops_num;
    char** ops;
};

struct block** master_tab;

void invoke_diff(char* files[], int size);

void delete_block(int index);

void delete_op(int op_index,int bl_index);

int get_op_num(int index, struct block** tab);

void create_block_tab(char* file, int size);

#endif //SYSYOPY_LIB_H
