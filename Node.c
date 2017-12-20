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
	  /*
	  tmp->day = 0;
	  tmp->month = 0;
	  tmp->year = 0;
	   */
	  return(tmp);
}

void printNode(Node *n, FILE* outf){
	  Node * tmp = malloc(sizeof(Node));
	  DateTime *tmpDate = malloc(sizeof(DateTime));
	  tmp = n;
	  //tmpDate = tmp->date;
	  if(!tmp){
		printf("NULL");
		return;
	  }
	  else{
		printf("%d on index %d", tmp->name, tmp->index);
		fprintf(outf, "%d", tmp->name);
		tmp = (Node*)tmp->next;
		tmpDate = (DateTime*)tmp->date;
		while((tmp!=NULL)){
		  printf(" -> %d; %d-%d-%d pointTo: %d||", tmp->name, tmpDate->year, tmpDate->month, tmpDate->day, tmp->nodePointer);
		  fflush(stdout);
		  fprintf(outf, "-> %d ", tmp->name);
		  tmp = tmp->next;
		  if(tmp!=NULL) tmpDate = tmp->date;
		}
		printf("\n");
		fprintf(outf, "\n");
		//printf(" || visited: %d\n", n->visited);
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
  /*for (i = 0; i < NodeCount; i++) {
    if(Nodes[i]->name == name)
      return Nodes[i];
  }*/
  return nodes[nodePointer];
  /*printf("Node %d nenalezen\n", name);
  return NULL;*/
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
