typedef struct{
	int name;
	struct Node *next;
}node;

node *create_node(int name);
void print_node(node *n);
void add_node(node *n, int name);
