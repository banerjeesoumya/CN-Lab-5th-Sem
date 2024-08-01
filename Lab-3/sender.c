#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include<string.h>
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
sent.sin_port = 6000;
sent.sin_addr.s_addr = INADDR_ANY;
int ret1 = bind(ret, (const struct sockaddr*)(&sent), sizeof(sent));
if (ret1 == -1) {
	printf("Binding unsuccesfull\n");
	exit(0);
} else {
	printf("Binding successfull\n");
}

// Sending

char msg[100];
printf ("Enter the message : \n");
scanf("%s", msg);
struct sockaddr_in sendTo;
sendTo.sin_family = AF_INET;
sendTo.sin_port = 5000;
sendTo.sin_addr.s_addr = INADDR_ANY;

int res = sendto(ret, msg, strlen(msg), 0, (const struct sockaddr*)(&sendTo), sizeof(sendTo));
if (res == -1) {
	printf ("Error");
} else {
	printf ("Message sent successfully\n");
}

//printf ("Now sender is receiving : \n");
//char rec_buff[100];
//struct sockaddr_in recv;
//int size = sizeof(recv);

//int rec = recvfrom (ret, rec_buff, sizeof(rec_buff), 0, (struct sockaddr*)(&recv), (socklen_t *)(&recv));
//if (rec == -1) {
//	printf("Error");
//} else {
//	printf ("%s\n", rec_buff);
//}
}