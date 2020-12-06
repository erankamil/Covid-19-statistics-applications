#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>

typedef struct dataPerDate{
char Confirmed[20],Deaths[20],Recovered[20],Active[20],Date[30];
}DataPerDate; 

DataPerDate*** get_all_countries_data(int* arr_size);
DataPerDate** get_corona_data_of_country(char* country_name);
char* get_value_of_key(char* key, char* line_in_file);
FILE* open_file(char* name);
void insert_data(DataPerDate* curr_date,char* key, char* value_to_insert);
char** get_countries_names(int* arr_size);
void free_arr(DataPerDate** arr);
int get_index_by_county_name(char*  country_name, char** names_arr, int num_of_countries);
void free_country_arr(DataPerDate** country_data_arr);
void free_countries_data(DataPerDate*** arr,int size);
void free_countries_names(char** countries_names_arr);

#define MAX_STRING_LENGTH 50
#define COUNTRIES_DATA_PATH  "countries/ "
#define COUNTRIES_NAMES_FILE  "countries_list.txt"
#define NUM_OF_COUNTRIES 256
