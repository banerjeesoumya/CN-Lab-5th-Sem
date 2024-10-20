#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5000
#define BUFFER_SIZE 100

int main() {
    // Socket creation
    int client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock == -1) {
        printf("Socket creation failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully\n");

    // Establishing connection
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        printf("Connection failed\n");
        close(client_sock);
        exit(EXIT_FAILURE);
    }
    printf("Connection successful\n");

   
    FILE *fp = fopen("result1.txt", "w");
    char recv_buffer[BUFFER_SIZE];
    while (1) {
        int len = recv(client_sock, recv_buffer, sizeof(recv_buffer), 0);
        //recv_buffer[len] = '\0';  
        printf("receive BUFFER1: %s\n", recv_buffer);  
        if (strstr(recv_buffer, "EOF") != NULL) {
            break;
        }
        fwrite(recv_buffer, sizeof(char), len, fp);
    }
    fclose(fp);

    printf("\nEnter the file name you want to request: ");
    char file_name[BUFFER_SIZE];
    fgets(file_name, BUFFER_SIZE, stdin);
    send(client_sock, file_name, strlen(file_name), 0);

    printf("\nContents of the requested file:\n");
    FILE *fp1 = fopen("ContentFile.txt", "w");
    while (1) {
    int len = recv(client_sock, file_name, sizeof(file_name), 0);
    printf("Received BUFFER2: %s\n",file_name);
    if (strncmp(file_name, "EOF",3) == 0) {
            break;
        }
        fwrite(file_name, sizeof(char), len, fp1);
    }
    //while (1) {
      //  int len = recv(client_sock, recv_buffer, sizeof(recv_buffer), 0);
        //recv_buffer[len] = '\0';
       // if (strstr(recv_buffer, "EOF") != NULL) {
       //     break;
        //}
        //printf("%s", recv_buffer);
    //}

    close(client_sock);
}