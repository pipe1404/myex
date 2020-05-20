all: code pi_serial pi_multi-thread
code: code.c
	gcc -c code.c
	gcc -o code code.o -pthread
pi_serial: pi_serial.c
	gcc -c pi_serial.c
	gcc -o pi_serial pi_serial.c
pi_multi-thread: pi_multi-thread.c
	gcc -c pi_multi-thread.c
	gcc -o pi_multi-thread pi_multi-thread.o -pthread
clean:
	rm -rf *.o pi_serial code pi_multi-thread
	
