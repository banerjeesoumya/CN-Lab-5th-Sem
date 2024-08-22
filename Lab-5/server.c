#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
int main() {
// Creating the socket
    int send_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (send_sock == -1) {
        printf("Socket creation failed\n");
    exit(0);
    } else {
        printf ("Socket created successfully\n");
    }
    // Binding the socket
    struct sockaddr_in sent;
    sent.sin_family = AF_INET;
    sent.sin_port = htons(6000);
    sent.sin_addr.s_addr = inet_addr("127.0.0.1");
    int send_bind = bind(send_sock, (const struct sockaddr*)(&sent), sizeof(sent));
    if (send_bind == -1) {
        printf("Binding unsuccessful\n");
        exit(0);
    } else {
        printf("Binding successful\n");
    }
    // Listening
    int send_listen = listen(send_sock, 10);
    if (send_listen == -1) {
        printf ("Server is not listening\n");
    } else {
        printf ("Server is listening\n");
    }
    // Accepting messages
    struct sockaddr_in sent1;
    int size = sizeof(sent1);
    int sender_accept = accept(send_sock, (const struct sockaddr*)(&sent1), (socklen_t *)(&size));
    if (sender_accept == -1) {
        printf ("Server is not accepting messages\n");
    } else {
        printf ("Server accepted the message from the server \n");
    }
    printf ("Connection established\n");
    // Server is receiving the message
    char msg_buffer[100];
    int receiving = recv (sender_accept, msg_buffer, sizeof(msg_buffer), 0);
    if (receiving == -1) {
        printf ("Error receiving message\n");
    } else {
        printf (msg_buffer);
    }
    // Server is sending
    printf ("\nServer is sending now\n");
    char msg[100];
    printf ("Enter the message : \n");
    scanf("%s", msg);
    int sending = send(sender_accept, msg, strlen(msg), 0);
    if (sending == -1) {
        printf ("Error\n");
    } else {
        printf ("Message sent successfully\n");
    }
    int clo = close(sender_accept);
    if (clo == -1) {
        printf ("Error encountered");
    exit(0);
    } else {
        printf ("Server closed");
    }
}