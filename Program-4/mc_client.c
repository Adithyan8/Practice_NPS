#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>

#define MPORT 12345
#define MIP "225.0.0.37"
int main()
{
	int sockfd;
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		printf("Error in creation of socket\n");
		exit(0);
	}
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(MPORT);
	addr.sin_addr.s_addr=inet_addr(MIP);

	char *msg="Hello";
	while(1)
	{
		if(sendto(sockfd,msg,sizeof(msg),0,(struct sockaddr*)&addr,sizeof(addr))<0)
		{
			printf("Error in sending\n");
			exit(0);
		}
	}
}
