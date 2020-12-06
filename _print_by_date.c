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



void analayze_input(char* argv[], char* date,char* key);
void get_value_of_key_from_country_data(DataPerDate** counrty_data, char* value_of_key, char* key, char* date);

int main(int argc, char* argv[])
{
	int arr_size, num_of_countries;
	char date[MAX_STRING_LENGTH],key[MAX_STRING_LENGTH],value_of_key[MAX_STRING_LENGTH];
	char** countries_names =  get_countries_names(&num_of_countries);
	DataPerDate*** arr_of_countries = get_all_countries_data(&arr_size);
	DataPerDate** curr_counrty_data;
	analayze_input(argv + 1, date, key);


	for(int i = 0; i < arr_size; i++)
	{
		curr_counrty_data = arr_of_countries[i];
		if(arr_of_countries[i] != NULL)
		{
			get_value_of_key_from_country_data(curr_counrty_data,value_of_key,key,date);
			printf("%s: %s\n",countries_names[i], value_of_key);
		}
	}
	
	free_countries_names(countries_names);
	free_countries_data(arr_of_countries,arr_size);	

	return 0;
}


void get_value_of_key_from_country_data(DataPerDate** counrty_data, char* value_of_key, char* key, char* date)
{
	int i=0;
	while(counrty_data[i] != NULL)
	{

		if(strcmp(counrty_data[i]->Date, date) == 0)
		{
			if(strcmp(key, "Confirmed") == 0)
				strcpy(value_of_key,counrty_data[i]->Confirmed);
			else if(strcmp(key, "Deaths") == 0)
				strcpy(value_of_key,counrty_data[i]->Deaths);
			else if(strcmp(key, "Recovered") == 0)
				strcpy(value_of_key,counrty_data[i]->Recovered);
			else if(strcmp(key, "Active") == 0)
				strcpy(value_of_key,counrty_data[i]->Active);				
		}
			
		i++;
	}
}


void analayze_input(char* argv[], char* date,char* key)
{

	
	for(int index = 0; index < 3; index++)
	{
		if(strcmp(argv[index],"--date") == 0)
		{
			strcpy(date,argv[index+1]);
		}
		else if(strcmp(argv[index],"--key") == 0)
		{
			strcpy(key,argv[index+1]);
		}
	}
	
}
