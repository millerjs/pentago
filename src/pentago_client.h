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

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>


#define DEFAULT_PORT 9000
#define DEFAULT_BUF_LEN 512

typedef struct sockaddr_in sockaddr_in;

int run_client(int port);
