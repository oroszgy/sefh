CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		HunSyn_wrap.o

LIBS =

TARGET =	phphumor.so


all:
	swig -php -c++ HunSyn.i
	gcc `php-config --includes` -fpic -c HunSyn_wrap.cpp -o $(OBJS)
	gcc -shared HunSyn_wrap.o -o $(TARGET)


clean:
	rm -f $(OBJS) $(TARGET)
