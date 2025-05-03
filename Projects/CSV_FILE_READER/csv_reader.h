#ifndef CSV_READER

#define CSV_READER

#define ROWS 200
#define COLS 10
#define LINE_LEN 1024

int load_file(const char* filename, float X[ROWS][COLS-1], float y[ROWS]);
int count_rows(const char* filename);
int count_cols(const char* filename);
char feature_name(const char* filename);

#endif
