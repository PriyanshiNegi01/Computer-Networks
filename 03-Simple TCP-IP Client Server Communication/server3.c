#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>

int main(int asrgc,char*argv[])
{
  int bd,sd,ad;
  char buff[1024];
  struct sockaddr_in cliaddr,servaddr;
  socklen_t clilen;
  clilen=sizeof(cliaddr);
  bzero(&servaddr,sizeof(servaddr));

  //Server socket creation
  sd=socket(AF_INET,SOCK_STREAM,0);
  printf("Sockect successfully created!\n");

  //Socket address structure (assign IP, port)
  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
  servaddr.sin_port=htons(1999);

  //Binding newly created socket to specified IP and port
  bd=bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
  //Listen function specifies the maximum number of connections that can be accepted
  listen(sd,5);
  printf("Server is running...\n");
  //The server to return the next completed connection from the front of the completed connection Queue calls it
  ad=accept(sd,(struct sockaddr*)&cliaddr,&clilen);
  while(1)
  {
    bzero(&buff,sizeof(buff));
    //Receiving the request message from the client
    recv(ad,buff,sizeof(buff),0);
    printf("Message received from client: %s\n",buff);
  }
}
