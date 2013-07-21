
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


#include "pentago_client.h"

void pent_errc(char*func, char*msg){
  char buf[128];
  sprintf(buf, "error [%s]: %s\n", func, msg);
  perror(buf);
  exit(1);
}


int run_client(int port){

  int sock;
  sockaddr_in serv_addr;
  struct hostent *server;
  char*func = strdup("run_client");
  char buf[DEFAULT_BUF_LEN];
  int inloop = 1;

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    pent_errc(func, (char*)"unable to open socket");

  if (!(server = gethostbyname("localhost")))
    pent_errc(func, (char*)"host does not exist");

  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, 
	(char *)&serv_addr.sin_addr.s_addr,
	server->h_length);
  serv_addr.sin_port = htons(port);

  if (connect(sock,(sockaddr*)&serv_addr,sizeof(sockaddr)) < 0) 
    pent_errc(func, (char*)"could not connect to server");

  while (inloop){
    printf("pentago> ");
    fgets(buf,255,stdin);
    write(sock,buf,strlen(buf));
    read(sock,buf,255);
    printf("%s\n",buf);

  }


  return 0;

}
