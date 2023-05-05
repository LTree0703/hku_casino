FLAG=-std=c++11

casino: main.o func.o roulette.o slotmachine.o texpoker.o
	g++ $(FLAG) $^ -o $@

main.o: main2.cpp roulette.h slotmachine.h texpoker.h
	g++ $(FLAG) -c $< -o $@

bank.o: bank.cpp bank.h
	g++ $(FLAG) -c $<

func.o: func.cpp func.h
	g++ $(FLAG) -c $< 

texpoker.o: texpoker.cpp texpoker.h func.h
	g++ $(FLAG) -c $< 

slotmachine.o: slotmachine.cpp slotmachine.h func.h
	g++ $(FLAG) -c $< 

roulette.o: roulette.cpp roulette.h func.h
	g++ $(FLAG) -c $< 

clean: 
	rm -rf *.o casino

.PHONY: clean
