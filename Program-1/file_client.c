#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	int sockfd;
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("Error in creating socket\n");exit(0);
	}
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(15000);
	inet_pton(AF_INET,argv[1],&addr.sin_addr);
	if(connect(sockfd,(struct sockaddr*)&addr,sizeof(addr))<0)
	{
		printf("Error in connection\n");
		exit(0);
	}
	char fname[20];
	printf("Enter the name of file : ");
	scanf("%s",fname);
	send(sockfd,fname,sizeof(fname),0);
	printf("Waiting for the server.\n");
	char buffer[260];
	int n=recv(sockfd,buffer,256,0);
	if(n<=0)
	{
		printf("Error in recieving data\n");exit(0);
	}
	do
	{
		write(1,buffer,n);
	}while((n=recv(sockfd,buffer,256,0))>0);
	printf("\nEOF\n");
	return 0;

}
