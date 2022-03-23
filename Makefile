CXX = g++
MYCXXFLAGS = -ggdb -Wall -pedantic -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -std=gnu++11 -I./external/bit_span/include  -I./external/rasarindex/internal -I./external/rasarindex/build/_deps/bigbwt-src -I./external/rasarindex/build/_deps/klib-src -I./external/randSAbenchbase/include
CXX_LIBRARIES = -ldivsufsort64
CC = gcc
MYCFLAGS   = -ggdb -Wall -pedantic 
CXXSOURCES=$(wildcard *.cpp)
CSOURCES=$(wildcard *.c)
EXECS=$(CXXSOURCES:.cpp=.x) $(CSOURCES:.cpp=.x)
all: $(EXECS)

%.x: %.cpp
	    $(CXX) $(MYCXXFLAGS) $(CXXFLAGS) -o $@ $< $(CXX_LIBRARIES)

%.x: %.c
	    $(CC) $(MYCFLAGS) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(TARGET)
