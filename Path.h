typedef struct{
	int id;
	int pathSize;
	int pointer;
	int *nodePath;
}Path;

Path *createPath(int id);
void printPath(Path *p, FILE *outf);
void addToPath(Path *p, int nodeName);
void removeFromPath(Path *p);
