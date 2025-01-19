OBJ:= $(patsubst %.c, %.o, $(wildcard *.c))
Project.out: $(OBJ)
	gcc -o $@ $^  
clean:
	rm *.o *.out