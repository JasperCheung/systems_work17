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
  int to_client;
  int from_client;
  char buffer[BUFFER_SIZE];

  // from_client = server_handshake(&to_client);
  
   while(1){
     from_client = server_setup();
     printf("forking off... \n");
     
     int f  = fork();

     if(f == 0){
       printf("subserver\n");
       subserver(from_client);
     }
     else{ //parent (server) //removes connection to WKP, cretes WKP and waits for new connections
       printf("[server] ");
       remove("luigi");
       printf("WKP 'luigi' is removed\n");
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
}

void process(char * s) {
  while (*s != '\0'){
    *s = toupper((unsigned char) *s);
  }
}
