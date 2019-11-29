#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444
#define HELLO_WORLD_SERVER_PORT    6666
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512

int main(){

    int clientSocket, ret;
    // 宣告一個serverAddr來設定serversocket的資訊
    struct sockaddr_in serverAddr;
    // 宣告一個大小為 1024 的陣列buffer
    char buffer[1024];
    // Client端創建一個socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    // 若創建的回傳值小於0即發生錯誤
    if(clientSocket < 0){
        printf("[-]Error in connection.\n");
        exit(1);
    }
    printf("[+]Client Socket is created.\n");
    // 清空serverAddr
    memset(&serverAddr, '\0', sizeof(serverAddr));
    // 設定成IPv4
    serverAddr.sin_family = AF_INET;
    // 將要連線的server port number設定成4444
    serverAddr.sin_port = htons(PORT);
    // 將要連線的server IP address設定成loopback address 127.0.0.1
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Client端發起連線至Server端
    ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    // 若connect的回傳值小於0即發生錯誤
    if(ret < 0){
        printf("[-]Error in connection.\n");
        exit(1);
    }
    printf("[+]Connected to Server.\n");
    printf("Client: \t");
    // Client端輸入要執行的動作，此輸入放進buffer中
    scanf("%s", &buffer[0]);
    // 將buffer的內容透過clientSocket送出去
    send(clientSocket, buffer, strlen(buffer), 0);
    // 若使用者輸入的是exit的話就直接斷掉與server的連線
    if(strcmp(buffer, "exit;") == 0){
        // 關閉client端的socket
        close(clientSocket);
        printf("[-]Disconnected from server.\n");
        // 結束應用程式
        exit(1);
    }
    // 若使用者輸入的是download;，則開始下載檔案
    if(strcmp(buffer, "download;") == 0){
        printf("Downloading.....\n");
        // 創建指向要寫入的檔案的指標，並創建此檔案
        FILE * fp = fopen("HW2.txt","w");
        // 若此fp為NULL，即發生錯誤，無法打開檔案寫入
        if(fp == NULL)
        {
            printf("File:HW2.txt Can Not Open To Write\n");
            exit(1);
        }
        // 將buffer清空
        bzero(buffer,1024);
        // 創建存放recv回傳值的變數
        int length = 0;
        // 透過clientSocket從獲取資料放進buffer中，並回傳收到的位元組數
        while( length = recv(clientSocket,buffer,1024,0))
        {
            // 若收到的位元組數小於0即發生錯誤
            if(length < 0)
            {
                printf("Recieve Data From Server Failed!\n");
                break;
            }
            // fwrite的回傳值為成功有效的讀取fp指向的檔案的元素個數
            int write_length = fwrite(buffer,sizeof(char),length,fp);
            // 若fwrite回傳值小於從socket取得的資料數量即發生錯誤
            if (write_length<length)
            {
                printf("File:HW2.txt Write Failed\n");
                break;
            }
            // 清空buffer
            bzero(buffer,1024); 
        }
        printf("Recieve File:HW2.txt From Server Finished\n"); 
        // 關閉指向要寫入的檔案的指標
        fclose(fp); 
        printf("[-]Disconnected from server.\n");
        // 關閉client端socket
        close(clientSocket);
        // 結束應用程式
        exit(1);		
    }
    return 0;
}

