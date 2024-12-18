#include "pipe_networking.h"
//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  int from_client = 0;
  return from_client;
}

/*=========================
  server_handshake 
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
  int from_client;
  int fd_fifo;
  if ((fd_fifo = open(WKP, O_RDONLY)) == -1) {
      perror("open");
      exit(1);
   }
  int clinet_pid;
  read(fd_fifo, &clinet_pid, 4);
  printf("Recoeved SYN name (%d)\n", clinet_pid);
  *to_client = clinet_pid;
  remove(WKP);
  int random_syn = rand(time(NULL));
  //Private pipe?
   printf("Sending SYN_ACK (%d)\n", random_syn);
   write(clinet_pid, &random_syn, 4);
   int acknowledgement;
   read(fd_fifo, &acknowledgement, 4);
   printf("Recieved ACK (%d)\n", acknowledgement);
  from_client = fd_fifo;
  close(fd_fifo);
  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server;
  int pid = getpid(); //pid = SYN
	from_server = pid;
  int fd_fifo;
  if ((fd_fifo = open(WKP, O_WRONLY)) == -1) {
      perror("open");
      exit(1);
   }
 *to_server = fd_fifo;
  printf("Sending SYN (%d) to server\n", pid);
  write(fd_fifo, &pid, 4);
  int acknowledgement;
  read(pid, &acknowledgement, 4);
  printf("Recieved SYN_ACK (%d), sending ACK (%d) to server \n", acknowledgement, acknowledgement + 1);
  acknowledgement++;
  write(fd_fifo, &acknowledgement, 4);
  return from_server;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int to_client  = 0;
  return to_client;
}


