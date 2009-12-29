## your application name here
APP=
SRC=$(APP).cpp
## extra object files for your app here
OBJ=

prefix = /usr/local
exec_prefix = ${prefix}
libdir = ${exec_prefix}/lib
includedir = ${prefix}/include
INCPATH=-I$(includedir)
LIBPATH=-L$(libdir) -L/home/mee/workspaceCPP/hunStemmer/Debug
CXXFLAGS=-DPACKAGE_NAME=\"Indri\" -DPACKAGE_TARNAME=\"indri\" -DPACKAGE_VERSION=\"2.8\" -DPACKAGE_STRING=\"Indri\ 2.8\" -DPACKAGE_BUGREPORT=\"indri-info@ciir.cs.umass.edu\" -DINDRI_STANDALONE=1 -DHAVE_LIBM=1 -DHAVE_LIBPTHREAD=1 -DHAVE_LIBZ=1 -DHAVE_NAMESPACES= -DISNAN_IN_NAMESPACE_STD= -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -D_FILE_OFFSET_BITS=64 -DHAVE_FSEEKO=1 -DHAVE_EXT_ATOMICITY_H=1 -DP_NEEDS_GNU_CXX_NAMESPACE=1 -DHAVE_MKSTEMP=1 -DNDEBUG=1  -g -O3 $(INCPATH)
CPPLDFLAGS  =  -lindri -lz -lpthread -lm 

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(APP) $(OBJ) $(LIBPATH) $(CPPLDFLAGS)

clean:
	rm -f $(APP)


