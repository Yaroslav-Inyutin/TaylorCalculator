.PHONY: all clean install uninstall
CC = g++
CFLAGS = -std=c++20 -c

QTFLAGS = `pkg-config --cflags Qt6Widgets`
QTLIBS  = `pkg-config --libs Qt6Widgets`

all: taylorCalculator guiTaylorCalculator

clean: 
	rm -f *.o
	rm -f taylorCalculator
	rm -f guiTaylorCalculator
	rm -f moc_mainwindow.cpp

install:
	install ./taylorCalculator /usr/local/bin

uninstall:
	rm /usr/local/bin/taylorCalculator

# GUI ВЕРСИЯ

guiTaylorCalculator: gui_main.o mainwindow.o moc_mainwindow.o taylor_controller.o taylor_function.o function_factory.o calculator.o sin.o cos.o ln.o pow.o exp.o sh.o ch.o trigonometric_function.o
	$(CC) gui_main.o mainwindow.o moc_mainwindow.o taylor_controller.o taylor_function.o function_factory.o calculator.o sin.o cos.o ln.o pow.o exp.o sh.o ch.o trigonometric_function.o -o guiTaylorCalculator $(QTLIBS)

gui_main.o: gui_main.cpp gui/mainwindow.hpp
	$(CC) $(CFLAGS) $(QTFLAGS) gui_main.cpp -o gui_main.o

mainwindow.o: gui/mainwindow.cpp gui/mainwindow.hpp taylor_controller.hpp
	$(CC) $(CFLAGS) $(QTFLAGS) gui/mainwindow.cpp -o mainwindow.o

moc_mainwindow.o: moc_mainwindow.cpp
	$(CC) $(CFLAGS) $(QTFLAGS) moc_mainwindow.cpp -o moc_mainwindow.o

moc_mainwindow.cpp: gui/mainwindow.hpp
	/usr/lib/qt6/libexec/moc gui/mainwindow.hpp -o moc_mainwindow.cpp

# КОНЕЦ GUI

taylorCalculator: main.o taylor_controller.o taylor_function.o function_factory.o calculator.o sin.o cos.o ln.o pow.o exp.o sh.o ch.o trigonometric_function.o sum_function.o
	$(CC) -std=c++20 main.o taylor_controller.o taylor_function.o function_factory.o calculator.o sin.o cos.o ln.o pow.o exp.o sh.o ch.o trigonometric_function.o sum_function.o -o taylorCalculator

main.o: main.cpp function_factory.hpp calculator.hpp taylor_controller.hpp
	$(CC) $(CFLAGS) main.cpp -o main.o

taylor_controller.o: taylor_controller.cpp taylor_controller.hpp function_factory.hpp calculator.hpp
	$(CC) $(CFLAGS) taylor_controller.cpp -o taylor_controller.o

taylor_function.o: taylor_function.cpp taylor_function.hpp
	$(CC) $(CFLAGS) taylor_function.cpp -o taylor_function.o

trigonometric_function.o: trigonometric_function.cpp trigonometric_function.hpp taylor_function.hpp
	$(CC) $(CFLAGS) trigonometric_function.cpp -o trigonometric_function.o

function_factory.o: function_factory.cpp function_factory.hpp sin.hpp cos.hpp ln.hpp pow.hpp exp.hpp sh.hpp ch.hpp
	$(CC) $(CFLAGS) function_factory.cpp -o function_factory.o

calculator.o: calculator.cpp calculator.hpp taylor_function.hpp
	$(CC) $(CFLAGS) calculator.cpp -o calculator.o

sin.o: sin.cpp sin.hpp trigonometric_function.hpp
	$(CC) $(CFLAGS) sin.cpp -o sin.o

cos.o: cos.cpp cos.hpp trigonometric_function.hpp
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
  
sum_function.o: sum_function.cpp sum_function.hpp
	$(CC) $(CFLAGS) sum_function.cpp -o sum_function.o