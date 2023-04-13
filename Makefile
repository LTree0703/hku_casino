casino: main.cpp func.o
	g++ $^ -o casino

func.o: func.cpp func.h
	g++ -c $< -o $@

clean: 
	rm -rf *.o

.PHONY: clean