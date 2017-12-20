#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DateTime.h"
#include "Node.h"
#include "Path.h"


FILE *inpf, *outf;
int pathCount = 0;
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}
void savePath(Path* paths[], Path*p){
	int j=0;

	Path *tmp = createPath(pathCount);
		for (j = 0; j < p->pointer; j++) {
			addToPath(tmp, p->nodePath[j]);
		}
	paths[pathCount] = tmp;
	pathCount++;

}

/* funkční dfs void dfs(Path *paths[], Path *p, Node *Nodes[], int start, int end, int node_count, int maxLength){
	Node * pointNode = NULL;
	pointNode = getNode(Nodes, start, node_count);
	addToPath(p, pointNode->name);
	if(pointNode->name == end){
		savePath(paths, p);
		return;
	}
	pointNode->visited = 1;
	Node *nextNode = NULL;

	while(pointNode->next!=NULL){
		pointNode = (Node*)pointNode->next;
		nextNode = getNode(Nodes, pointNode->name, node_count);
		if(maxLength!=0){
			if(p->pointer>maxLength) return;
		}
		if (nextNode->visited == 0){
			nextNode->visited =1;
			dfs(paths, p, Nodes, nextNode->name, end, node_count, maxLength);
			removeFromPath(p);
			nextNode->visited =0;
		}
	}
}*/
void dfs(Path *paths[], Path *p, Node *nodes[], Node *startNode, int end, int node_count, int maxLength){
	Node * pointNode = NULL;


	pointNode = getNode(nodes, startNode->index);
	//printf("dfs pro pointNode: %d\n", pointNode->name);
	if(pointNode->name == end){
		//addToPath(p, pointNode);
		savePath(paths, p);
		return;
	}
	pointNode->visited = 1;
	Node *nextNode = NULL;

	while(pointNode->next!=NULL){
		pointNode = (Node*)pointNode->next;

		nextNode = getNode(nodes, pointNode->nodePointer);
		//printf("nextNode-> %d\n", nextNode->name);

		if(maxLength!=0){
			if(p->pointer>maxLength) return;
		}
		if (nextNode->visited == 0){
			nextNode->visited =1;
			addToPath(p, pointNode);
			dfs(paths, p, nodes, nextNode, end, node_count, maxLength);
			removeFromPath(p);
			nextNode->visited =0;
		}

	}
	//free(pointNode);
	//free(nextNode);
}



int main(int argc, char* argv[]){
	printf("start\n");


	FILE *inpf = fopen("data1.csv", "r");
	FILE *outf = fopen("output.txt", "w");
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
	int node_count = 0;
	Node ** nodes = (Node**)malloc(sizeof(Node*)*record_count);

	for (i = 0; i < record_count; i++) {
		if(records2_tmp[i]>previous){
			Node * tmp;
			previous = records2_tmp[i];
			tmp = createNode(records2_tmp[i]);
			tmp->index = node_count;
			nodes[node_count] = tmp;
			node_count++;
		}
	}


	j = 0;
	for (i = 0; i < node_count; i++) {
		for (j = 0; j < record_count; j+=2) {
			if(nodes[i]->name == records_tmp[j]){
				addNode(nodes[i], nodes, records_tmp[j+1], createDateTime(years[j/2], months[j/2], days[j/2]));
			}
			if(nodes[i]->name == records_tmp[j+1]){
				addNode(nodes[i], nodes, records_tmp[j], createDateTime(years[j/2], months[j/2], days[j/2]));
			}
		}
	}
	free(records2_tmp);
	free(records_tmp);
	/*for(i = 0; i<node_count; i++){
		printNode(nodes[i], outf);
	}*/
	printf("recordCount: %d\nNodeCount: %d\n\n\n", record_count, node_count);

	//Path ** paths = (Path**)calloc(250000000,sizeof(Path*));
	Path ** paths = (Path**)malloc(sizeof(Path*)*10000000);
	Path *p = createPath(0);
	int source, destination, maxLength;
	source = 1;
	destination = 6;
	maxLength = 0;
	Node* sourceNode = findNode(nodes, source, node_count);
	Node* endNode = findNode(nodes, destination, node_count);
	if((sourceNode==NULL)||(endNode==NULL)){
		printf("Počáteční nebo konečný node neexistuje\n");
	}
	else{
		printf("DFS\n------------------\n");
		addToPath(p, sourceNode);
		dfs(paths, p, nodes, sourceNode, destination, node_count, maxLength );
		i=0;
			for(i=0; i<pathCount; i++){
				printPath(paths[i], outf);
				//printf("%d\n",i);
			}
			if(pathCount==0){
				printf("Mezi body %d a %d neexistuje cesta.\n", source, destination);
			}
			printf("Počet cest: %d\n",pathCount);
	}
	int test = countMetric(paths[1]);


	free(nodes);

	free(paths);
	fclose(inpf);
	return 0;
}















