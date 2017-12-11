typedef struct{
	int name;
	struct node *next;
	int visited;
}node;

node *create_node(int name);
void print_node(node *n);
void add_node(node *n, int name);
void print_node_name(node *n);
node *getNode(node *nodes[], int name, int nodeCount);
