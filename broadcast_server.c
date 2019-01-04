#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>

char *a = "emergency";
int main()
{
	int ret,sock_fd;
	struct sockaddr_in broadcast;
	sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock_fd == -1)
	{
		perror("socket error\n");
		return -1;
	}
	int broad = 1;
	ret = setsockopt(sock_fd, SOL_SOCKET, SO_BROADCAST, &broad, sizeof(int));
	if(ret == -1)
	{
		perror("setsockopt\n");
		return -1;
	}
	memset(&broadcast, 0, sizeof(broadcast));
	broadcast.sin_family = AF_INET;
	broadcast.sin_port = htons(8080);
	broadcast.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	
	if(sendto(sock_fd, a, strlen(a), 0, (struct sockaddr *)&broadcast, sizeof(struct sockaddr_in)) < 0)
	{
		perror("send ot\n");
	}
}
	
