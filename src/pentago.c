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
#include <strings.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include "pentago_server.h"
#include "pentago_client.h"

int main(int argc, char *argv[]){

  run_server();

  return 0; 
}
