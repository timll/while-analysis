ccsrc = $(wildcard src/*.cc src/*/*.cc src/*/*/*.cc src/*/*/*/*.cc)
obj = $(ccsrc:.cc=.o)
CXXFLAGS = -Wall -DDEBUG -g
LDFLAGS = 

all: main

main: $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean: 
	rm $(obj)
	rm main