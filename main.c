#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Node.h"
#include "Path.h"

FILE *inpf, *outf;

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}
void savePath(Path* paths[], Path*p){
	int i=0;
	int j=0;

	while(paths[i]!=0){
		i++;
	}

	Path *tmp = createPath(i);
		for (j = 0; j < p->pathSize; j++) {
			addToPath(tmp, p->nodePath[j]);
		}


	paths[i] = tmp;


}

void dfs(Path *paths[], Path *p, node *nodes[], int start, int end, int node_count, int maxLength){
	node * pointNode = NULL;
	pointNode = getNode(nodes, start, node_count);
	addToPath(p, pointNode->name);
	if(pointNode->name == end){
		savePath(paths, p);
		return;
	}
	pointNode->visited = 1;
	node *nextNode = NULL;

	while(pointNode->next!=NULL){
		pointNode = (node*)pointNode->next;
		nextNode = getNode(nodes, pointNode->name, node_count);
		if(maxLength!=0){
			if(p->pointer>=maxLength) return;
		}
		if (nextNode->visited == 0){
			nextNode->visited =1;
			dfs(paths, p, nodes, nextNode->name, end, node_count, maxLength);
			removeFromPath(p);
			nextNode->visited =0;
		}
	}
}


int main(int argc, char* argv[]){
	printf("start\n");
	FILE *inpf = fopen("data.csv", "r");
	FILE *outf = fopen("output.txt", "w");
	char line[500];
	int node1, node2, day, month, year = 0;
	int line_count=0;
	int record_count = 0;
	int i = 0;

	while(fgets(line, 500, inpf)){
		line_count++;
	}
	record_count = line_count*2;
	int *records_tmp =(int*) malloc(sizeof(int)*record_count);

	rewind(inpf);

	//read file for lines
	while(fgets(line, 500 ,inpf)){
		char *pch;

		pch = strtok(line, ";");
		node1 = atoi(pch);

		pch = strtok(NULL, ";");
		node2 = atoi(pch);

		pch = strtok(NULL, "-");
		year = atoi(pch);

		pch = strtok(NULL, "-");
		month = atoi(pch);

		pch = strtok(NULL, "-");
		day = atoi(pch);

		records_tmp[i] = node1;
		i++;
		records_tmp[i] = node2;
		i++;

	}
	int* records2_tmp = (int *)malloc(sizeof(int)*record_count);
	memcpy(records2_tmp, records_tmp, record_count*sizeof(int));
	qsort(records2_tmp, record_count, sizeof(int), cmpfunc);

	int previous = 0;
	int node_count = 0;
	node ** nodes = (node**)malloc(sizeof(node*)*record_count);

	for (i = 0; i < record_count; i++) {
		if(records2_tmp[i]>previous){
			node * tmp;
			previous = records2_tmp[i];
			tmp = createNode(records2_tmp[i]);
			nodes[node_count] = tmp;
			node_count++;
		}
	}

	int j = 0;
	for (i = 0; i < node_count; i++) {
		for (j = 0; j < record_count; j+=2) {
			if(nodes[i]->name == records_tmp[j]){
				addNode(nodes[i], records_tmp[j+1]);
			}
			if(nodes[i]->name == records_tmp[j+1]){
				addNode(nodes[i], records_tmp[j]);
			}
		}
	}
	printf("recordCount: %d\nnodeCount: %d\n\n\n", record_count, node_count);
	printf("DFS\n------------------\n");
	Path ** paths = (Path**)calloc(100000,sizeof(Path*));

	Path *p = createPath(0);
	int source, destination, maxLength;
	source = 1;
	destination = 2;
	maxLength = 4;
	dfs(paths, p, nodes, source, destination, node_count, maxLength );

	i=0;
	while(paths[i]!=0){
		printPath(paths[i], outf);
		i++;
	}
	if(i==0){
		printf("Mezi body %d a %d neexistuje cesta.\n", source, destination);
	}
	printf("Počet cest: %d\n",i);
	free(nodes);
	free(records2_tmp);
	free(records_tmp);
	free(paths);
	fclose(inpf);
	return 0;
}















