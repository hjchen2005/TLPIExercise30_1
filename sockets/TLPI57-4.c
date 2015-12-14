/*
This program will get a EPERM error. On Linux, the sendto() call fails with the error EPERM. On some other UNIX systems,
a different error results. Some other UNIX implementations don’t enforce this
constraint, letting a connected UNIX domain datagram socket receive datagrams
from a sender other than its peer.
*/

#include "us_xfr.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

void logger(const char* tag, const char* message);
void logger(const char* tag, const char* message) {
   time_t now;
   time(&now);
   printf("%s [%s]: %s\n", ctime(&now), tag, message);
}
int main(int ac, char *av[]){
	const char *SOCKa = "tmp/socketsa";
	const char *SOCKb = "tmp/socketsb";
	const char *SOCKc = "tmp/socketsc";
	int sfd,  sfd1, sfd2;
	struct sockaddr_un addr_a;
	struct sockaddr_un addr_b;
	struct sockaddr_un addr_c;
		
	size_t msglen=200;
	
	sfd = socket(AF_UNIX, SOCK_DGRAM,0);
	if (sfd == -1)
		logger(SOCKa,"socket A cannot be created");

	sfd1 = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sfd1 == -1)
		logger(SOCKb,"socket B cannot be created");

	sfd2 = socket(AF_UNIX, SOCK_DGRAM,0);
	if(sfd1 == -1)
		logger(SOCKc,"socket C cannot be created");

	memset (&addr_a, 0, sizeof(struct sockaddr_un));
	addr_a.sun_family = AF_UNIX;
 	strncpy(addr_a.sun_path, SOCKa, sizeof(addr_a.sun_path) -1);
	if (bind(sfd, (struct sockaddr*) &addr_a, sizeof(struct sockaddr_un))== -1)
		logger(SOCKa,"binding socket A failed");
	//Binding socket "b"
	memset (&addr_b, 0, sizeof(struct sockaddr_un));
	addr_b.sun_family = AF_UNIX;
	strncpy(addr_b.sun_path, SOCKb, sizeof(addr_b.sun_path) -1);
	if (bind(sfd1, (struct sockaddr*) &addr_b, sizeof(struct sockaddr_un))== -1)
		logger(SOCKb,"binding socket B failed");
	if (connect(sfd,(struct sockaddr *) &addr_b, sizeof(struct sockaddr_un))==-1)
		logger(SOCKc,"binding socket B failed");

	//Binding socket c
	memset (&addr_c, 0, sizeof(struct sockaddr_un));
	addr_c.sun_family = AF_UNIX;
	strncpy(addr_c.sun_path, SOCKc, sizeof(addr_c.sun_path) -1);

	if (bind(sfd2, (struct sockaddr*) &addr_c, sizeof(struct sockaddr_un))== -1){
		errExit("bind");	
	}

	if (connect(sfd,(struct sockaddr *) &addr_b, sizeof(struct sockaddr_un))==-1){
		errExit("send to");
	}

	if (sendto(sfd2,s1,msglen,0,(struct sockaddr*)&addr_a,sizeof(struct sockaddr_un))==-1){
		errExit("send to");
	}

	return 0;
}
