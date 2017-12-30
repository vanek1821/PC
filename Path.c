#include <stdio.h>
#include <stdlib.h>
#include "DateTime.h"
#include "Node.h"
#include "Path.h"

/**
Creates new path
params: 
int id - id of path
returns:
Path *path
*/
Path *createPath(int id){
	Path *tmp=NULL;
	tmp = malloc(sizeof(Path));
	tmp->id = id;
	tmp->pathSize = 0;
	tmp->pointer = 0;
	tmp->nodePath = malloc(sizeof(Node*)*tmp->pathSize);
	tmp->metric = 0;
	return(tmp);
}
/**
Prints path
params:
Path *p - path to print
*/
void printPath(Path *p){
	int i = 0;
	Node *tmp = NULL;
	DateTime *tmpDate = NULL;
	
	for (i = 0; i < p->pointer-1; i++) {
		tmp = p->nodePath[i];
		printf("%d-", tmp->name);
	}
	tmp = p->nodePath[i];
	printf("%d;", tmp->name);

	for (i = 0; i < p->pointer-1; i++) {
			if((p->nodePath[i]!=NULL)&&(i!=0)){
				tmp = p->nodePath[i];
				tmpDate = tmp->date;
				printf("%d-%02d-%02d,", tmpDate->year, tmpDate->month, tmpDate->day);
			}
		}
	tmp = p->nodePath[i];
	tmpDate = tmp->date;
	printf("%d-%02d-%02d", tmpDate->year, tmpDate->month, tmpDate->day);
	printf(";%d\n",p->metric);
	return;
}

/**
Adds node at the end of path
params:
Path *p - path
Node *node - node to be added
*/
void addToPath(Path *p, Node *node){
	p->nodePath = realloc(p->nodePath, sizeof(Node*) * (p->pathSize+1));
	p->nodePath[p->pointer] = (Node*) node;
	p->pointer++;
	p->pathSize = p->pointer;
}

/**
Removes last node in path
params:
Path *p - path
*/
void removeFromPath(Path *p){
	p->nodePath = realloc(p->nodePath, sizeof(Node*) * (p->pathSize-1));
	p->pointer--;
	p->pathSize = p->pointer;
	p->nodePath[p->pointer] = NULL;
	return;
}

/**
Counts metric of path
params: 
Path *p - path
*/
void countMetric(Path* p){
	int i;
	DateTime *max = NULL;
	DateTime *min = NULL;
	Node *tmp = NULL;
	DateTime *tmpDate = NULL;

	int maxYear = 0;
	int maxMonth = 0;
	int maxDay = 0;
	int minYear = 10000;
	int minMonth = 13;
	int minDay = 32;

	for (i = 1; i < p->pointer; i++){
			tmp = p->nodePath[i];
			tmpDate = tmp->date;

			if(tmpDate->year < minYear){
				minYear = tmpDate->year;
				minMonth = tmpDate->month;
				minDay = tmpDate->day;	
			} 

			else if(tmpDate->year == minYear){
				if(tmpDate->month < minMonth) {
					minYear = tmpDate->year;
					minMonth = tmpDate->month;
					minDay = tmpDate->day;	
				} 

				else if(tmpDate->month == minMonth){
					if(tmpDate->day < minDay) {
						minYear = tmpDate->year;
						minMonth = tmpDate->month;
						minDay = tmpDate->day;	
					} 
				}
			}

			if(tmpDate->year>maxYear){
				maxYear = tmpDate->year;
				maxMonth = tmpDate->month;
				maxDay = tmpDate->day;	
			}

			else if (tmpDate->year == maxYear){
				if(tmpDate->month > maxMonth){
					maxYear = tmpDate->year;
					maxMonth = tmpDate->month;
					maxDay = tmpDate->day;	
				} 

				else if(tmpDate->month == maxMonth){
					if(tmpDate->day > maxDay){
						maxYear = tmpDate->year;
						maxMonth = tmpDate->month;
						maxDay = tmpDate->day;	
						} 
					}
				}
	}

	max = createDateTime(maxYear, maxMonth, maxDay);
	min = createDateTime(minYear, minMonth, minDay);
	p->metric = getDifference(min, max);
	free(min);
	free(max);
	return;
}