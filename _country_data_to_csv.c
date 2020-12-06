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

FILE* my_open_file(char* name);

int main(int argc, char* argv[])
{
	int arr_size, num_of_countries,index_of_country,i=0;
	char country_name[MAX_STRING_LENGTH],file_name[MAX_STRING_LENGTH];
	
	strcpy(country_name,argv[2]);
	strcpy(file_name,COUNTRIES_DATA_PATH);
	strcpy(file_name + strlen(file_name) - 1,country_name);
	strcpy(file_name + strlen(file_name),".csv"); 

	DataPerDate*** arr_of_countries = get_all_countries_data(&arr_size);
	char** country_names =  get_countries_names(&num_of_countries);
	index_of_country = get_index_by_county_name(country_name, country_names, num_of_countries);
	DataPerDate** country_data = arr_of_countries[index_of_country];
	
	FILE* file = my_open_file(file_name);
	fprintf(file,"%s;%s;%s;%s;%s\n","Date","Confirmed","Deaths","Recovered","Active");
	
	while(country_data[i] != NULL)
	{
		fprintf(file,"%s;%s;%s;%s;%s\n",country_data[i]->Date,country_data[i]->Confirmed,
		country_data[i]->Deaths,country_data[i]->Recovered,country_data[i]->Active);
		i++;
	}
	
	fclose(file);
	return 0;
}


FILE* my_open_file(char* name)
{
  FILE *fp;
  fp=fopen(name, "w+");
  if(fp == NULL)
  {
    fprintf(stderr, "ERROR: open \"%s\" failed \n", name);
    exit(2);
  }

  return (fp);
 }


