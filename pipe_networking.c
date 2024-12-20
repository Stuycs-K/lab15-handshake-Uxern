#include "pipe_networking.h"
//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made
  wait why are we doing this in server setup???
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
// Client  Server
// w ----WKP----> r
// r <---pp----- w
  int from_client = 0;
  char * fifo = WKP;
  if (mkfifo(fifo, 0660) == -1 && errno != EEXIST) {
      perror("mkfifo");
      exit(1);
  }

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
  //Open well known pipe
  if ((fd_fifo = open(WKP, O_RDONLY)) == -1) {
      perror("open");
      exit(1);
   }
  int clinet_pid;
  read(fd_fifo, &clinet_pid, 4);
  //
  printf("Recoeved SYN name (%d)\n", clinet_pid);
  //*to_client = clinet_pid;
  remove(WKP);
  int random_syn = rand();
  //Private pipe?
   printf("Sending SYN_ACK (%d)\n", random_syn);

   write(clinet_pid, &random_syn, 4);
   int acknowledgement;
   read(fd_fifo, &acknowledgement, 4);
   printf("Recieved ACK (%d)\n", acknowledgement);
  //from_client = fd_fifo;
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
  int pp = getpid(); //pp = SYN
	//from_server = pp;
  if (mkfifo(pp, 0660) == -1 && errno != EEXIST) {
      perror("mkfifo");
      exit(1);
  }
  //Open private pipe
  int pp_fd;
  if ((pp_fd = open(pp, O_RDONLY)) == -1) {
      perror("open");
      exit(1);
   }
   //Open well known pipe
  int fd_fifo;
  if ((fd_fifo = open(WKP, O_WRONLY)) == -1) {
      perror("open");
      exit(1);
   }
 //*to_server = fd_fifo;
 //Start of handshake: sends pid into well known pipe
  printf("Sending SYN (%d) to server\n", pp);
  write(fd_fifo, &pp, 4);

  int acknowledgement;
  read(pp, &acknowledgement, 4);
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
