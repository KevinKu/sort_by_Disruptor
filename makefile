clean_file = *.o test_Disruptor
Disruptor_test_cflags = -g -c -std=gnu99 -Wall
Disruptor_cflags = -std=gnu99 -Wall -c
Disruptor_lflags = -o test_Disruptor test_main.o Disruptor.o 
CC = gcc




bluid_Disruptor_test:test_main.o test_Disruptor.o
	$(CC) $(Disruptor_lflags)

test_main.o:
	$(CC) $(Disruptor_test_cflags) test_main.c

test_Disruptor.o:
	$(CC) $(Disruptor_test_cflags) Disruptor.c

bluid_Disruptor.o:
	$(CC) $(Disruptor_cflags) Disruptor.c

.PHONY = clean
clean:
	-rm -rf $(clean_file)
