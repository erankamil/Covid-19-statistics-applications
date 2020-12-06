# Covid-19-statistics-applications
A bash program that retrieves statistics for each country(except USA) in the world using REST APIs from the following link: https://documenter.getpostman.com/view/10808728/SzS8rjbc?version=latest

- The corona_api_script.sh file its a bash script that downloads the countries names that the REST API supports, 
and then for each country downloads the corona statistics from 2020-01-21 until now (statistics include: Active,Confirmed,Deaths,Date,Recovered).


- The _print_by_date.c file its a executalbe program that prints all countries specific data according to:
i. Date
ii. Key (Confirmed, Death, Recovered, active)

- The _print_graph.c file its a executable program that prints a “graph” according to:
i.	country name
ii.	Key (Confirmed, Death, Recovered, active)


- The libEx01utils.c file its a Shared Library (complies to libEx01utils.so file), all the executable programs retrive data structures(an array with all countries, each country cell has all the corona stataistics for the relevant country) from this library.

![print_by_date](https://user-images.githubusercontent.com/62330191/101274551-b921d380-37a7-11eb-8aaf-6f903c9e6687.PNG)

![print_graph](https://user-images.githubusercontent.com/62330191/101274603-47965500-37a8-11eb-8b52-2fa2b7e39b61.png)

![data_to_csv](https://user-images.githubusercontent.com/62330191/101274620-63016000-37a8-11eb-957b-a35405434557.png)

