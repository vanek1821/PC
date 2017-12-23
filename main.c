#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DateTime.h"
#include "Node.h"
#include "Path.h"


FILE *inpf;
int pathCount = 0;

int cmpfunc (const void *a, const void *b) {
   return ( *(int*)a - *(int*)b );
}

int cmpFuncPaths(const void *a, const void *b){
	Path **x = (Path**)a;
	Path **y = (Path**)b;

	int value = (*x)->pathSize - (*y)->pathSize;
	if(value==0){
		value = (*x)->metric - (*y)->metric;
	}
	return value;
}

void savePath(Path* paths[], Path*p){
	int j;
	Path *tmp = createPath(pathCount);
		for (j = 0; j < p->pointer; j++) {
			addToPath(tmp,(Node*) p->nodePath[j]);
			}
	paths[pathCount] = tmp;
	pathCount++;
}

void dfs(Path *paths[], Path *p, Node *nodes[], Node *startNode, int end, int nodeCount, int maxLength){

	//Node * pointNode = NULL;
	Node * pointNode = getNode(nodes, startNode->index);

	if(pointNode->name == end){
		savePath(paths, p);
		return;
	}
	pointNode->visited = 1;
	Node *nextNode = NULL;

	while(pointNode->next!=NULL){
		pointNode = (Node*)pointNode->next;
		nextNode = getNode(nodes, pointNode->nodePointer);
		if(maxLength!=0){
			if(p->pointer>maxLength) return;
		}
		if (nextNode->visited == 0){
			nextNode->visited =1;
			addToPath(p, pointNode);
			dfs(paths, p, nodes, nextNode, end, nodeCount, maxLength);
			removeFromPath(p);
			nextNode->visited =0;
		}
	}
}

int main(int argc, char* argv[]){
	if((argv[1]==NULL)||(argv[2]==NULL)||(argv[3]==NULL)||(argv[4]==NULL)){
		printf("Špatně zadané vstupní parametry.\nParametry musí být ve tvaru: soubor.csv [počáteční vrchol] [cílový vrchol] [maximální délka cesty]\n");
		return 0;
	}
	FILE *inpf = fopen(argv[1], "r");
	int source = atoi(argv[2]);
	int destination = atoi(argv[3]);
	int maxLength = atoi(argv[4]);
	char line[500];
	int Node1, Node2, day, month, year = 0;
	int line_count=0;
	int record_count = 0;
	int i = 0;
	int j = 0;

	while(fgets(line, 500, inpf)){
		line_count++;
	}
	record_count = line_count*2;
	int *records_tmp =(int*) malloc(sizeof(int)*record_count);
	int *years = (int*) malloc(sizeof(int)*line_count);
	int *months = (int*) malloc(sizeof(int)*line_count);
	int *days = (int*) malloc(sizeof(int)*line_count);

	rewind(inpf);

	//read file for lines
	while(fgets(line, 500 ,inpf)){
		char *pch;

		pch = strtok(line, ";");
		Node1 = atoi(pch);

		pch = strtok(NULL, ";");
		Node2 = atoi(pch);

		pch = strtok(NULL, "-");
		year = atoi(pch);

		pch = strtok(NULL, "-");
		month = atoi(pch);

		pch = strtok(NULL, "-");
		day = atoi(pch);

		records_tmp[i] = Node1;
		i++;
		records_tmp[i] = Node2;
		i++;
		years[j] = year;
		months[j] = month;
		days[j] = day;
		j++;


	}
	int* records2_tmp = (int *)malloc(sizeof(int)*record_count);
	memcpy(records2_tmp, records_tmp, record_count*sizeof(int));
	qsort(records2_tmp, record_count, sizeof(int), cmpfunc);

	int previous = 0;
	int nodeCount = 0;
	Node ** nodes = (Node**)malloc(sizeof(Node*)*record_count);

	for (i = 0; i < record_count; i++) {
		if(records2_tmp[i]>previous){
			Node * tmp;
			previous = records2_tmp[i];
			tmp = createNode(records2_tmp[i]);
			printf("creating node: %d\n", tmp->name);
			tmp->index = nodeCount;
			nodes[nodeCount] = tmp;
			nodeCount++;
		}
	}

	j = 0;
	for (i = 0; i < nodeCount; i++) {
		for (j = 0; j < record_count; j+=2) {
			if(nodes[i]->name == records_tmp[j]){
				printf("adding node: %d to %d\n",records_tmp[j+1], nodes[i]->name);
				addNode(nodes[i], nodes, records_tmp[j+1], createDateTime(years[j/2], months[j/2], days[j/2]));
			}
			if(nodes[i]->name == records_tmp[j+1]){
				printf("adding node: %d to %d\n",records_tmp[j], nodes[i]->name);
				addNode(nodes[i], nodes, records_tmp[j], createDateTime(years[j/2], months[j/2], days[j/2]));
			}
		}
	}
	free(records2_tmp);
	records2_tmp = NULL;
	free(records_tmp);
	records_tmp = NULL;

	Path ** paths = (Path**)malloc(sizeof(Path*)*10000000);
	Path *p = createPath(0);

	Node* sourceNode = findNode(nodes, source, nodeCount);
	Node* endNode = findNode(nodes, destination, nodeCount);

	if((sourceNode==NULL)||(endNode==NULL)){
	}
	else{
		addToPath(p, sourceNode);
		dfs(paths, p, nodes, sourceNode, destination, nodeCount, maxLength );
		i=0;
		for(i=0; i<pathCount; i++){
			countMetric(paths[i]);
		}
		qsort(paths, pathCount, sizeof(Path*), cmpFuncPaths);
		for(i=0; i<pathCount; i++){
			printPath(paths[i]);
		}

	}
	for(i=0; i<nodeCount;i++){
		freeNode(nodes[i]);
		free(nodes[i]->date);
		free(nodes[i]);
	}
	free(nodes);
	for(i=0; i<pathCount;i++){
		for(j=0; j<paths[i]->pointer;j++){
			free(paths[i]->nodePath[j]);
		}
		free(paths[i]->nodePath);
		free(paths[i]);
		}
	free(paths);
	free(years);
	free(months);
	free(days);
	fclose(inpf);
	return 0;
}















