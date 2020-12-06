#include "libEx01utils.h"
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

typedef int BOOL;
#define TRUE 1
#define FALSE 0

#define MAX_SPACES 100

void analayze_input(char* argv[], char* country_name,char* key);
char** create_arr_values_form_key(DataPerDate** counrty_data,int size_arr, int* max_value,char* key);
int get_index_by_county_name(char*  country_name, char** names_arr, int num_of_countries);
void print_graph_of_values(char** arr_of_key_values , int size_arr, int max_value);
void free_arr_of_values(char** arr_values, int size);

int main(int argc, char* argv[])
{
	int arr_size, max_value = 0,index, num_of_countries;
	char country_name[MAX_STRING_LENGTH],key[MAX_STRING_LENGTH];
	
	analayze_input(argv + 1, country_name, key);
	DataPerDate*** arr_of_countries = get_all_countries_data(&arr_size);
	char** country_names =  get_countries_names(&num_of_countries);
	index = get_index_by_county_name(country_name,country_names, num_of_countries);
	DataPerDate** counrty_data = arr_of_countries[index];
	char** arr_of_key_values;

	if(arr_of_countries[index][0] != NULL)
	{
		arr_of_key_values = create_arr_values_form_key(counrty_data,arr_size,&max_value, key);
		print_graph_of_values(arr_of_key_values, arr_size, max_value);
	}
	else
		printf("no data for this country.. \n");
	
	free_countries_names(country_names);
	free_countries_data(arr_of_countries, arr_size);
	free_arr_of_values(arr_of_key_values, arr_size);

	return 0;
}

void print_graph_of_values(char** arr_of_key_values , int size_arr, int max_value)
{
	double amount_spaces;
	for(int i = 0; i < size_arr; i++)
	{	
		amount_spaces = MAX_SPACES / (double)max_value;
		amount_spaces = atoi(arr_of_key_values[i]) * amount_spaces;

		for(int j = 0; j < (int)amount_spaces - 1; j++)
			printf(" ");

		printf("%s\n",arr_of_key_values[i]);
		amount_spaces = 0;
	}
}

char** create_arr_values_form_key(DataPerDate** counrty_data,int size_arr, int* max_value,char* key)
{
	char** arr_of_key_values = (char**)malloc(sizeof(char*)*size_arr);
	int max = 0,curr_amount=0;
		
	for(int i = 0; i < size_arr; i++)
	{
		arr_of_key_values[i] = (char*)malloc(sizeof(char)*MAX_STRING_LENGTH);

		if(strcmp(key, "Confirmed") == 0)
			strcpy(arr_of_key_values[i],counrty_data[i]->Confirmed);
		else if(strcmp(key, "Deaths") == 0)
			strcpy(arr_of_key_values[i],counrty_data[i]->Deaths);
		else if(strcmp(key, "Recovered") == 0)
			strcpy(arr_of_key_values[i],counrty_data[i]->Recovered);
		else if(strcmp(key, "Active") == 0)
			strcpy(arr_of_key_values[i],counrty_data[i]->Active);
		
		curr_amount = atoi(arr_of_key_values[i]);

		if(curr_amount > max)
			max = curr_amount;
	}
	
	*max_value  = max;
	return arr_of_key_values;
}

void analayze_input(char* argv[], char* country_name,char* key)
{	
	for(int index = 0; index < 3; index++)
	{
		if(strcmp(argv[index],"--country") == 0)
			strcpy(country_name,argv[index+1]);
		else if(strcmp(argv[index],"--key") == 0)
			strcpy(key,argv[index+1]);
	}
}

void free_arr_of_values(char** arr_values, int size)
{
	for(int i = 0; i < size; i++)
	{
		free(arr_values[i]);
	}

	free(arr_values);
}
