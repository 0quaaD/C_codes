#include <stdio.h>
#include <stdlib.h>
#include "csv_reader.h"
void print_feature_name(){
    printf("Index |  FEATURE_1 | FEATURE_2 | FEATURE_3 | FEATURE_4 | FEATURE_5 | FEATURE_6 | FEATURE_7 | FEATURE_8 | FEATURE_9 | TARGET\n");
}
int main(void)
{
    float X[ROWS][COLS-1], y[ROWS];
    printf("\n========== THE CSV FILE CONTENTS ==========\n\n");
    print_feature_name();
    int row_ = load_file("/home/elnokin/Downloads/classification_data.csv",X,y);
    if(row_ < 1) return -1;
    for(int i=0;i<row_;++i){
        printf("%d | ",i+1);
        for(int j=0;j<COLS-1;++j){
            printf(" %f ",X[i][j]);
        }
        printf("--> %.1f\n",y[i]);
        if(i != row_ -1) printf("------------------------------------------------------------------------------------------------------\n");
    }

    return 0;
}
