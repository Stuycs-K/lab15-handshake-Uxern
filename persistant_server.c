#include "pipe_networking.h"
#define WKP "mario"

int server_running = 1;

static void sighandler(int signo) {
    if ( signo == SIGINT ){
		remove(WKP);
		server_running = 0;	
    }
    else if ( signo == SIGPIPE ){
    
	}
}
    
int main() {
  srand(time(NULL));
  signal(SIGINT, sighandler);
  signal(SIGPIPE, SIG_IGN);

  while (server_running) {
	  
	int to_client;
	int from_client;
	printf("Created mario pipe, waiting for client...\n");
        from_client = server_setup();
        if (from_client == -1) {
            perror("server setup");
            continue;
        }	
        if (server_handshake(&to_client) == -1) {
            perror("handshake");
            close(from_client);
            continue;
        }  
		while (server_running){
	int random_number = rand() % 101;
	if(write(to_client, &random_number, sizeof(random_number)) < 0){
		break;//exit(0);
	}
	sleep(1);
  }
	close(to_client);
	close(from_client);
  }

}
