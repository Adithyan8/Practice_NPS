#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
void str_echo(int connfd)
{
 int n,size=50;char *buffer=malloc(size);
 while((n=recv(connfd,buffer,size,0))>0)
 {
  if(strcmp(buffer,"end")!=0)
  {
	  system(buffer);
	  printf("\n");
  }
  else	break;
 }
}

int main()
{
 int listenfd;
 if((listenfd=socket(AF_INET,SOCK_STREAM,0))<0)
 {
	printf("Error in socket creation.\n");
	exit(0);
 }
 struct sockaddr_in addr;
 addr.sin_family=AF_INET;
 addr.sin_port=htons(15001);
 addr.sin_addr.s_addr= INADDR_ANY;
 if(bind(listenfd,(struct sockaddr*)&addr,sizeof(addr))<0)
 {
	 printf("Error in binding\n");
	 exit(0);
 }
 printf("Binding of socket completed\n.");
 listen(listenfd,4);
 for(;;)
 {
  int connfd = accept(listenfd,(struct sockaddr*)NULL,NULL);
  str_echo(connfd);
  close(connfd);
 }
 return close(listenfd);
}
