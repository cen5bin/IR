SRC_DIR=./src
OBJ_DIR=./obj
BIN_DIR=./bin
DEBUG_DIR=$(BIN_DIR)/debug
RELEASE_DIR=$(BIN_DIR)/release
INCLUDE_DIR=./include
LIB_DIR=./lib

EXTENSION=.c .cpp .cc 

SOURCE_FILES=$(foreach ex, ${EXTENSION}, $(wildcard ${SRC_DIR}/*${ex}))
OBJECTS=$(foreach ex, ${EXTENSION}, $(patsubst %${ex}, ${OBJ_DIR}/%.o, $(filter %${ex}, $(notdir ${SOURCE_FILES}))))

$(shell mkdir -p ${OBJ_DIR})
$(shell mkdir -p ${DEBUG_DIR})
$(shell mkdir -p ${RELEASE_DIR})

#=============================================================




CC=g++ 
CFLAGS=-g -Wall -O2 -I$(INCLUDE_DIR)
CPPFLAGS=-g -Wall -O2 -I$(INCLUDE_DIR) -include IRLog.h 
LDFLAG=-L$(LIB_DIR)

TARGET=work.o
TARGET_LIB=inverted_index.a

#=============================================================

edit : $(OBJECTS)
	@echo sources: $(SOURCE_FILES)
	$(CC) $(CPPFLAGS) $(OBJECTS) -o  $(TARGET) $(LDFLAG)
	ar rvl $(TARGET_LIB) $(OBJECTS)
	cp $(TARGET_LIB) $(RELEASE_DIR)/

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@ $(LDFLAG)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(CC) -c $(CPPFLAGS) $< -o $@ $(LDFLAG)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@ $(LDFLAG)

.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(RELEASE_DIR)/* $(DEBUG_DIR)/*  *.a *.out *.o
