objects = FCFS.o
target = FCFS
target:$(objects)
	g++ -g $(objects) -o $(target) 

$(objects):%.o:%.cpp
objects:
	g++ -c -g %< -o $(objects) 
clean:
	rm -rf $(objects) $(target)
