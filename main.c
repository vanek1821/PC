#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Node.h"

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}
void dfs(node *nodes[], int start, int end, int node_count ){

	node * startNode = NULL;
	startNode = getNode(nodes, start, node_count);
	startNode->visited = 1;
	printf("Aktuální node: ");
	print_node_name(startNode);

	while(startNode->next!=NULL){
		startNode = startNode->next;
		if(getNode(nodes, startNode->name, node_count)->visited==0){
			if(startNode->name == end){
				getNode(nodes, end, node_count)->visited=0;
			}
			startNode->visited=1;
			dfs(nodes, startNode->name, end,node_count );
		}
	}

}


int main(int argc, char* argv[]){
	printf("start\n");
	FILE *inpf = fopen("data1.csv", "r");
	char line[500];
	int node1, node2, day, month, year = 0;
	int line_count=0;
	int record_count = 0;
	int i = 0;

	//Get count of lines in file
	while(fgets(line, 500, inpf)){
		line_count++;
	}
	record_count = line_count*2;
	//int records_tmp[record_count];
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
			tmp = create_node(records2_tmp[i]);
			//tmp->name = records2_tmp[i];
			//tmp->next = NULL;
			//tmp->visited = 0;
			nodes[node_count] = tmp;
			node_count++;
		}
	}


	int j = 0;
	for (i = 0; i < node_count; i++) {
		for (j = 0; j < record_count; j+=2) {
			if(nodes[i]->name == records_tmp[j]){
				add_node(nodes[i], records_tmp[j+1]);
			}
			if(nodes[i]->name == records_tmp[j+1]){
				add_node(nodes[i], records_tmp[j]);
			}
		}
	}
	for (i = 0; i < node_count; i++){
		print_node(nodes[i]);
	}

	printf("recordCount: %d\nnodeCount: %d\n\n\n", record_count, node_count);

	dfs(nodes, 2, 4, node_count );
	free(nodes);
	free(records2_tmp);
	free(records_tmp);
	fclose(inpf);
	return 0;
}















