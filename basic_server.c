#include "pipe_networking.h"
#define WKP "mario"

int main() {
  int to_client;
  int from_client;
  from_client = server_setup();
  printf("Created mario pipe, waiting for client...\n");
  server_handshake( &to_client );
}
