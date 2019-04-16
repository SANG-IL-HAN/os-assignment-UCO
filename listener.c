//Sang il han
//cs2:~myserver/listen.c
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include<stdio.h> // Standard Input/Output library
#include<stdlib.h> // Standard library
#include<errno.h> // Error library
#include<string.h> // String library
#include<sys/types.h> // System types library
#include<netinet/in.h> // Main internet library
#include<sys/socket.h// Sockets library
#include<arpa/inet.h> // The Internet library
#define MYPORT 20084 // The port users will be connecting to
#define MAXBUFLEN 256 // The maximum receiving buffer

int main()
{
        int numbytes;// Number of bytes received
        int sockfd; // Socket descriptor
        char buf[MAXBUFLEN];
        char str[MAXBUFLEN];
        unsigned long int addr_len;
        struct sockaddr_in my_addr; /*server information */
        struct sockaddr_in their_addr; /*client information */

/*create a socket*/

        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
        {
                perror("socket");
                exit(1);
        }


        my_addr.sin_family = AF_INET; //host byte order
        my_addr.sin_port = htons(MYPORT);//short network by order
        my_addr.sin_addr.s_addr = htonl(INADDR_ANY);//zero any network card
        bzero(&(my_addr.sin_zero), 8);// Fill structure with empty info

/*bind*/

        if (bind(sockfd,(struct sockaddr*)&my_addr, sizeof(my_addr)) == -1)
        {
                perror("bind");
                exit(1);
         }

    printf("listener: waiting to recvfrom...\n"); // Give waiting to receive message
    addr_len = sizeof(struct sockaddr);

/*recvfrom*/

    if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN , 0,
        (struct sockaddr *)&their_addr, (socklen_t*)&addr_len)) == -1) 
   {        
 	perror("recvfrom"); // Give receive error
	exit(1);
    }

        buf[numbytes] = '\0'; // Add null-terminator
        inet_ntop(AF_INET,&their_addr.sin_addr,str,MAXBUFLEN); /* converted IP address*/
    printf("listener: got packet from %s\n", str); 
    printf("listener: packet is %d bytes long\n", numbytes); /*Give number of bytes in the packet*/
    printf("listener: packet contains \"%s\"\n", buf); // Print packet contents

    close(sockfd); // Close the socket
}
