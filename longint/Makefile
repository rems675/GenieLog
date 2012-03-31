C = g++
INC = include
OBJ = obj
SRC = src
LIB = lib
HEADERS = $(INC)/long.h $(INC)/general.h
OBJECTS = $(OBJ)/general.o $(OBJ)/add.o $(OBJ)/sub.o $(OBJ)/mul.o $(OBJ)/div.o \
          $(OBJ)/LongInt.o $(OBJ)/operators.o $(OBJ)/compound.o $(OBJ)/ios.o

all : $(LIB)/liblongint.a

$(LIB)/liblongint.a : $(OBJECTS) $(HEADERS)
	ar r $(LIB)/liblongint.a $(OBJECTS)

$(OBJ)/general.o : $(SRC)/general.cpp $(INC)/general.h
	$(C) -I $(INC) -c $(SRC)/general.cpp -o $(OBJ)/general.o

##  ops  ##

DIR = operations

$(OBJ)/add.o : $(SRC)/$(DIR)/add.cpp  $(HEADERS)
	$(C) -I $(INC) -c $(SRC)/$(DIR)/add.cpp -o $(OBJ)/add.o

$(OBJ)/sub.o : $(SRC)/$(DIR)/sub.cpp  $(HEADERS)
	$(C) -I $(INC) -c $(SRC)/$(DIR)/sub.cpp -o $(OBJ)/sub.o

$(OBJ)/mul.o : $(SRC)/$(DIR)/mul.cpp  $(HEADERS)
	$(C) -I $(INC) -c $(SRC)/$(DIR)/mul.cpp -o $(OBJ)/mul.o

$(OBJ)/div.o : $(SRC)/$(DIR)/div.cpp  $(HEADERS)
	$(C) -I $(INC) -c $(SRC)/$(DIR)/div.cpp -o $(OBJ)/div.o

## /ops  ##

$(OBJ)/LongInt.o : $(SRC)/LongInt.cpp  $(HEADERS)
	$(C) -I $(INC) -c $(SRC)/LongInt.cpp -o $(OBJ)/LongInt.o

$(OBJ)/operators.o : $(SRC)/operators.cpp  $(HEADERS)
	$(C) -I $(INC) -c $(SRC)/operators.cpp -o $(OBJ)/operators.o

$(OBJ)/compound.o : $(SRC)/compound.cpp  $(HEADERS)
	$(C) -I $(INC) -c $(SRC)/compound.cpp -o $(OBJ)/compound.o

$(OBJ)/ios.o : $(SRC)/ios.cpp  $(HEADERS)
	$(C) -I $(INC) -c $(SRC)/ios.cpp -o $(OBJ)/ios.o




clean :
	rm -f $(OBJ)/*.o $(LIB)/*.a *~


