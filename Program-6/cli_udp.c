#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>

void str_cli(int sockfd,FILE *fp,struct sockaddr_in addr,int addrlen)
{
 int size=1024,count;
 char *buffer = malloc(size);
 struct sockaddr_in raddr;int rlen=sizeof(struct sockaddr_in);
 while(fgets(buffer,size,fp)!=NULL)
 {
  sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&addr,addrlen);
  if((count=recvfrom(sockfd,buffer,size,0,(struct sockaddr*)&raddr,&rlen))>0)
  	fputs(buffer,stdout);
 }
 printf("EOF\n");
}

int main(int argc, char* argv[])
{
 int sockfd;
 if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
 {
	 printf("Error in socket creation\n");
	 exit(0);
 }
 struct sockaddr_in addr;
 addr.sin_family=AF_INET;
 addr.sin_port=htons(15001);
 inet_pton(AF_INET,argv[1],&addr.sin_addr);
 
 str_cli(sockfd,stdin,addr,sizeof(addr));
 return close(sockfd);
}
