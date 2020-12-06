# include "libEx01utils.h"

DataPerDate*** get_all_countries_data(int* arr_size)
{
	int num_of_countries;
	char** country_names = get_countries_names(&num_of_countries); 
	DataPerDate*** arr_of_countries = (DataPerDate***)malloc(sizeof(DataPerDate**)*num_of_countries);
	for(int i = 0; i < num_of_countries; i++)
	{
		arr_of_countries[i] = get_corona_data_of_country(country_names[i]);
	}
	
	*arr_size = num_of_countries;
	return arr_of_countries;
}

char** get_countries_names(int* arr_size)
{
	char** countries_name =(char**)malloc(sizeof(char*)*NUM_OF_COUNTRIES);
	int log_size = 0, phy_size = NUM_OF_COUNTRIES;
	char country_names_file[MAX_STRING_LENGTH] = COUNTRIES_NAMES_FILE,country_name[MAX_STRING_LENGTH];
	FILE* fp = open_file(country_names_file);
	
 	while(fscanf(fp, "%s", country_name) != EOF)
 	{
 		if(log_size == phy_size)
 		{
 			phy_size*=2;
 			countries_name = (char**)realloc(countries_name, sizeof(char*)*phy_size);
 		}
 		
 		countries_name[log_size] =(char*)malloc(sizeof(char)*strlen(country_name) + 1);
 		strcpy(countries_name[log_size], country_name);
 		log_size++;
 	}
 	
 	countries_name = (char**)realloc(countries_name, sizeof(char*)*log_size + 1);
 	countries_name[log_size] = NULL;
 	*arr_size = log_size - 1;
	
	fclose(fp);
 	return countries_name;
}

DataPerDate** get_corona_data_of_country(char* country_name)
{
	char country_path[MAX_STRING_LENGTH] = COUNTRIES_DATA_PATH;
	strcpy(country_path + strlen(country_path) - 1, country_name);
	FILE* fp = open_file(country_path);
	int log_size = 0,phy_size = 350;
	DataPerDate** arr_of_corona_data = (DataPerDate**)malloc(sizeof(DataPerDate*)*phy_size);
 	char line_in_file[MAX_STRING_LENGTH],key[MAX_STRING_LENGTH];
 	char* value_of_key;
 	while(fscanf(fp, "%s", line_in_file) != EOF)
 	{
 		if(log_size == phy_size)
 		{
 			phy_size*=2;
 			arr_of_corona_data = (DataPerDate**)realloc(arr_of_corona_data,sizeof(DataPerDate*)*phy_size);
 		}			

		arr_of_corona_data[log_size] = (DataPerDate*)malloc(sizeof(DataPerDate));
 		for(int i = 0 ; i <  5; i++)
 		{
 			value_of_key = get_value_of_key(key, line_in_file);
 			insert_data(arr_of_corona_data[log_size], key, value_of_key);
 			if( i != 4)
				fscanf(fp, "%s", line_in_file);
 		}

		log_size++; 	
 	}
 	
	arr_of_corona_data = (DataPerDate**)realloc(arr_of_corona_data,sizeof(DataPerDate*)*log_size + 1);
	arr_of_corona_data[log_size] = NULL;
	fclose(fp);
	
	return arr_of_corona_data;	
}


void insert_data(DataPerDate* curr_date,char* key, char* value_to_insert)
{	
	if(strcmp(key,"Confirmed") == 0)
		strcpy(curr_date->Confirmed, value_to_insert);
	else if(strcmp(key,"Deaths") == 0)	
		strcpy(curr_date->Deaths, value_to_insert);
	else if(strcmp(key,"Recovered") == 0)	
		strcpy(curr_date->Recovered, value_to_insert);
	else if(strcmp(key,"Active") == 0)	
		strcpy(curr_date->Active, value_to_insert);
	else if(strcmp(key,"Date") == 0)	
		strcpy(curr_date->Date, value_to_insert);	
}

char* get_value_of_key(char* key, char* line_in_file)
{
	char* value_of_key = (char*)malloc(sizeof(char)*MAX_STRING_LENGTH);
	int index_read = 0, index_write_key = 0,index_write_value = 0;
	while(line_in_file[index_read] != ':')
	{
	    if(line_in_file[index_read] != '"')
	    {
	    	key[index_write_key] = line_in_file[index_read];
	    	index_write_key++;
	    }

	    index_read++;	
	}

	index_read++;
	
	while(line_in_file[index_read] != '\0' && line_in_file[index_read] != 'T')
	{
		if(line_in_file[index_read] != '"')
		{
			value_of_key[index_write_value] = line_in_file[index_read];
			index_write_value++;
		}

		index_read++;
	}
	
	value_of_key[index_write_value] = '\0';
	key[index_write_key]= '\0';
	return value_of_key;
}


void free_countries_names(char** countries_names_arr)
{
	int i=0;
	while(countries_names_arr[i] != NULL)
	{
		free(countries_names_arr[i]);
		i++;
	}
	
	free(countries_names_arr);
}

void free_countries_data(DataPerDate*** arr,int size)
{
	for(int i = 0; i < size; i++)
	{
		free_country_arr(arr[i]);
	}
	
	free(arr);
}

void free_country_arr(DataPerDate** country_data_arr)
{
	int i=0;
	while(country_data_arr[i] != NULL)
	{
		free(country_data_arr[i]);
		i++;
	}
	
	free(country_data_arr);
}

int get_index_by_county_name(char*  country_name, char** names_arr, int num_of_countries)
{
	int index_to_return;
	for(int i = 0; i < num_of_countries; i++)
	{
		if(strcmp(names_arr[i],country_name) == 0)
		{
			index_to_return = i;
			break;
		}
	}
	
	return index_to_return;
}

FILE* open_file(char* name)
{
  FILE *fp;
  fp=fopen(name, "a+");
  if(fp == NULL)
  {
    fprintf(stderr, "ERROR: open \"%s\" failed \n", name);
    exit(2);
  }

  return (fp);
}
  
  
