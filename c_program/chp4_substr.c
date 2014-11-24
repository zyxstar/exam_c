#include <stdio.h>
#define MAXLINE 1000

int get_line(char line[], int max);
int str_index(char source[], char searchfor[]);

char pattern[] = "ould";

int main(){

	char line[MAXLINE];
	int found = 0;

	while(get_line(line, MAXLINE) > 0)
		if(str_index(line, pattern) >= 0){
			printf("%s", line);
			found++;
		}
	return found;
}

int get_line(char line[], int lim){
	int c, i = 0;
	while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
		line[i++] =  c;
	if(c == '\n') line[i++] = c;
	line[i] = '\0';
	return i;	
}

int str_index(char source[], char searchfor[]){
	int i, j, k;
	for(i = 0; source[i] != '\0'; i++){
		for(j = i, k = 0; searchfor[k] != '\0' && source[j] == searchfor[k]; j++, k++);
		if(k > 0 && searchfor[k] == '\0')
			return i;
	}
	return -1;	
}

