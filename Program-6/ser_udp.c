#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

void str_echo(int sockfd)
{
 printf("Hi\n");
 int count,size=1024;char *buffer=malloc(size);
 struct sockaddr_in cliaddr;int clilen=sizeof(cliaddr),addrlen=clilen;
 printf("Hi-2\n");
 for(;;)
 {
	 printf("Hi-3\n");
	 clilen=addrlen;
	 count=recvfrom(sockfd,buffer,size,0,(struct sockaddr*)&cliaddr,&clilen);
	 printf("Hi-4\n");
	 printf("%d\n",count);
	 fputs(buffer,stdout);
	 sendto(sockfd,buffer,count,0,(struct sockaddr*)&cliaddr,clilen);
	 printf("Hi-5\n");
 }
}

int main()
{
 int sockfd;
 if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
 {
	printf("Error in socket creation.\n");
	exit(0);
 }
 struct sockaddr_in addr;
 addr.sin_family=AF_INET;
 addr.sin_port=htons(15001);
 addr.sin_addr.s_addr= INADDR_ANY;
 printf("Server Address : %s : %d\n",inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));
 int val = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
 //printf("Value : %d\n",val);
 if(val<0)
 {
	 printf("Error in binding\n");
	 exit(0);
 }
 printf("Binding successful\n");
 str_echo(sockfd);
 return close(sockfd);
}
