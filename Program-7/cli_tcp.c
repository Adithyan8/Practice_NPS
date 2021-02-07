#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

void str_cli(int sockfd,FILE *fp)
{
 int size=50,count;
 char *buffer = malloc(size);
 while(fgets(buffer,size,fp)!=NULL)
 {
  send(sockfd,buffer,sizeof(buffer),0);
  if(strcmp(buffer,"end")==0)
	  break;
 }
 printf("End of communication\n");
}

int main(int argc, char* argv[])
{
 int sockfd;
 if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
 {
	 printf("Error in socket creation\n");
	 exit(0);
 }
 struct sockaddr_in addr;
 addr.sin_family=AF_INET;
 addr.sin_port=htons(15001);
 inet_pton(AF_INET,argv[1],&addr.sin_addr);
 if(connect(sockfd,(struct sockaddr*)&addr,sizeof(addr))<0)
 {
	 printf("Error in Connection established\n");
	 exit(0);
 }
 printf("Communicating with the server\n");
 str_cli(sockfd,stdin);
 return close(sockfd);
}
