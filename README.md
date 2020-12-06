# Covid-19-statistics-applications

- The corona_api_script.sh file its a bash program that retrieves statistics for each country(except USA) in the world using REST APIs from the following link: https://documenter.getpostman.com/view/10808728/SzS8rjbc?version=latest and saves them to local directory.

- The _print_by_date.c file will compile to an executalbe program that prints all countries specific data according to:
i. Date
ii. Key (Confirmed, Death, Recovered, active)

- The _print_graph.c file will compile to an executable program that prints a “graph” according to:
i.	country name
ii.	Key (Confirmed, Death, Recovered, active)

- The _country_data_to_csv.c file will compile to an executable program that creates an csv file and exports all the corona statistics of the given country to this csv file.

- The libEx01utils.c file will compile to a Shared Library, all the executable programs retrive data structures(an array with all countries, each country cell has all the corona stataistics for the relevant country) from this library.

- Makefile : run 'make all' command in the terminal,
the Makefile will complie each *.c  file to executable  *.out file, and each lib*.c file to lib*.so shared library

screen shots of the output for each program:

![print_by_date](https://user-images.githubusercontent.com/62330191/101274690-dacf8a80-37a8-11eb-8748-e0aa9833ff5f.PNG)

![print_graph](https://user-images.githubusercontent.com/62330191/101274603-47965500-37a8-11eb-8b52-2fa2b7e39b61.png)

![data_to_csv](https://user-images.githubusercontent.com/62330191/101274620-63016000-37a8-11eb-957b-a35405434557.png)

