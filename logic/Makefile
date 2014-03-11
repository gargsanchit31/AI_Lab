CC = g++ -std=c++0x -g 
DEPS = formula.h  utils.h decider.h
OBJ = main.o formula.o utils.o decider.o
# $@ : lhs
# $< : first item in rhs
# $< : complete rhs

logic.out: $(OBJ)
	$(CC) -o $@ $(OBJ)

%.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< 



.PHONY: clean
clean:
	rm -rf *.out 
	rm -rf *.o

