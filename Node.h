typedef struct nod Node;

struct nod{
	int name;
	Node *next;
	int nodePointer;
	int index;
	int visited;
	DateTime *date;
};

Node *createNode(int name);
void printNode(Node *n);
void addNode(Node *head, Node *nodes[], int name, DateTime *date);
int findNodePointer(Node *nodes[], int nodeName);
void printNodeName(Node *n);
Node *findNode(Node *nodes[], int nodeName, int node_count);
Node *getNode(Node *nodes[], int nodePointer);
void freeNode(Node* n);
