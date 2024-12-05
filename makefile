CC = gcc                
CFLAGS = -Wall -g       
OBJ = main.o pizza.o ingrediente.o  
EXEC = pizzaria.exe      

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c pizza.h ingrediente.h
	$(CC) $(CFLAGS) -c main.c

pizza.o: pizza.c pizza.h ingrediente.h
	$(CC) $(CFLAGS) -c pizza.c

ingrediente.o: ingrediente.c ingrediente.h
	$(CC) $(CFLAGS) -c ingrediente.c


clean:
	rm -f $(OBJ) $(EXEC)


run: $(EXEC)
	./$(EXEC)