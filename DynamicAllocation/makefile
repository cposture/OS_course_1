objects = DynamicAllocation.o main.o
target = DynamicAllocation
CXXFLAGS = -g
all:$(objects)
	$(CXX) $(CXXFLAGS) $(objects) -o $(target)
clean:
	rm -rf $(objects) $(objectsmain) $(target)
