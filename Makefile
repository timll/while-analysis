ccsrc = $(wildcard src/*.cc)
obj = $(ccsrc:.cc=.o)
CXXFLAGS = -D DEBUG -g
LDFLAGS = 

all: main

main: $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean: 
	rm $(obj)
	rm main