#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "DateTime.h"
#include "Node.h"


Node *createNode(int name){
	  Node *tmp = NULL;
	  tmp = malloc(sizeof(Node));
	  tmp->name = name;
	  tmp->next = NULL;
	  tmp->index = 0;
	  tmp->nodePointer = 0;
	  tmp->visited = 0;
	  tmp->date = createDateTime(0,0,0);
	  return(tmp);
}

void printNode(Node *n){
	  Node * tmp = malloc(sizeof(Node));
	  DateTime *tmpDate = malloc(sizeof(DateTime));
	  tmp = n;
	  if(!tmp){
		  printf("NULL");
		  return;
	  }
	  else{
		  printf("%d on index %d", tmp->name, tmp->index);
		  tmp = (Node*)tmp->next;
		  tmpDate = (DateTime*)tmp->date;
		  while((tmp!=NULL)){
			  printf(" -> %d; %d-%d-%d pointTo: %d||", tmp->name, tmpDate->year, tmpDate->month, tmpDate->day, tmp->nodePointer);
		  tmp = tmp->next;
		  if(tmp!=NULL) tmpDate = tmp->date;
		}
		printf("\n");
	  }
	  return;
}

void printNodeName(Node *n){
  Node * tmp = malloc(sizeof(Node));
  tmp = n;
  if(!tmp){
    printf("NULL");
    return;
  }
  else{
    printf("%d ", tmp->name);

    printf("\n");
  }
  return;
}
int findNodePointer(Node *nodes[], int nodeName){
  int i = 0;
  while(nodes[i]->name != nodeName){
	  //printf("nodeName: %d\n", nodes[i]->name);
	  i++;
  }
  return i;

}
void addNode(Node *head, Node *nodes[], int name, DateTime *date){
  Node * current = head;
  while(current->next != NULL){
    current = (Node*)current->next;
  }
  current->next = malloc(sizeof(Node));
  current = (Node*)current->next;
  current->name = name;
  current->nodePointer = findNodePointer(nodes, name);
  current->date = date;
  current->next = NULL;
  current->visited = 0;
  return;
}
Node *getNode(Node *nodes[], int nodePointer){
  int i = 0;
  return nodes[nodePointer];
 }
Node *findNode(Node *nodes[], int nodeName, int nodeCount){
  int i = 0;
  for (i = 0; i < nodeCount; i++) {
    if(nodes[i]->name == nodeName)
      return nodes[i];
    }
  printf("Node %d nenalezen\n", nodeName);
  return NULL;
}
void freeNode(Node *n){
	if(n->next == NULL) free(n);
	else {
		n=n->next;
		freeNode(n);
	}
}
