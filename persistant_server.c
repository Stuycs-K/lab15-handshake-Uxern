
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
    srand(time(NULL));  // Seed random number generator
    signal(SIGINT, sighandler);  // Register signal handlers
    signal(SIGPIPE, SIG_IGN);

    while (server_running) {
        int to_client, from_client;

        // Create WKP and wait for client
        printf("Created mario pipe and waiting for a client...\n", WKP);
        from_client = server_setup();
        if (from_client == -1) {
            perror("server setup");
            continue;
        }

        // Perform handshake with client
        if (server_handshake(&to_client) == -1) {
            perror("handshake");
            close(from_client);
            continue;
        }

        printf("Handshake successful \n");

        // Send random numbers to the client
        while (server_running) {
            int random_number = rand() % 101;  // Random number between 0 and 100
            printf("Sending: %d\n", random_number);

            if (write(to_client, &random_number, sizeof(random_number)) == -1) {
                perror("Error writing");
                break;
            }

            sleep(1);  // Wait 1 second before sending the next number
        }

        // Clean up file descriptors after client disconnects
        printf("dced \n");
        close(to_client);
        close(from_client);
    }

    printf("j\n");
    return 0;
}
