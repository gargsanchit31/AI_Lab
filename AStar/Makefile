CC = g++ -std=c++0x -g 
DEPS = graph.h PriorityQueue.h
OBJ = main8sq.o 

# $@ : lhs
# $< : first item in rhs
# $< : complete rhs

%.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< 

main8.out: $(OBJ)
	$(CC) -o $@ $(OBJ)

.PHONY: clean
clean:
	rm -rf *.out 
	rm -rf *.o

