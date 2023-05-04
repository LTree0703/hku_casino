FLAG=-pedantic-errors -std=c++11
OBJECTS=bank.o func.o main.o menu.o roulette.o slotmachine.o texpoker.o


casino: $(OBJECTS)
	g++ $(FLAG) $^ -o casino 



bank.o: bank.cpp bank.hpp
	g++ $(FLAG) -c $< 


func.o: func.cpp func.h
	g++ $(FLAG) -c $< 

texpoker.o: texpoker.cpp texpoker.h
	g++ $(FLAG) -c $< 

slotmachine.o: slotmachine.cpp
	g++ $(FLAG) -c $<

roulette.o: roulette.cpp
	g++ $(FLAG) -c $<

main.o: main.cpp
	g++ $(FLAG) -c $<

clean: 
	rm -rf *.o

.PHONY: clean
