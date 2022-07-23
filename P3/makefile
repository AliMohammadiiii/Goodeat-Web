CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: src/handlers.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp src/Person.hpp src/Filter.hpp src/Shelves.hpp src/Recipes.hpp src/general.hpp src/handlers.cpp
	$(CC) $(CF) -c src/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: src/my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c src/my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: src/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp src/Person.hpp src/Shelves.hpp src/Recipes.hpp src/general.hpp src/Filter.hpp src/handlers.hpp 
	$(CC) $(CF) -c src/main.cpp -o $(BUILD_DIR)/main.o


$(BUILD_DIR)/Recipes.o: src/Recipes.hpp src/general.hpp src/Recipes.cpp
	$(CC) $(CF) -c src/Recipes.cpp -o $(BUILD_DIR)/Recipes.o


$(BUILD_DIR)/Shelves.o: src/Shelves.hpp src/Recipes.hpp src/general.hpp src/Shelves.cpp
	$(CC) $(CF) -c src/Shelves.cpp -o $(BUILD_DIR)/Shelves.o


$(BUILD_DIR)/Person.o: src/Person.hpp src/Shelves.hpp src/Recipes.hpp src/general.hpp src/Person.cpp
	$(CC) $(CF) -c src/Person.cpp -o $(BUILD_DIR)/Person.o

$(BUILD_DIR)/Filter.o: src/Filter.hpp src/Recipes.hpp src/general.hpp src/Filter.cpp
	$(CC) $(CF) -c src/Filter.cpp -o $(BUILD_DIR)/Filter.o

myserver.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/Recipes.o $(BUILD_DIR)/Shelves.o $(BUILD_DIR)/Person.o $(BUILD_DIR)/Filter.o 
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/Recipes.o $(BUILD_DIR)/Shelves.o $(BUILD_DIR)/Person.o $(BUILD_DIR)/Filter.o -o myserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
