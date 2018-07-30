#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>


#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 10010 /*port*/

int main(int argc, char **argv) 
{
  int sockfd;
  struct sockaddr_in servaddr;
  char sendline[MAXLINE], recvline[MAXLINE];

  // alarm(300);  // to terminate after 300 seconds
  
  //basic check of the arguments
  perror(argv[1]);
  perror(argv[2]);
 
  if (argc !=4) {
    perror("Usage: TCPClient <Server IP> <Server Port> <Sleep Interval>"); 
    exit(1);
  }
  int sleeptime=atoi(argv[3]);
  //Creation of the socket
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr= inet_addr(argv[1]);
  servaddr.sin_port =  htons((int) strtol(argv[2], (char **)NULL, 10));
  
  //Create a socket for the client
  //If sockfd<0 there was an error in the creation of the socket
  if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
    perror("Problem in creating the socket");
    exit(2);
  }
  //Connection of the client to the socket 
  if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
    perror("Problem in connecting to the server");
    exit(3);
  }
  printf("Enter line to loop for %d seconds:",sleeptime);
  fgets(sendline,MAXLINE,stdin);
  FILE *fp;
  fp=fopen("a3p2Clientlog1.txt", "w");
  fclose(fp);
  while (1) {
    
    send(sockfd, sendline, strlen(sendline), 0);
    
    if (recv(sockfd, recvline, MAXLINE,0) == 0){
      //error: server terminated prematurely
      perror("The server terminated prematurely"); 
      exit(4);
    }
    printf("%s", "String received from the server: \n");
    fputs(recvline, stdout);
  
    fp = fopen("a3p2Clientlog1.txt", "a");
    fprintf(fp, "%s", recvline);
    fclose(fp);

    sleep(sleeptime);
  }

  exit(0);
}
