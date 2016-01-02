objects = DynamicAllocation.o main.o Process.o
target = DynamicAllocation
CXXFLAGS = -g --std=c++11
all:$(objects)
	$(CXX) $(CXXFLAGS) $(objects) -o $(target)
clean:
	rm -rf $(objects) $(objectsmain) $(target)
