CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		Humor_wrap.o Humor.o

SRCS = 		Humor_wrap.cpp Humor.cpp

LIBS =

TARGET =	phphumor.so


all:
	swig -php -c++ Humor.i
	g++ `php-config --includes` -fpic -c Humor_wrap.cpp -o Humor_wrap.o
	g++ `php-config --includes` -fpic -c Humor.cpp -o Humor.o
	# g++ QueryRunner.cpp -o QuerRunner.o -I../indri/include
	g++ -shared Humor_wrap.o  Humor.o -o $(TARGET) -lhumor -lstem2005 -L../testingData/lib
	g++ -c main.cpp
	g++ main.o Humor.o -o test -lhumor -lstem2005 -L../testingData/lib
	chmod +x ./test


clean:
	rm -f $(OBJS) $(TARGET) *.o *.so
