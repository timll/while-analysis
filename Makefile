ccsrc = $(wildcard src/*.cc)
obj = $(ccsrc:.cc=.o)
CXXFLAGS = -DDEBUG -g
LDFLAGS = 

main: $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS)
