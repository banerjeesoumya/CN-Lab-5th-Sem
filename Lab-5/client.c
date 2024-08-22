#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

int main() {
// Socket creation
    int client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock == -1) {
        printf ("Socket creation failed \n");
        exit(0);
    } else {
        printf ("Socket created successfully \n");
    }
    // Establishing connection
    struct sockaddr_in recv1;
    recv1.sin_family = AF_INET;
    recv1.sin_port = htons(6000);
    recv1.sin_addr.s_addr = inet_addr("127.0.0.1");
    int recv_connect = connect(client_sock, (const struct sockaddr*)(&recv1), sizeof(recv1));
    if (recv_connect == -1) {
     printf("Connection unsuccessful\n");
        exit(0);
    } else {
        printf("Connection successful\n");
    }
    // Sending messages
    char msg[100];
    printf ("Enter the message : \n");
    scanf("%s", msg);
    int sending = send(client_sock, msg, strlen(msg), 0);
    if (sending == -1) {
        printf ("Error");
    } else {
        printf ("Message sent successfully\n");
    }
    // Receiving messages
    char msg_buffer[100];
    int receiving = recv (client_sock, msg_buffer, sizeof(msg_buffer), 0);
    if (receiving == -1) {
        printf ("Error receiving message");
    } else {
        printf (msg_buffer);
    }
    // Closing
    int clo = close(client_sock);
    if (clo == -1) {
        printf ("\nError encountered");
    exit(0);
    } else {
        printf ("\nClient closed");
    }
}