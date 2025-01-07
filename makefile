.PHONY: clean client server compile
compile: compile_client compile_server
compile_client: basic_client.o pipe_networking.o
	gcc -o client basic_client.o pipe_networking.o
compile_server: persistant_server.o pipe_networking.o
	gcc -o server persistant_server.o pipe_networking.o
basic_client.o: basic_client.c pipe_networking.h
	gcc -c basic_client.c
persistant_server.o: persistant_server.c pipe_networking.h
	gcc -c persistant_server.c
pipe_networking.o: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c
client:
	./client
server:
	./server
clean:
	rm *.o
	rm *~
