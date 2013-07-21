/***************************************************************/
/* This file is a member of the pentago game server written by */
/*                                                             */
/*                 Rachel Hwang & Josh Miller                  */
/*                                                             */
/*            _ __   ___ _ __ | |_ __ _  __ _  ___             */
/*           | '_ \ / _ \ '_ \| __/ _` |/ _` |/ _ \            */
/*           | |_) |  __/ | | | || (_| | (_| | (_) |           */
/*           | .__/ \___|_| |_|\__\__,_|\__, |\___/            */
/*           |_|                        |___/                  */
/*                                                             */
/*                                                             */
/*                    Because we're awesome.                   */
/*                                                             */
/***************************************************************/

#include "pentago_server.h"


void pris(char*s){fprintf(stderr, "debug: %s\n", s);}
void prii(int i){fprintf(stderr, "debug: %d\n", i);}

void pent_errs(char*func, char*msg){
  char buf[128];
  sprintf(buf, "error [%s]: %s", func, msg);
  perror(buf);
  exit(1);
}

int create_socket(sockaddr_in* server_soc, int port){
  server_soc->sin_family = AF_INET;
  server_soc->sin_addr.s_addr = INADDR_ANY;
  server_soc->sin_port = htons(port);
  return 0;
}

void * server_thread(void* vargs){

  prii(1);
  char*func = strdup("server_thread");
  prii(2);

  thread_args *args = (thread_args*) vargs;
  prii(3);


  int sock = args->socket;
  char buf[DEFAULT_BUF_LEN];

  while(1){
    
    if (read(sock, buf, sizeof(buf)) < 0)
      pent_errs(func, (char*)"unable to read from socket");

    printf("revcd cmd: %s", buf);

    char* msg = strdup("ACK\n");
    if (write(sock,msg,strlen(msg)) < 0)
      pent_errs(func, (char*)"unable to write to socket");

  }

  return 0;
}

int parse_cmd(char*cmd){

  // char*func = strdup("parse_cmd");
  printf("recvd: %s\n", cmd);


  
  return 0;
  
}

int run_server(int port){

  char* func;
  int inloop;
  int s_sock, bound;
  socklen_t c_len;

  func = strdup("pentago_server");
  inloop = 1;

  sockaddr_in* s_addr = (sockaddr_in*)malloc(sizeof(sockaddr_in));
  sockaddr_in* c_addr = (sockaddr_in*)malloc(sizeof(sockaddr_in));

  // initialize socket
  if ((s_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    pent_errs(func, (char*)"unable to open socket");

  // fill socket 
  if (create_socket(s_addr, port))
    pent_errs(func, (char*)"unable to initialize to socket struct");

  // bind
  if (bind(s_sock, (sockaddr *) s_addr, sizeof(sockaddr)) < 0)
    pent_errs(func, (char*)"unable to bind to socket");

  // set socket to listen for clients
  listen(s_sock,5);
  c_len = sizeof(c_addr);

  while (1){

    // upon receive sock
    if ((bound = accept(s_sock, (sockaddr*)&c_addr, &c_len)) < 0)
      pent_errs(func, (char*)"failed to accept client bind");

    // ready thread
    thread_args args;
    args.socket = bound;
    pthread_t* s_thread = (pthread_t*)malloc(sizeof(pthread_t));

    // spawn client's thread
    if (!(s_thread = (pthread_t*)malloc(sizeof(pthread_t))))
      pent_errs(func, "unable to add new client thread");

    fprintf(stderr, "New connection: %d.\n", bound);
    pthread_create(s_thread, NULL, &server_thread, (void*) &args);
    

  }
  return 0; 
}
