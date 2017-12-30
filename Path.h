typedef struct pat Path;

struct pat{
	int id;
	short pathSize;
	short pointer;
	Node **nodePath;
	int metric;
};

Path *createPath(int id);
void printPath(Path *p);
void addToPath(Path *p, Node *node);
void removeFromPath(Path *p);
void countMetric(Path *p);
