#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

struct sockaddr_in ser;
struct sockaddr_in cli;
struct sockaddr_in broadcast;
char hash[200][20];
char emp;
void hash_update(int fd, char *name)
{
	strcpy(*(hash + fd), name);
	printf("fd %d belongs to %s\n",fd,name);
}
int hash_check(int fd)
{
	printf("hash_check %d\n",fd);
	printf("%s\n",(hash + fd));
	if(*hash[fd]==0)
	{
		printf("in if\n");
		return 0;
	}
	return 1;
}
int main()
{
	int server_fd,ret,client_fd,broad_fd;
	char buf[2048];
 	client_fd = 0;	
	server_fd = socket(AF_INET,SOCK_STREAM,0);
	if( -1 == server_fd)
	{
		perror("socket error\n");
		return -1;
	}
	broad_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if( broad_fd == -1)	
	{
		perror("broad_fd_socket\n");
		return -1;
	}
	memset(&ser, 0, sizeof(struct sockaddr_in));
	memset(&cli, 0, sizeof(struct sockaddr_in));
	memset(&broadcast, 0, sizeof(struct sockaddr_in));
	memset(buf, 0, 2048);
	ser.sin_family = AF_INET;
	ser.sin_port = htons(8080);
	ser.sin_addr.s_addr = htonl(INADDR_ANY);//htonl(INADDR_ANY);
	
	broadcast.sin_family = AF_INET;
	broadcast.sin_port = htons(8080);
	char broadcast_addr[20];
	memset(broadcast_addr,0,20);
	strcpy(broadcast_addr,"192.168.131.255");
        if(inet_pton(AF_INET,broadcast_addr,&broadcast.sin_addr) < 1)
	{

	        perror("client: inet_pton() error ->");
	}
	ret = bind(server_fd, (struct sockaddr *)&ser, sizeof(struct sockaddr_in));
	if( -1 == ret)
	{
		perror("bind error\n");
		return -1;
	}
	ret = listen(server_fd, 6);
	if( -1 == ret)
	{
		perror("listen error\n");
		return -1;
	}
	printf("size %d\n",sizeof(cli));
	int len;
	len = 16;
	int prvs=0;
	while(1)
	{
		client_fd = accept(server_fd,(struct sockaddr *)&cli,(socklen_t *)&len);

		read(client_fd, buf,2048);
		if(!hash_check(client_fd))
			hash_update(client_fd,buf);
	
		
		printf("%s\n",buf);
		
	}
}
