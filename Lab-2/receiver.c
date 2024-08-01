#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
int main() {

// Creating the socket

int ret = socket(AF_INET, SOCK_DGRAM, 0);
if (ret == -1) {
	printf ("Socket creation failed \n");
	exit(0);
} else {
	printf ("Socket created succesfully \n");
}

// Binding the socket

struct sockaddr_in sent;
sent.sin_family = AF_INET;
sent.sin_port = 5000;
sent.sin_addr.s_addr = INADDR_ANY;
int ret1 = bind(ret, (const struct sockaddr*)(&sent), sizeof(sent));
if (ret1 == -1) {
	printf("Naming unsuccesfull\n");
	exit(0);
} else {
	printf("Naming successfull\n");
}
