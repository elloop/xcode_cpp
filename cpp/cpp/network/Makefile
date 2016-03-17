TARGET = start_client

OBJS = simple_socket_client.o \
	   start_client.o

COMPILER = clang++

REBUILDABLE = $(TARGET) $(OBJS)

CPP_FLAGS = -std=c++11

INCLUDE_FLAG = -I../ \
			   -I../include

all: $(OBJS)
	$(COMPILER) -o $(TARGET) $^

%.o: %.cpp
	$(COMPILER) $(CPP_FLAGS) $(INCLUDE_FLAG) -g -o $@ -c $<


.PHONY: clean
clean:
	-rm $(TARGET) *.o

