CC = g++ -std=c++11
EXE_FILE = goodeats.out

&(EXE_FILE) : main.o Recipes.o Shelves.o Person.o Filter.o Interface.o Offers.o Order.o Ingeradiant.o
	$(CC) main.o Recipes.o Shelves.o Person.o Filter.o Interface.o Offers.o Order.o Ingeradiant.o -o $(EXE_FILE)

main.o: Interface.hpp Person.hpp Shelves.hpp Recipes.hpp general.hpp Filter.hpp main.cpp
	$(CC) -c main.cpp -o main.o


Recipes.o: Recipes.hpp general.hpp Recipes.cpp
	$(CC) -c Recipes.cpp -o Recipes.o


Shelves.o: Shelves.hpp Recipes.hpp general.hpp Shelves.cpp
	$(CC) -c Shelves.cpp -o Shelves.o


Person.o: Person.hpp Shelves.hpp Recipes.hpp general.hpp Order.hpp Offers.hpp Person.cpp
	$(CC) -c Person.cpp -o Person.o

Filter.o: Filter.hpp Recipes.hpp general.hpp Filter.cpp
	$(CC) -c Filter.cpp -o Filter.o

Interface.o: Interface.hpp Person.hpp Shelves.hpp Recipes.hpp general.hpp Filter.hpp Order.hpp Offers.hpp Ingeradiant.hpp Interface.cpp
	$(CC) -c Interface.cpp -o Interface.o

Offers.o: Offers.hpp general.hpp Offers.cpp
	$(CC) -c Offers.cpp -o Offers.o

Order.o: Order.hpp Offers.hpp general.hpp Order.cpp
	$(CC) -c Order.cpp -o Order.o

Ingeradiant.o: Ingeradiant.hpp general.hpp Ingeradiant.cpp
	$(CC) -c Ingeradiant.cpp -o Ingeradiant.o

clean:
	rm *.o $(EXE_FILE)
