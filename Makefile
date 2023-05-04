FLAG=-std=c++11

casino: main.cpp bank.o func.o menu.o roulette.o slotmachine.o texpoker.o
	g++ $(FLAG) $^ -o $@

bank.o: bank.cpp bank.h
	g++ $(FLAG) -c $< -o $@

func.o: func.cpp func.h
	g++ $(FLAG) -c $< -o $@

texpoker.o: texpoker.cpp texpoker.h
	g++ $(FLAG) -c $< -o $@

slotmachine.o: slotmachine.cpp slotmachine.h
	g++ $(FLAG) -c $< -o $@

roulette.o: roulette.cpp roulette.h
	g++ $(FLAG) -c $< -o $@

clean: 
	rm -rf *.o

.PHONY: clean
