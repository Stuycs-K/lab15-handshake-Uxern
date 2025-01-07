#include "pipe_networking.h"
#define WKP "mario"

int server_running = 1;

// Signal handler for SIGINT and SIGPIPE
static void sighandler(int signo) {
    if (signo == SIGINT) {
        remove(WKP);
        server_running = 0;
    } else if (signo == SIGPIPE) {
        printf("broken pipe...\n");
    }
}

int main() {
    srand(time(NULL));
    signal(SIGINT, sighandler);  
    signal(SIGPIPE, SIG_IGN);
    while (server_running) {
        int to_client, from_client;
        
        printf("Created mario pipe and waiting for a client...\n");
        from_client = server_setup();
        if (from_client == -1) {
            perror("server setup");
            continue;
        }
		pid_t p = fork();
			if(p < 0){
			printf("%s\n",strerror(errno));
			}
		else if(p == 0){
	remove(WKP);
   if (server_handshake(&to_client) == -1) {
        perror("handshake failed");
        close(from_client);
        exit(1);
    }
    printf("Sub - Handshake successful. \n");
    while (1) {
        int random_number = rand() % 101;  
        if (write(to_client, &random_number, sizeof(random_number)) == -1) {
            perror("Client disconnected?");
            break;
        }
        sleep(1); 
    }
	close(to_client);
    close(from_client);
	exit(0);
	}
}
}