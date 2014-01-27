CC = g++
DEPS = components.h utils.h
OBJ = main.o components.o

# $@ : lhs
# $< : first item in rhs
# $< : complete rhs

%.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< 

a.out: $(OBJ)
	$(CC) -o $@ main.cpp components.cpp

.PHONY: clean
clean:
	rm -rf a.out
	rm -rf *.o

