CC = g++ -std=c++11
EXE_FILE = goodeats.out

&(EXE_FILE) : main.o Recipes.o Shelves.o Person.o Filter.o Interface.o
	$(CC) main.o Recipes.o Shelves.o Person.o Filter.o Interface.o -o $(EXE_FILE)

main.o: Interface.hpp Person.hpp Shelves.hpp Recipes.hpp general.hpp Filter.hpp main.cpp
	$(CC) -c main.cpp -o main.o


Recipes.o: Recipes.hpp general.hpp Recipes.cpp
	$(CC) -c Recipes.cpp -o Recipes.o


Shelves.o: Shelves.hpp Recipes.hpp general.hpp Shelves.cpp
	$(CC) -c Shelves.cpp -o Shelves.o


Person.o: Person.hpp Shelves.hpp Recipes.hpp general.hpp Person.cpp
	$(CC) -c Person.cpp -o Person.o

Filter.o: Filter.hpp Recipes.hpp general.hpp Filter.cpp
	$(CC) -c Filter.cpp -o Filter.o

Interface.o: Interface.hpp Person.hpp Shelves.hpp Recipes.hpp general.hpp Filter.hpp Interface.cpp
	$(CC) -c Interface.cpp -o Interface.o


clean:
	rm *.o $(EXE_FILE)
