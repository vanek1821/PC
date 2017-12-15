typedef struct{
	int name;
	struct Node *next;
	int visited;
}node;

node *createNode(int name);
void printNode(node *n);
void addNode(node *head, int name);
void addEdge(node *n, int name);
void printNodeName(node *n);
node *getNode(node *nodes[], int name, int nodeCount);
