#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>

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
	unsigned int yes=1;
	if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes))<0)
	{
		printf("Error in setsockopt\n");
		exit(0);
	}
	struct sockaddr_in addr;
	addr.sin_port=htons(MPORT);
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sockfd,(struct sockaddr*)&addr,sizeof(addr))<0)
	{
		printf("Error in binding");
	}
	printf("Binding of socket successful\n");
	struct ip_mreq m;
	m.imr_multiaddr.s_addr = inet_addr(MIP);
	m.imr_interface.s_addr = htonl(INADDR_ANY);
	if(setsockopt(sockfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&m,sizeof(m))<0)
        {
                printf("Error in setsockopt\n");
                exit(0);
        }
	char msg[26];
	struct sockaddr_in caddr;int clen=sizeof(struct sockaddr_in);
	while(1)
	{
		int n=recvfrom(sockfd,msg,25,0,(struct sockaddr*)&caddr,&clen);			if(n<0) {printf("Error in recvfrom");exit(0);}
	       puts(msg);	
	}
	return close(sockfd);

}
