#include <stdio.h>
#include <stdlib.h>
#include "DateTime.h"
#include "Node.h"
#include "Path.h"


Path *createPath(int id){
	Path *tmp=NULL;
	tmp = malloc(sizeof(Path));
	tmp->id = id;
	tmp->pathSize = 0;
	tmp->pointer = 0;
	tmp->nodePath = (Node*) malloc(sizeof(Node*)*tmp->pathSize);
	tmp->metric = 0;
	return(tmp);
}
void printPath(Path *p){
	int i = 0;
	Node *tmp = NULL;
	DateTime *tmpDate = NULL;
	for (i = 0; i < p->pointer-1; i++) {
		if(p->nodePath[i]!=NULL){
			tmp = p->nodePath[i];
			printf("%d-", tmp->name);
		}
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

void addToPath(Path *p, Node *node){
	p->nodePath = realloc(p->nodePath, sizeof(Node*) * (p->pathSize+1));
	p->nodePath[p->pointer] = (Node*) node;
	p->pointer++;
	p->pathSize = p->pointer;

}
void removeFromPath(Path *p){
	p->nodePath = realloc(p->nodePath, sizeof(Node*) * (p->pathSize-1));
	p->pointer--;
	p->pathSize = p->pointer;
	p->nodePath[p->pointer] = NULL;
	return;
}
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


	//max = createDateTime(0,0,0);
	//min = createDateTime(10000,13,32);

	for (i = 1; i < p->pointer; i++) {
			if(p->nodePath[i]!=NULL){
				tmp = p->nodePath[i];
				tmpDate = tmp->date;
				if(tmpDate->year < minYear){
					minYear = tmpDate->year;
					minMonth = tmpDate->month;
					minDay = tmpDate->day;	
				} 
				else if (tmpDate->year == minYear){
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
	}
	printf("b\n");
	max = createDateTime(maxYear, maxMonth, maxDay);
	min = createDateTime(minYear, minMonth, minDay);
	/*printf("max: %d.%d.%d\n", max->day, max->month, max->year);
	printf("min: %d.%d.%d\n", min->day, min->month, min->year);*/
	p->metric = getDifference(min, max);
	free(min);
	free(max);
	return;
}












