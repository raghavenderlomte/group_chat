#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
int main()
{
	int once=1;
	struct sockaddr_in server,client;
	int fd,ret;
	char serv_host_addr[40];
	char buff[2048];
	memset(&server, 0, sizeof(server));
	memset(&serv_host_addr, 0, sizeof(serv_host_addr));
	
	fd=socket(AF_INET, SOCK_STREAM, 0);
	if( -1 == fd)
	{
		perror("socket error\n");
		return -1;
	}
	client.sin_family = AF_INET;
	client.sin_port = htons(8080);
	strcpy(serv_host_addr,"192.168.131.51");
	//client.sin_addr.s_addr = inet_addr("127.0.0.1");
	if(inet_pton(AF_INET,serv_host_addr,&client.sin_addr) < 1){
	
        perror("client: inet_pton() error ->");
    }

	
	ret = connect(fd, (struct sockaddr *)&client, sizeof(client));
	if(ret == -1)
	{
		perror("connect error\n");
		return -1;
	}
	if(once)
	{
		ret = write(fd,"raghu",5);
		if ( -1 == ret)
		{
			perror("write error\n");
			return -1;
		}
		once--;
	}
	while(1)
	{
		printf("enter the data to send to server\n");
		scanf("%s",buff);
		write(fd,buff,sizeof(buff));
		memset(buff, 0,sizeof(buff));
	}
}

	
	

