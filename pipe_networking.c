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
  if ((from_client = open(WKP, O_RDONLY)) == -1) {
      perror("open");
      exit(1);
   }
  char pp[HANDSHAKE_BUFFER_SIZE];
  if (read(from_client, pp, sizeof(pp)) <= 0) {
    perror("read");
    exit(1);
  }
   printf("Sending SYN_ACK (%s)\n", pp);
   remove(WKP);
  if ((*to_client = open(pp, O_WRONLY)) == -1) {
    perror("open");
    exit(1);
  }
   int random_syn = rand();
   write(*to_client, &random_syn, 4);
   int acknowledgement;
   read(from_client, &acknowledgement, 4);
   printf("Recieved ACK (%d)\n", acknowledgement);
  close(from_client);
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
  char pp[HANDSHAKE_BUFFER_SIZE];
  snprintf(pp, sizeof(pp), "%d", getpid());
  //from_server = pp;
  //snprintf this;
  if (mkfifo(pp, 0660) == -1 && errno != EEXIST) {
      perror("mkfifo");
      exit(1);
  }
  if ((*to_server = open(WKP, O_WRONLY)) == -1) {
      perror("open");
      exit(1);
   }
 //*to_server = fd_fifo;
  printf("Sending SYN (%s) to server\n", pp);
  write(*to_server, pp, 4);
  from_server = open(pp, O_RDONLY);
  int acknowledgement;
  read(from_server, &acknowledgement, 4);
  printf("Recieved SYN_ACK (%d), sending ACK (%d) to server \n", acknowledgement, acknowledgement + 1);
  acknowledgement++;
  write(*to_server, &acknowledgement, 4);
  remove(pp);
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
