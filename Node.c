#include <stdio.h>
#include <stdlib.h>
#include "node.h"

node *create_node(int name){
	node *tmp = NULL;
	tmp = malloc(sizeof(node));
	tmp->name = name;
	tmp->next = NULL;

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
void add_node(node *head, int name){
	node * current = head;
	while(current->next != NULL){
		current = current->next;
	}
	current->next = malloc(sizeof(node));
	current = current->next;
	current->name = name;
	current->next = NULL;
	return;
}
