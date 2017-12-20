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
	//tmp->nodePath = (int) malloc(sizeof(int)*tmp->pathSize);
	return(tmp);
}
void printPath(Path *p, FILE* outf){
	int i = 0;
	Node *tmp = NULL;
	DateTime *tmpDate = NULL;
	fprintf(outf, "Path%d: ", p->id);
	for (i = 0; i < p->pointer-1; i++) {
		if(p->nodePath[i]!=NULL){
			tmp = p->nodePath[i];
			printf("%d-", tmp->name);
			fprintf(outf, " %d", tmp->name);
		}
	}
	tmp = p->nodePath[i];
	printf("%d;", tmp->name);

	for (i = 0; i < p->pointer-1; i++) {
			if((p->nodePath[i]!=NULL)&&(i!=0)){
				tmp = p->nodePath[i];
				tmpDate = tmp->date;
				printf("%d-%d-%d,", tmpDate->year, tmpDate->month, tmpDate->day);
				fprintf(outf, "%d-%d-%d,", tmpDate->year, tmpDate->month, tmpDate->day);
			}
		}
	tmp = p->nodePath[i];
	tmpDate = tmp->date;
	printf("%d-%d-%d", tmpDate->year, tmpDate->month, tmpDate->day);

	fprintf(outf, " %d", tmp->name);
	printf(";%d\n",p->pathSize-1);
	fprintf(outf, "|| delka cesty: %d",p->pointer-1);
	fprintf(outf, "\n");
	return;
}
/*funkcni int addToPath void addToPath(Path *p, int nodeName){
	int i = 0;
	if(p->pointer>=p->pathSize){
		int *tmp = (int*)malloc(sizeof(int)*(p->pathSize*2));
		for (i = 0; i <= p->pointer; i++) {
			tmp[i] = p->nodePath[i];
		}
		p->nodePath = tmp;
		//p->pathSize = p->pathSize*2;
		//free(tmp);
	}
	//printf("na pozici %d přidávám node %d\n", p->pointer, nodeName);
	p->nodePath[p->pointer] = nodeName;
	p->pointer++;
	p->pathSize = p->pointer;

}*/
void addToPath(Path *p, Node *node){
	int i = 0;
	if(p->pointer>=p->pathSize){
		Node **tmp = (Node*) malloc(sizeof(Node*)*(p->pathSize*2));
		for (i = 0; i <= p->pointer; i++) {
			tmp[i] = (Node*) p->nodePath[i];
		}
		p->nodePath = tmp;
		//p->pathSize = p->pathSize*2;
		//free(tmp);
	}
	//printf("na pozici %d přidávám node %d\n", p->pointer, nodeName);
	p->nodePath[p->pointer] = (Node*) node;
	p->pointer++;
	p->pathSize = p->pointer;

}
void removeFromPath(Path *p){
	p->pointer--;
	p->nodePath[p->pointer] = NULL;

	//printf("path pointer: %d\n", p->pointer );
	return;
}
int countMetric(Path* p){
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
				if(tmpDate->year<min->year) min = tmpDate;
				else if (tmpDate->year == min->year){
					if(tmpDate->month<min->month) min = tmpDate;
					else if(tmpDate->month == min->month){
						if(tmpDate->day < min->day) min = tmpDate;
					}
				}
				if(tmpDate->year>max->year) max = tmpDate;
					else if (tmpDate->year == max->year){
						if(tmpDate->month > max->month) max = tmpDate;
						else if(tmpDate->month == max->month){
							if(tmpDate->day < max->day) max = tmpDate;
						}
					}
			}
		}
	printf("maxDate = %d.%d.%d\n", max->day, max->month, max->year);
	printf("minDate = %d.%d.%d\n", min->day, min->month, min->year);
	return 0;
}












