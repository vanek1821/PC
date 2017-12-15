#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
#include "Path.h"



Path *createPath(int id){
	Path *tmp=NULL;
	tmp = malloc(sizeof(Path));
	tmp->id = id;
	tmp->pathSize = 1;
	tmp->pointer = 0;
	tmp->nodePath = (int*) malloc(sizeof(int)*tmp->pathSize);
	return(tmp);
}
void printPath(Path *p, FILE* outf){
	int i = 0;
	//printf("Path%d :", p->id);
	fprintf(outf, "Path%d: ", p->id);
	for (i = 0; i < p->pathSize; i++) {
		if(p->nodePath[i]!=NULL){
			printf("%d-", p->nodePath[i]);
			fprintf(outf, " %d ", p->nodePath[i]);
		}
	}
	printf("|| delka cesty: %d \n",p->pointer);
	fprintf(outf, "\n");
	return;
}
void addToPath(Path *p, int nodeName){
	int i = 0;
	if(p->pointer>=p->pathSize){
		int *tmp = (int*)malloc(sizeof(int)*(p->pathSize*2));
		for (i = 0; i <= p->pointer; i++) {
			tmp[i] = p->nodePath[i];
		}
		p->nodePath = tmp;
		p->pathSize = p->pathSize*2;
		//free(tmp);
	}
	//printf("na pozici %d přidávám node %d\n", p->pointer, nodeName);
	p->nodePath[p->pointer] = nodeName;
	p->pointer++;

}
void removeFromPath(Path *p){
	p->pointer--;
	p->nodePath[p->pointer] = NULL;

	//printf("path pointer: %d\n", p->pointer );
	return;
}












