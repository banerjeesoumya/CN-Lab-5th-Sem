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
    // Creating the socket
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        printf("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully\n");

    // Binding the socket
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        printf("Binding failed");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    printf("Binding successful\n");

    // Listening
    if (listen(server_sock, 10) == -1) {
        printf("Server is not listening");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    printf("Server is listening\n");
   
    //Acepting
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_len);
    if (client_sock == -1) {
        perror("Server is not accepting connections");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    printf("Connection established\n");
   
    int list_of_files = system("ls > result.txt");
    FILE* fp = fopen("result.txt", "r");
    char str[100];
    while (feof(fp)==0)
    {
    int buff_len=fread(str, sizeof(char), sizeof(str), fp);
    int sending = send(client_sock, str, buff_len, 0);
    }
   
    sleep(2);
    send(client_sock, "EOF", 3, 0);
   
    char file_name[BUFFER_SIZE];
    recv(client_sock, file_name, BUFFER_SIZE, 0);
    file_name[strcspn(file_name, "\n")] = 0;
    printf("Client requested file: %s\n", file_name);

    FILE *requested_file = fopen(file_name, "r");
    if (requested_file == NULL) {
        send(client_sock, "File not found\n", 15, 0);
    }
    else {
    while (feof(requested_file)==0)
    {
    int buff_len=fread(str, sizeof(char), sizeof(str), requested_file);
    printf("DATA SENT:%s\n",str);
    int sending = send(client_sock, str, buff_len, 0);
    }
  sleep(2);
        send(client_sock, "EOF", 3, 0);
        fclose(requested_file);
    }

    close(client_sock);
    close(server_sock);
}
