include ../AdditionalMakeDefns
include ../MakeDefns
SHARED=
INCPATH=-I../include $(patsubst %, -I../contrib/%/include, $(DEPENDENCIES)) $(ADDINCPATH)
LIBPATH=-L../obj  $(patsubst %, -L../contrib/%/obj, $(DEPENDENCIES)) $(ADDLIBPATH)
LIBS=-lindri $(patsubst %, -l%, $(DEPENDENCIES)) $(ADDLIBS)
APP=ModifyFields

all:
	$(CXX) $(CXXFLAGS) $(APP).cpp -o $(APP) $(LIBPATH) $(LIBS) $(CPPLDFLAGS)

install:
	$(INSTALL_PROGRAM) $(APP) $(bindir)

clean:
	rm -f $(APP)


