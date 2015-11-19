objects = HRN.o
target = HRN
target:$(objects)
	gcc -g $(objects) -o $(target) 

$(objects):%.o:%.cpp
objects:
	gcc -g -c %< -o $(objects) 
clean:
	rm -rf $(objects) $(target)
