//sangil han (hsi3348495@gmail.com)
//talker.c
//this program is UDP client in linux 
//a.clinet program using a transport layer protocol

#include <stdio.h>      // Standard Input/Output library
#include <stdlib.h>     // Standard library
#include <errno.h>      // Error library
#include <string.h>     // String library
#include <sys/types.h>  // System types library
#include <sys/socket.h> // Sockets library
#include <netinet/in.h> // Main internet library
#include <arpa/inet.h>  // The Internet library
 #define  HISPORT 20084 // The port users will be connecting to
 
 int main(int argc, char *argv[])// Uses command line arguments
   {
     int sockfd;// Socket descriptor
     int i=0;
     struct sockaddr_in their_addr; /* connector's address information */
     struct hostent *he;
     struct in_addr addr;
     int numbytes; // Number of bytes to send
     char str[256];

     if (argc != 3) // Check command line arguments
       {
         fprintf(stderr,"usage: talker hostname message\n");
         exit(1);
       }

     /* get the host info */
     if ((he=gethostbyname(argv[1])) == NULL)
       {
         perror("gethostbyname");
         exit(1);
        }
       
       addr.s_addr = *(u_long *) he->h_addr_list[i++];
       printf("talker :: IPv4 Address #%x: %x\n", i, addr.s_addr);

     if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
       {
         perror("socket");
         exit(1);
       }
       printf("talker::socket created -- number %d \n",sockfd);

       their_addr.sin_family = AF_INET;      /* host byte order */
       their_addr.sin_port = htons(HISPORT);  /* short, network byte order */
       their_addr.sin_addr = *((struct in_addr *)he->h_addr);
       bzero(&(their_addr.sin_zero), 8);     /* zero the rest of the struct */

       if ((numbytes=sendto(sockfd, argv[2], strlen(argv[2]), 0,
            (struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1)
         {
           perror("sendto");
           exit(1);
         }
         
       printf("talker :: sent %d bytes to %s \n", numbytes, inet_ntoa(their_addr.sin_addr));
       close(sockfd);
       return 0;
   }
