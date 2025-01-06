compile: compile_client compile_server
compile_client: basic_client.o pipe_networking.o
	gcc -o client basic_client.o pipe_networking.o
compile_server: basic_server.o pipe_networking.o
	gcc -o server basic_server.o pipe_networking.o
basic_client.o: basic_client.c pipe_networking.h
	gcc -c basic_client.c
client:
	./client
server:
	./server
basic_server.o: basic_server.c pipe_networking.h
	gcc -c basic_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c
clean:
	rm *.o
	rm *~
