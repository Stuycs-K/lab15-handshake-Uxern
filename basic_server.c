#include "pipe_networking.h"
#define WKP "mario"

int main() {
  int to_client;
  int from_client;
  printf("Created mario pipe, waiting for client...\n");
  from_client = server_setup();
  server_handshake( &to_client );
}
