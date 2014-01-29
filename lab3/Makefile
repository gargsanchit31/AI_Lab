CC = g++ -std=c++0x
DEPS = components.h utils.h layer.h neural_network.h
OBJ = main.o components.o utils.o layer.o neural_network.o
OBJ2 = main_network.o components.o utils.o layer.o neural_network.o

# $@ : lhs
# $< : first item in rhs
# $< : complete rhs

%.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< 

main.out: $(OBJ)
	$(CC) -o $@ $(OBJ)
net.out: $(OBJ2)
	$(CC) -o $@ $(OBJ2)

.PHONY: clean
clean:
	rm -rf a.out main.out net.out
	rm -rf *.o

