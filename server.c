#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

/*
//  NAME         : Constantine Peros
//
//  HOMEWORK     : 2
//
//  CLASS        : ICS 451
//
//  INSTRUCTOR   : Ravi Narayan
//
//  DATE         : September 22, 2022
//
//  FILE         : server.c
//
//  DESCRIPTION  : A barest of bones server, Hosts a message that can be recieved via Telnet.
//                 Assistance from https://www.youtube.com/watch?v=jRJKpfSBXvY
*/

int main(int argc, char *argv[])
{
   struct sockaddr_in address, cAddress;
   int opt = 1;
   int sz = sizeof(struct sockaddr_in);
   socklen_t cSz = sizeof(struct sockaddr_in);
   int sock, cSock;
   FILE* fp;
   char sendMe; 
   int port;
   int run = 1;
   char *filename = "file_server.png";

   if( argc == 2 ) 
   {
      port = atoi(argv[1]);
      address.sin_family = AF_INET;
      address.sin_port = htons(port);
      address.sin_addr.s_addr = 0;
      /* Statements below print a negative value upon failure */
      printf("Using port number %d...\n", port);
      printf("Creating A Socket...%d\n", sock = socket(PF_INET, SOCK_STREAM, 0));
      printf("Accessing port Number %d...%d\n", port, setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)));
      printf("Binding to Socket Address...%d\n", bind(sock, (struct sockaddr*)&address, sz));
      printf("Listening For Connection...%d\n", listen(sock, 4));

      while(run)
      {
         printf("...%d\n", cSock = accept(sock, (struct sockaddr*)&cAddress, &cSz));
         printf("Sending Message...\n");
         fp = fopen(filename, "r");
         while(!feof(fp))
         {
            sendMe = fgetc(fp);
            if (!feof(fp)) send(cSock, &sendMe, sizeof(sendMe), 0);
         }
         printf("Message Sent...\n");
         run = 0;
         
      }
      fclose(fp);
      close(sock);
      close(cSock);
   }
   else
   {
      printf("Incorrect Number of Arguments\n");
      run = -1;
   }
   return run;
}
