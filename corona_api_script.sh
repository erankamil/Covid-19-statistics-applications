#!/bin/bash


curl --location --request GET 'https://api.covid19api.com/countries'|  tr "," "\n"  | grep "Slug" | awk -F ":" '{print $2}' | grep -v 'Uninted State of America\|united-states' | tr -d  '"' | sort -d > countries_list.txt



mkdir countries

cd countries 

while read curr_country; do
wget https://api.covid19api.com/total/country/$curr_country
 tr '\{,' '\n' < $curr_country > $curr_country.tmp
 grep  'Date\|Confirmed\|Deaths\|Recovered\|Active'  < $curr_country.tmp > $curr_country.tmp2
 tr "}" "\n" < $curr_country.tmp2  > $curr_country.tmp3
 tr -d "]" < $curr_country.tmp3 > $curr_country
 rm $curr_country.tmp
 rm $curr_country.tmp2
 rm $curr_country.tmp3

done < ../countries_list.txt
