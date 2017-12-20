#include "pipe_networking.h"
#include <signal.h>

void process(char *s);
void subserver(int from_client);

static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove("luigi");
    exit(0);
  }
}

int main() {
  signal(SIGINT, sighandler);
  int from_client;
  int t
  // from_client = server_handshake(&to_client);
  
  while(1){
    from_client = server_setup();
    printf("forking off... \n");
    int f  = fork();
    //if child
    if(!f){
      printf("subserver\n");
      subserver(from_client);
    }  else{
      close(from_client);

      
    }
  }
}
  


//Subserver connects to client FIFO, sending an intual acknowledgement message

void subserver(int from_client) {
  int to_client = server_connect(from_client);
  char buffer[BUFFER_SIZE];

  
  while(read(from_client, buffer, sizeof(buffer))){
  
    printf("[subserver]received message from client: %s",buffer);
    process(buffer);
    write(to_client, buffer,sizeof(buffer));
  }
  exit(0);
}

void process(char * s) {
  while (*s != '\0'){
    *s = toupper((unsigned char) *s);
  }
}
