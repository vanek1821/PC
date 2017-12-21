CC = gcc
BIN = dfs.exe
OBJ = DateTime.o Node.o Path.o main.o

all: $(BIN) clean

$(BIN): $(OBJ)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $< -o $@
  
clean:	
	rm -f *.o
