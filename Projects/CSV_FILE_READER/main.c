#include <stdio.h>
#include <stdlib.h>
#include "csv_reader.h"
#include <time.h>

int main(void)
{
    float X[ROWS][COLS-1], y[ROWS];
    printf("\n========== THE CSV FILE CONTENTS ==========\n\n");
    printf("index");
    clock_t start = clock();
    headers_name("./classification_data.csv");
    puts("");
    int row_ = load_file("./classification_data.csv",X,y);
    if(row_ < 1) return -1;
    for(int i=0;i<row_;++i){
        printf("%d\t",i+1);
        for(int j=0;j<COLS-1;++j){
            printf("%f\t\t",X[i][j]);
        }
        printf("%.1f\n",y[i]);
        if(i != row_ -1) printf("------------------------------------------------------------------------------------------------------\n");
        clock_t end = clock();
        double spent_time = (double)(end-start)/CLOCKS_PER_SEC;
        printf("\n%lf seconds took to run the program.\n",spent_time);
    }

    return 0;
}
