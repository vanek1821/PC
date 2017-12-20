typedef struct{
	int name;
	struct Node *next;
	int nodePointer;
	int index;
	int visited;
	struct DateTime *date;
	short day, month;
	int year;
}Node;

Node *createNode(int name);
void printNode(Node *n, FILE* outf);
void addNode(Node *head, Node *nodes[], int name, DateTime *date);
int findNodePointer(Node *nodes[], int nodeName);
void addEdge(Node *n, int name);
void printNodeName(Node *n);
Node *findNode(Node *nodes[], int nodeName, int node_count);
Node *getNode(Node *nodes[], int nodePointer);
