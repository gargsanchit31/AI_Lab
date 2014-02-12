CC = g++ -std=c++0x -g 
DEPS = graph.h
OBJ = main.o 

# $@ : lhs
# $< : first item in rhs
# $< : complete rhs

%.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< 

main.out: $(OBJ)
	$(CC) -o $@ $(OBJ)

.PHONY: clean
clean:
	rm -rf a.out main.out 
	rm -rf *.o

