#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "DateTime.h"
#include "Node.h"

/**
Creates node
params: 
int name - name of node
returns: 
Node *node
*/
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

/**
prints information about node
params: Node *n - pointer to node
*/
void printNode(Node *n){
	  Node * tmp = n;
	  DateTime *tmpDate = tmp->date;
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
/**
prints node name
params: Node *n - pointer to node
*/
void printNodeName(Node *n){
  Node * tmp = n;
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
/**
Finds index of node in array of nodes
params: 
Node *node[] - array of nodes
int nodeName - name of node
returns:
index of node in array 
*/
int findNodePointer(Node *nodes[], int nodeName){
  int i = 0;
  while(nodes[i]->name != nodeName){
    i++;
  }
  return i;

}
/**
Adds node to adjacency list of node
params:
Node *head - head Node to which is new node added
int name - name of added node
DateTime *date - pointer to a date of edge between head node and added node
*/
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
/**
Gets node on index in array
params:
Node *nodes[] - array of nodes
int nodePointer - index of node in array
returns: 
Node *node - found node
*/
Node *getNode(Node *nodes[], int nodePointer){
  int i = 0;
  return nodes[nodePointer];
 }
/**
Finds node in array according to its name
params:
Node *nodes[] - array of nodes
int nodeName - name of node 
int nodeCount - number of nodes in array
returns:
Node *node
*/
Node *findNode(Node *nodes[], int nodeName, int nodeCount){
  int i = 0;
  for (i = 0; i < nodeCount; i++) {
    if(nodes[i]->name == nodeName)
      return nodes[i];
    }
  printf("Node %d nenalezen\n", nodeName);
  return NULL;
}
/**
Frees mallocked space for node 
params: 
Node *n - Node to be freed

*/
void freeNode(Node *n){
   Node * tmp;
   while (n != NULL){
       tmp = n;
       n = n->next;
       free(tmp->date);
       free(tmp);
    }

}

