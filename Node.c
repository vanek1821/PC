#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Node.h"


node *create_node(int name){
	node *tmp = NULL;
	tmp = malloc(sizeof(node));
	tmp->name = name;
	tmp->next = NULL;
	tmp->visited = 0;

	return(tmp);
}

void print_node(node *n){
	node * tmp = malloc(sizeof(node));
	tmp = n;
	if(!tmp){
		printf("NULL");
		return;
	}
	else{
		printf("%d", tmp->name);
		tmp = tmp->next;
		while(tmp!=NULL){
			printf(" -> %d", tmp->name);
			tmp = tmp->next;
		}
		printf("\n");
	}
}
void print_node_name(node *n){
	node * tmp = malloc(sizeof(node));
	tmp = n;
	if(!tmp){
		printf("NULL");
		return;
	}
	else{
		printf("%d ", tmp->name);
		printf("\n");
	}
	fflush(stdout);
}
void add_node(node *head, int name){
	node * current = head;
	while(current->next != NULL){
		current = current->next;
	}
	current->next = malloc(sizeof(node));
	current = current->next;
	current->name = name;
	current->next = NULL;
	current->visited = 0;
	return;
}
node *getNode(node *nodes[], int name, int nodeCount){
	int i = 0;
	for (i = 0; i < nodeCount; i++) {
		if(nodes[i]->name == name)
			return nodes[i];
	}
	printf("node %d nenalezen\n", name);
	return NULL;
}
