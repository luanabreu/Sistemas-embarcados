prog: Ex11.o num_caracs.o  
	gcc $(CFLAGS) -o prog Ex11.o num_caracs.o 
num_caracs.o: num_caracs.c num_caracs.h  
	gcc $(CFLAGS) -c num_caracs.c  
Ex11.o: Ex11.c num_caracs.h
	gcc $(CFLAGS) -c Ex11.c 
  