
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

// Receiveing 

char recv_buff [100]; 
struct sockaddr_in recv;
int size = sizeof(recv);

int res = recvfrom (ret, recv_buff, sizeof(recv_buff), 0, (struct sockaddr*)(&recv), (socklen_t *)(&recv));
if (res == -1) {
	printf("Error");
} else {
	printf ("%s\n", recv_buff);
}

// Sending

//printf ("Now reciver is sending: \n"); 

//char msg[100];
//printf ("Enter the message : \n");
//scanf("%s", msg);
//struct sockaddr_in sendTo;
//sendTo.sin_family = AF_INET;
//sendTo.sin_port = 6000;
//sendTo.sin_addr.s_addr = INADDR_ANY;

//int sen = sendto(ret, msg, strlen(msg), 0, (const struct sockaddr*)(&sendTo), sizeof(sendTo));
//if (sen == -1) {
//	printf ("Error");
//} else {
//	printf ("Message sent successfully\n");
//}

}