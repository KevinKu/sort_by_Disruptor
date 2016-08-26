clean_file = *.o test_Disruptor
Disruptor_test_cflags = -g -c -std=gnu99 -Wall -pthread
Disruptor_cflags = -std=gnu99 -Wall -c
Disruptor_lflags =  -pthread -o test_Disruptor test_main.o Disruptor.o 
CC = gcc




build_Disruptor_test:test_main.o test_Disruptor.o
	$(CC) $(Disruptor_lflags)
	-rm -f *.o

test_main.o:
	$(CC) $(Disruptor_test_cflags) test_main.c

test_Disruptor.o:
	$(CC) $(Disruptor_test_cflags) Disruptor.c
	

build_Disruptor.o:
	$(CC) $(Disruptor_cflags) Disruptor.c
	-rm -f *.o

.PHONY = clean
clean:
	-rm -rf $(clean_file)


