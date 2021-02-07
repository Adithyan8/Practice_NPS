#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
	int listenfd;
	if((listenfd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("Error in creating socket");exit(0);
	}
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(15000);
	addr.sin_addr.s_addr=INADDR_ANY;
	if(bind(listenfd,(struct sockaddr*)&addr,sizeof(addr))<0)
	{
		printf("Error in binding.");exit(0);
	}
	while(1)
	{
		listen(listenfd,4);
		int connfd = accept(listenfd,(struct sockaddr*)NULL,NULL);
		char fname[20];
		recv(connfd,fname,20,0);
		int fd = open(fname,O_RDONLY);
		if(fd<0)
		{
			printf("Error in opening file\n");
			send(connfd,fname,0,0);
			exit(0);
		}
		char buffer[256];int n;
		while((n=read(fd,buffer,256))>0)
		{
			send(connfd,buffer,n,0);
		}
		printf("Data sent\n");
		close(connfd);
	}
	close(listenfd);
}
