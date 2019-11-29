#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 7777
#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{
    // 宣告一個client_addr來設定client socket的資訊
    struct sockaddr_in client_addr;
    // 把一段記憶體區的內容先全部設置為0
    bzero(&client_addr,sizeof(client_addr));
    // 設置成IPv4
    client_addr.sin_family = AF_INET;
    // 將地址設置為0.0.0.0，即任意位置
    client_addr.sin_addr.s_addr = htons(INADDR_ANY);
    // 0表示讓系統自動分配一個port number
    client_addr.sin_port = htons(0);
    // 創建一個socket，使用IPv4、TCP
    int client_socket = socket(AF_INET,SOCK_STREAM,0); 
    // 檢查 socket 是否有創建失敗
    if( client_socket < 0)
    {
        printf("[-]Create Socket Failed!\n");
        exit(1);
    }
    // 將設定好的address及port number設定置創建好的socket，錯誤回傳-1
    if( bind(client_socket,(struct sockaddr*)&client_addr,sizeof(client_addr)))
    {
        printf("[-]Client Bind Port Failed!\n");
        exit(1);
    }
    // 宣告一個server_addr來設定server socket的資訊
    struct sockaddr_in server_addr;
    // 把一段記憶體區的內容先全部設置為0
    bzero(&server_addr,sizeof(server_addr));
    // 設置成IPv4
    server_addr.sin_family = AF_INET;
    // 將輸入在終端機的字串轉成數字後，將之設為伺服器的address
    if(inet_aton(argv[1],&server_addr.sin_addr) == 0) 
    {
        printf("[-]Server IP Address Error!\n");
        exit(1);
    }
    // 將server port number設置成7777
    server_addr.sin_port = htons(PORT);
    // 取得server_addr的大小
    socklen_t server_addr_length = sizeof(server_addr);
    //向server發起連接請求，若錯誤則回傳-1
    if(connect(client_socket,(struct sockaddr*)&server_addr, server_addr_length) < 0)
    {
        printf("[-]Can Not Connect To %s!\n",argv[1]);
        exit(1);
    }
    // 創建放置檔案名稱的array
    char file_name[1024];
    bzero(file_name, 1024);
    // 要求client端輸入要從server端要載的檔案名稱
    printf("Please input a file name which is you want to download from server: ");
    scanf("%s", file_name);
    // 創建一個大小為1024的client端buffer，並將其清空
    char buffer[1024];
    bzero(buffer,1024);
    // 將client端輸入的file_name放進buffer中
    strncpy(buffer, file_name, 1024);
    //將buffer中的資料送出去給server
    send(client_socket,buffer,1024,0);
    // 創建一個指向下載的檔案名稱的指標，並創建此檔案
    FILE * fp = fopen(file_name,"w");
    // 若該指標為NULL，則無法打開此檔寫入，即錯誤
    if(fp == NULL)
    {
        printf("File: %s Can Not Open To Write\n", file_name);
        exit(1);
    }
    // 清空buffer
    bzero(buffer,BUFFER_SIZE);
    int length = 0;
    // client socket將收到的data放進buffer裡面，並回傳收到的位元組數
    while( length = recv(client_socket,buffer,BUFFER_SIZE,0))
    {
        // 若回傳的位元數組小於0，則代表錯誤
        if(length < 0)
        {
            printf("Recieve Data From Server %s Failed!\n", argv[1]);
            break;
        }
        // fwrite的回傳值為成功有效的讀取fp指向的檔案的元素個數
        int write_length = fwrite(buffer,sizeof(char),length,fp);
        // 若fwrite取得的回傳的元素個數小於recv得到的即錯誤
        if (write_length<length)
        {
            printf("File:\t%s Write Failed\n", file_name);
            break;
        }
        // 清空buffer
        bzero(buffer,BUFFER_SIZE);
    }
    printf("Recieve file: %s from server[%s] finished\n",file_name, argv[1]); 
    // 完成將從server端下載的資料寫入檔案中後，關閉指向檔案的指標
    fclose(fp);
    //關閉client端socket
    close(client_socket);
    return 0;
}

