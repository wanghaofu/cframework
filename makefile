#DIR_INC = ./include
DIR_INC = ./headers
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin

SRC = $(wildcard ${DIR_SRC}/*.cpp)
OBJ = $(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${SRC}))
#$(warning $(SRC))
#$(warning $(OBJ))

SERVER_TARGET = server_main
CLIENT_TARGET = client_main

SERVER_OBJ=$(filter-out ./obj/client_main.o,$(OBJ))
CLIENT_OBJ=$(filter-out ./obj/server_main.o,$(OBJ))

$(warning $(SERVER_OBJ))
$(warning $(CLIENT_OBJ))

BIN_SERVER_TARGET = ${DIR_BIN}/${SERVER_TARGET}
BIN_CLIENT_TARGET = ${DIR_BIN}/${CLIENT_TARGET}

CC = g++ -lpthread -lcrypto
CFLAGS = -g -Wall -I${DIR_INC}

ALL : $(BIN_SERVER_TARGET) $(BIN_CLIENT_TARGET)

${BIN_SERVER_TARGET}:${SERVER_OBJ}
	$(CC) ${SERVER_OBJ} -o $@
${BIN_CLIENT_TARGET}:${CLIENT_OBJ}
	$(CC) $(CLIENT_OBJ) -o $@

${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean:
	find ${DIR_OBJ} -name *.o -exec rm -rf {} \;
