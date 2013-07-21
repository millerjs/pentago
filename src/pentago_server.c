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

void pent_err(char*func, char*msg){
  fprintf(stderr, "error [%s]: %s\n", func, msg);
  exit(1);
}

void pris(char*s){fprintf(stderr, "debug: %s\n", s);}

int create_socket(sockaddr_in* server_soc, int port){
  server_soc->sin_family = AF_INET;
  server_soc->sin_addr.s_addr = INADDR_ANY;
  server_soc->sin_port = htons(port);
  return 0;
}

int run_server(){

  char* func = (char*)"pentago_server";
  int n;
  int inloop = 1;
  char buf[256];
  int sockfd, newsockfd;
  int port = DEFAULT_PORT;
  socklen_t clilen;
  sockaddr_in* s_addr = (sockaddr_in*)malloc(sizeof(sockaddr_in));
  sockaddr_in* c_addr = (sockaddr_in*)malloc(sizeof(sockaddr_in));

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    pent_err(func, (char*)"unable to open socket");

  if (create_socket(s_addr, port))
    pent_err(func, (char*)"unable to initialize to socket struct");


  if (bind(sockfd, (sockaddr *) s_addr, sizeof(sockaddr)) < 0)
    pent_err(func, (char*)"unable to bind to socket");

  listen(sockfd,5);
  clilen = sizeof(c_addr);
  while (inloop){

    if ((newsockfd = accept(sockfd, (sockaddr*)&c_addr, &clilen)) < 0)
      pent_err(func, (char*)"failed to accept client bind");

    *buf = '\0';
    if ((n = read(newsockfd, buf, 255)) ){
      pent_err(func, (char*)"unable to read from socked");
    }

    printf("recvd: %s\n", buf);

    n = write(newsockfd,"I got your message",18);
    if (n < 0)
      {
	perror("ERROR writing to socket");
	exit(1);
      }

  }
  return 0; 
}
