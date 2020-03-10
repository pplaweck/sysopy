#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/times.h>
#include <string.h>
#include <zconf.h>
#include "library.h"

static char *rand_string(char *str, size_t size)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK...";
    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}

void create_table(int n){
    master_tab = (struct block**)calloc(n, sizeof(struct block*));

}

double calculate_time(clock_t start, clock_t end) {
    return (double) (end - start) / sysconf(_SC_CLK_TCK);
}

int main(int argc, char* args[]){

    int n = 1;
    while(argc-n > 0){
        if (strcmp(args[n], "create_table") == 0){
            create_table(atoi(args[n+1]));
            n+=2;
        }
        else if(strcmp(args[n], "compare_pairs") == 0){
           char* dupl[atoi(args[n+1])];
           memcpy(dupl, args+n+2, sizeof(char*)*atoi(args[n+1]));
           
           invoke_diff(dupl, atoi(args[n+1]));
           create_block_tab("tmp", atoi(args[n+1])/2);
           n += atoi(args[n+1]) + 2;
        }
        else if(strcmp(args[n], "remove_block") == 0){
            delete_block(atoi(args[n+1]));
            n+=2;
        }
        else if(strcmp(args[n], "remove_operation") == 0){
            delete_op(atoi(args[n+2]), atoi(args[n+1]));
            n+=3;
        }
    }

    // TESTS
    struct tms **tms_time = malloc(4 * sizeof(struct tms *));
    clock_t r_time[4];

    for (int i = 0; i < 4; i++) {
        tms_time[i] = (struct tms *) malloc(sizeof(struct tms *));
    }

    //BIG files

    int i =0 ;
    r_time[0] = times(tms_time[0]);

    char* files[2] = {"big.txt", "big2.txt"};
    invoke_diff(files, 2);
    create_block_tab("tmp", 100000000);
    for(i = 0; i < 10; i++) delete_op(i, 0);

    r_time[1] = times(tms_time[1]);

    printf("%s", "BIG DIFF\n");
    printf("%lf   ", calculate_time(r_time[0], r_time[1]));
    printf("%lf   ", calculate_time(tms_time[0]->tms_utime, tms_time[1]->tms_utime));
    printf("%lf ", calculate_time(tms_time[0]->tms_stime, tms_time[1]->tms_stime));
    printf("\n");

    r_time[2] = times(tms_time[2]);

    int xd = 100;

    while(xd){
        char* fil[6];
        for(i = 0 ; i < 6;i++){
            if (i % 2 == 0) fil[i] = "big.txt";
            else {
                fil[i] = "big2.txt";
            }
        }
        invoke_diff(fil, 6);
        create_block_tab("tmp", 10000000);
        for(i = 0; i < 10; i++) delete_op(i, 2);
        delete_block(0);
        xd--;
    }

    r_time[3] = times(tms_time[3]);

    printf("%s", "BIGGER DIFF\n");
    printf("%lf   ", calculate_time(r_time[2], r_time[2]));
    printf("%lf   ", calculate_time(tms_time[2]->tms_utime, tms_time[3]->tms_utime));
    printf("%lf ", calculate_time(tms_time[2]->tms_stime, tms_time[3]->tms_stime));
    printf("\n");

    return 0;
}


