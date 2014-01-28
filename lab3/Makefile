CC = g++ -std=c++0x
DEPS = components.h utils.h layer.h neural_network.h
OBJ = main.o components.o utils.o layer.o neural_network.o
OBJ2 = main.o components.o utils.o layer.o neural_network.o

# $@ : lhs
# $< : first item in rhs
# $< : complete rhs

%.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< 

main.out: $(OBJ)
	$(CC) -o $@ $(OBJ)
net.out: $(OBJ)
	$(CC) -o $@ $(OBJ2)

.PHONY: clean
clean:
	rm -rf a.out
	rm -rf *.o

