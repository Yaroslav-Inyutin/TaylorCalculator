.PHONY: all clean 
CC = g++
CFLAGS = -std=c++20 -c
all: taylorCalculator

clean: 
	rm -f *.o
	rm -f taylorCalculator

taylorCalculator: main.o taylor_function.o function_factory.o calculator.o sin.o cos.o ln.o pow.o exp.o sh.o ch.o 
	$(CC) -std=c++20 main.o taylor_function.o function_factory.o calculator.o sin.o cos.o ln.o pow.o exp.o sh.o ch.o -o taylorCalculator

main.o: main.cpp function_factory.hpp calculator.hpp
	$(CC) $(CFLAGS) main.cpp -o main.o

taylor_function.o: taylor_function.cpp taylor_function.hpp
	$(CC) $(CFLAGS) taylor_function.cpp -o taylor_function.o

function_factory.o: function_factory.cpp function_factory.hpp sin.hpp cos.hpp ln.hpp pow.hpp exp.hpp sh.hpp ch.hpp
	$(CC) $(CFLAGS) function_factory.cpp -o function_factory.o

calculator.o: calculator.cpp calculator.hpp taylor_function.hpp
	$(CC) $(CFLAGS) calculator.cpp -o calculator.o

sin.o: sin.cpp sin.hpp taylor_function.hpp
	$(CC) $(CFLAGS) sin.cpp -o sin.o

cos.o: cos.cpp cos.hpp taylor_function.hpp
	$(CC) $(CFLAGS) cos.cpp -o cos.o

ln.o: ln.cpp ln.hpp taylor_function.hpp
	$(CC) $(CFLAGS) ln.cpp -o ln.o

pow.o: pow.cpp pow.hpp taylor_function.hpp
	$(CC) $(CFLAGS) pow.cpp -o pow.o

exp.o: exp.cpp exp.hpp taylor_function.hpp
	$(CC) $(CFLAGS) exp.cpp -o exp.o

sh.o: sh.cpp sh.hpp taylor_function.hpp
	$(CC) $(CFLAGS) sh.cpp -o sh.o

ch.o: ch.cpp ch.hpp taylor_function.hpp
	$(CC) $(CFLAGS) ch.cpp -o ch.o