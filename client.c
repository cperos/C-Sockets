#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

/*
//  NAME         : Constantine Peros
//
//  HOMEWORK     : 3
//
//  CLASS        : ICS 451
//
//  INSTRUCTOR   : Ravi Narayan
//
//  DATE         : Octobner 05, 2022
//
//  FILE         : client.c
//
//  DESCRIPTION  : A barest of bones client, Recieves a message from server on pecified port.
//                 Assistance from https://www.youtube.com/watch?v=jRJKpfSBXvY
*/

int main(int argc, char *argv[])
{
   int port, sock, run;
   struct sockaddr_in address;
   int sz = sizeof(struct sockaddr_in);
   char msg;
   FILE* fp;
   char *filename = "file_client.png";

   if( argc == 2 ) 
   {
      port = atoi(argv[1]);
      printf("port is %d\n", port);
      address.sin_family = AF_INET;
      address.sin_port = htons(port);
      address.sin_addr.s_addr = 0;
      /* Statements below print a negative value upon failure */
      printf("Using port number %d...\n", port);
      printf("Creating A Socket...%d\n", sock = socket(AF_INET, SOCK_STREAM, 0));
      printf("Connecting to Socket Address...%d\n", connect(sock, (struct sockaddr*)&address, sz));
      printf("Recieving Message From Server...\n");
      fp = fopen(filename, "w+");
      while (recv(sock, &msg, sizeof(msg), 0) > 0) fprintf(fp, "%c", msg);
      fclose(fp);
      close(sock);
      run = 0;
   }
   else
   {
      printf("Incorrect Number of Arguments\n");
      run = -1;
   }
   return run;
}
