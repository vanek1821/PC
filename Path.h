typedef struct{
	int id;
	short pathSize;
	short pointer;
	int *nodePath;
	int metric;
}Path;

Path *createPath(int id);
void printPath(Path *p);
void addToPath(Path *p, Node *node);
void removeFromPath(Path *p);
void countMetric(Path *p);
