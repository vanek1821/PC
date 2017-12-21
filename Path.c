#include <stdio.h>
#include <stdlib.h>
#include "DateTime.h"
#include "Node.h"
#include "Path.h"


Path *createPath(int id){
	Path *tmp=NULL;
	tmp = malloc(sizeof(Path));
	tmp->id = id;
	tmp->pathSize = 1;
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
	int i = 0;
	if(p->pointer>=p->pathSize){
		Node **tmp = (Node*) malloc(sizeof(Node*)*(p->pathSize*2));
		for (i = 0; i <= p->pointer; i++) {
			tmp[i] = (Node*) p->nodePath[i];
		}
		//free(p->nodePath);
		p->nodePath = tmp;
	}
	p->nodePath[p->pointer] = (Node*) node;
	p->pointer++;
	p->pathSize = p->pointer;

}
void removeFromPath(Path *p){
	p->pointer--;
	p->nodePath[p->pointer] = NULL;

	return;
}
void countMetric(Path* p){
	int i;
	DateTime *max = NULL;
	DateTime *min = NULL;
	Node *tmp = NULL;
	DateTime *tmpDate = NULL;

	max = createDateTime(0,0,0);
	min = createDateTime(10000,13,32);
	for (i = 1; i < p->pointer; i++) {
			if(p->nodePath[i]!=NULL){
				tmp = p->nodePath[i];
				tmpDate = tmp->date;
				if(tmpDate->year < min->year) min = tmpDate;
				else if (tmpDate->year == min->year){
					if(tmpDate->month < min->month) min = tmpDate;
					else if(tmpDate->month == min->month){
						if(tmpDate->day < min->day) min = tmpDate;
					}
				}
				if(tmpDate->year>max->year) max = tmpDate;
					else if (tmpDate->year == max->year){
						if(tmpDate->month > max->month) max = tmpDate;
						else if(tmpDate->month == max->month){
							if(tmpDate->day > max->day) max = tmpDate;
						}
					}
			}
		}
	p->metric = getDifference(min, max);
	return;
}












