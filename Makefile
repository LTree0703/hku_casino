FLAG=-pedantic-errors -std=c++11

casino: main.cpp func.o texpoker.o
	g++ $(FLAG) $^ -o casino

func.o: func.cpp func.h
	g++ $(FLAG) -c $< -o $@

texpoker.o: texpoker.cpp func.h
	g++ $(FLAG) -c $< -o $@

clean: 
	rm -rf *.o

.PHONY: clean