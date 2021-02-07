#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>

void str_echo(int sockfd)
{
	int size=1024,count;
	char *buffer=malloc(size);

	while((count=recv(sockfd,buffer,size,0))>0)
	{
		fputs("Client:",stdout);
		fputs(buffer,stdout);
		fputs("\nMe:",stdout);
		if(fgets(buffer,size,stdin)!=NULL)
			send(sockfd,buffer,sizeof(buffer),0);
	}
}

int main()
{
	int listenfd;
	if((listenfd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("Error in creating socket");
		exit(0);
	}
	struct sockaddr_in addr;
	addr.sin_port=htons(15000);
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=INADDR_ANY;
	if(bind(listenfd,(struct sockaddr*)&addr,sizeof(addr))<0)
	{
		printf("Error in binding socket");
		exit(0);
	}
	listen(listenfd,4);
	for(;;)
	{
		int connfd = accept(listenfd,(struct sockaddr*)NULL,NULL);
		int pid;
		if((pid=fork())==0)
		{
			close(listenfd);
			str_echo(connfd);
			close(listenfd);
			exit(0);
		}
		close(connfd);
	}

}
