include ../AdditionalMakeDefns
include ../MakeDefns
SHARED=
INCPATH=-I../include $(patsubst %, -I../contrib/%/include, $(DEPENDENCIES)) $(ADINCPATH)
LIBPATH=-L../obj  $(patsubst %, -L../contrib/%/obj, $(DEPENDENCIES)) $(ADDLIBPATH)
LIBS=-lindri $(patsubst %, -l%, $(DEPENDENCIES)) $(ADDLIBS)
APP=SimpleQueryRunner

all:
	#swig -php -c++ $(APP).i
	#$(CXX) `php-config --includes` -fpic -c $(CXXFLAGS) $(APP)_wrap.cpp -o $(APP)_wrap.o $(LIBPATH) $(LIBS)
	#$(CXX) `php-config --includes` -fpic -c $(CXXFLAGS) $(APP).cpp -o $(APP).o $(LIBPATH) $(LIBS) 
	#$(CXX) -shared $(CXXFLAGS) $(APP).o $(APP)_wrap.o -o libsimplequery.so $(LIBPATH) $(LIBS)
	$(CXX) $(CXXFLAGS) run.cpp SimpleQueryRunner.cpp -o runSimpleQuery $(LIBPATH) $(LIBS) $(CPPLDFLAGS)
	
test:
	#$(CXX) $(CXXFLAGS) run.cpp SimpleQueryRunner.cpp -o runSimpleQuery $(LIBPATH) $(LIBS) 

install:
	$(INSTALL_PROGRAM) $(APP) $(bindir)

clean:
	rm -f test *.o *.so runSimpleQuery



#all:
	#swig -php -c++ Humor.i
	#g++ `php-config --includes` -fpic -c Humor_wrap.cpp -o Humor_wrap.o
	#g++ `php-config --includes` -fpic -c SimpleQueryRunner.cpp -o SimpleQueryRunner.o -I../indri/include/ -I../indri/contrib/lemur/include/
	# g++ QueryRunner.cpp -o QuerRunner.o -I../indri/include
	#g++ -shared Humor_wrap.o  Humor.o -o $(TARGET) -lhumor -lstem2005 -L../testingData/lib
	#g++ -c main.cpp
	#g++ main.o Humor.o -o test -lhumor -lstem2005 -L../testingData/lib
	#chmod +x ./test
