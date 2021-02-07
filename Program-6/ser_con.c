#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

void str_echo(int connfd)
{
 int n,size=1024;char *buffer=malloc(size);
 while((n=recv(connfd,buffer,size,0))>0)
 {
  fputs(buffer,stdout);
  send(connfd,buffer,n,0);
 }
 printf("End of communication\n");
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
 addr.sin_port=htons(15000);
 addr.sin_addr.s_addr= INADDR_ANY;
 if(bind(listenfd,(struct sockaddr*)&addr,sizeof(addr))<0)
 {
	 printf("Error in binding\n");
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
   close(connfd);
   exit(0);
  }
  close(connfd);
 }
 return close(listenfd);
}
