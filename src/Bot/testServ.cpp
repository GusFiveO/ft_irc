#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void
usage(const char *str)
{
	printf("Usage: %s <port> \n", str);
	exit(-1);
}

int
create_server(int port)
{
	int                 sock;
	struct sockaddr_in  sin;
	struct protoent     *proto;

	proto = getprotobyname("tcp");
	if (!proto)
	{
		return -1;
	}
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		printf("Bind error\n");
		exit(-2);
	}
	listen(sock, 42);
	return sock;
}

int
main(int argc, char const *argv[])
{
	int 				cs;
	int 				port;
	int					sock;
	unsigned int 		cslen;
	struct 	sockaddr_in csin;

	int		r;
	char	buf[1024];

	if (argc != 2)
	{
		usage(argv[0]);
	}
	port = atoi(argv[1]);
	sock = create_server(port);
	cs = accept(sock, (struct sockaddr *)&csin, &cslen);
	while ((r = read(cs, buf, 1023)) != 0)
	{
		buf[r] = 0;
		printf("Received %d bytes : [%s] \n", r, buf);
	}
	close(cs);
	close(sock);
	return 0;
}