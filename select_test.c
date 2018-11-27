#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int socket_fd, result;
	fd_set exceptset;
	socket_fd = open("/proc/29337/status", O_RDONLY);
	do {
		FD_ZERO(&exceptset);
		FD_SET(socket_fd, &exceptset);
		result = select(socket_fd + 1, NULL, NULL, &exceptset, NULL);
	} while (result == -1 && errno == EINTR);

	if (result > 0) {
		if (FD_ISSET(socket_fd, &exceptset)) {
		/* The socket_fd has data available to be read */
			printf("\n The process died now \n");
		}
	}
}
