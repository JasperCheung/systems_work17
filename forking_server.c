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
  while(1){
  }
  
  subserver(server_setup());

}

void subserver(int from_client) {
  int f  = fork();
  if(f != 0 ){
    server_connect(from_client);
  }else{
    server
  
}

void process(char * s) {
  
}
