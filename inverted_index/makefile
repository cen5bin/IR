SRC_DIR=./src
OBJ_DIR=./obj
BIN_DIR=./bin
DEBUG_DIR=$(BIN_DIR)/debug
RELEASE_DIR=$(BIN_DIR)/release
INCLUDE_DIRS=./include /usr/lib/jvm/java-7-openjdk-i386/include  /usr/lib/jvm/java-7-openjdk-i386/include/linux
LIB_DIR=./lib

EXTENSION=.c .cpp .cc 

SOURCE_FILES=$(foreach ex, ${EXTENSION}, $(wildcard ${SRC_DIR}/*${ex}))
OBJECTS=$(foreach ex, ${EXTENSION}, $(patsubst %${ex}, ${OBJ_DIR}/%.o, $(filter %${ex}, $(notdir ${SOURCE_FILES}))))
OBJS=$(foreach obj, ${OBJECTS}, $(notdir ${obj}))
LIBS=$(patsubst lib%.a, %, $(notdir $(wildcard ${LIB_DIR}/*.a)))

$(shell mkdir -p ${OBJ_DIR})
$(shell mkdir -p ${DEBUG_DIR})
$(shell mkdir -p ${RELEASE_DIR})

#=============================================================


PUBLIC_HEADERS= IRLog.h 

CC=g++ 
INCLUDE_FLAG=$(foreach in, ${INCLUDE_DIRS}, -I${in})
CFLAGS=-g -Wall -O2 $(INCLUDE_FLAG)
CPPFLAGS=-g -Wall -O2 $(INCLUDE_FLAG) $(foreach h, ${PUBLIC_HEADERS}, -include ${h})
LDFLAG= $(foreach lib, ${LIBS}, -l${lib}) -L$(LIB_DIR)

TARGET=work.o
TARGET_LIB=inverted_index.a
TARGET_SO=libIR.so

#=============================================================

all : main
main : $(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) -o  $(TARGET) $(LDFLAG)
	$(CC) $(CPPFLAGS) -shared -fpic $(OBJECTS) -o $(TARGET_SO) $(LDFLAG)
	ar rvl $(TARGET_LIB) $(OBJECTS)
	cp $(TARGET_LIB) $(RELEASE_DIR)/
	mv $(TARGET_SO) $(RELEASE_DIR)/


$(OBJ_DIR)/%.d : $(SRC_DIR)/%.cpp
	rm -f $@
	echo -n $(OBJ_DIR)/ > $@; \
	$(CC) -MM $(CPPFLAGS) $< >> $@; \
	echo "\t" $(CC) -c $(CPPFLAGS) $< -o $(@:.d=.o) $(LDFLAG) >> $@

include $(OBJECTS:.o=.d)

#$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
#	$(CC) -c $(CPPFLAGS) $< -o $@ $(LDFLAG)

#$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
#	$(CC) -c $(CPPFLAGS) $< -o $@ $(LDFLAG)

#$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
#	$(CC) -c $(CFLAGS) $< -o $@ $(LDFLAG)

.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(RELEASE_DIR)/* $(DEBUG_DIR)/*  *.a *.out *.o $(OBJ_DIR)/*.d

