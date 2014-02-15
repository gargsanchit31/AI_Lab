CC = g++ -std=c++0x -g 
DEPS = graph.h PriorityQueue.h utils.h
OBJ_8SQ = main8sq.o  utils.o
OBJ_MNC = main_mnc.o  utils.o

# $@ : lhs
# $< : first item in rhs
# $< : complete rhs

%.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< 

main8.out: $(OBJ_8SQ)
	$(CC) -o $@ $(OBJ_8SQ)

main_mnc.out: $(OBJ_MNC)
	$(CC) -o $@ $(OBJ_MNC)

.PHONY: clean
clean:
	rm -rf *.out 
	rm -rf *.o

