cs219_program: main.o helpers.o
	g++ -o cs219_program main.o helpers.o
main.o: main.cpp helpers.h register.h
	g++ -c main.cpp -g
helpers.o: helpers.h helpers.cpp register.h
	g++ -c helpers.cpp -g
clean:
	rm *.o cs219_program