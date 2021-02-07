#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<stdlib.h>

void str_cli(int sockfd,FILE *fp)
{
	int size=1024,count;
	char *buffer=malloc(size);
	fputs("Me:",stdout);
	while(fgets(buffer,size,stdin)>0)
	{
		send(sockfd,buffer,sizeof(buffer),0);
		if((count=recv(sockfd,buffer,size,0))>0)
		{
			fputs("Server:",stdout);
			fputs(buffer,stdout);
		}
		fputs("Me:",stdout);
	}
	printf("End of chat\n");

}

int main(int argc,char *argv[])
{
	int sockfd;
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("Error in creating socket");
		exit(0);
	}
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(15000);
	inet_pton(AF_INET,argv[1],&addr.sin_addr);
	if(connect(sockfd,(struct sockaddr*)&addr,sizeof(addr))<0)
	{
		printf("Error in connection");
		exit(0);
	}

	str_cli(sockfd,stdin);
	return close(sockfd);
}
