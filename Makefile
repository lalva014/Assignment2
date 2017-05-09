##work in progress
##these are variables 
CC=g++
## not needed
CC__= -std=c++11
OBJS = main.o And.o Command.o Or.o Semi.o 
##errors flag
CC_FLAGS=-Wall -Werror -ansi -pedantic
##this will be the name of the executable file
EXEC=test.out
##probably want to make all files have the same suffix
SOURCES=$(wildcard *.cpp)


# OBJECTS=$(SOURCES:.cpp=.o)

# $(EXEC): $(OBJECTS)
# 	$(CC) $(OBJECTS) -o $(EXEC)

# %.o: %.cpp
# 	$(CC) -c $(CC_FLAGS) $< -o $@

# clean:
# 	rm -f $(EXEC) $(OBJECTS)
	
# tar: 
# 	tar -czvf .tar.gz 	
	
	
	

	
rshell: $(OBJS)
	$(CC) $(CC_FLAGS) $(OBJS) -o rshell

all: $(OBJS)
	$(CC) $(CC_FLAGS) $(OBJS) -o all
main.o: main.cpp And.cpp Command.cpp Or.cpp Semi.cpp Base.h
	$(CC) $(CC_FLAGS) -c main.cpp

And.o: And.h And.cpp Base.h
	$(CC) $(CC_FLAGS) -c And.cpp
	
Command.o: Command.cpp Command.h Base.h
	$(CC) $(CC_FLAGS) -c Command.cpp
	
Or.o: Or.cpp Or.h Base.h
	$(CC) $(CC_FLAGS) -c Or.cpp
	
Semi.o: Semi.cpp Semi.h Base.h
	$(CC) $(CC_FLAGS) -c Semi.cpp
	
# $(OBJS)/sfml-app: $(OBJS)
# 	$(CC) -o $@ $(OBJ) 
 
clean:
	rm -f *.o *~ all *~ rshell
	


# all: $(EXEDIR)/sfml-app

# $(EXEDIR)/sfml-app: $(OBJ)
#         $(CXX) -o $@ $(OBJ) $(LIBS)
	