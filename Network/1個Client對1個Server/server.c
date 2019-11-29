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
    // 宣告一個server_addr來設定server socket的資訊
    struct sockaddr_in server_addr;
    // 把一段記憶體區的內容先全部設置為0
    bzero(&server_addr,sizeof(server_addr)); 
    // 設置成IPv4
    server_addr.sin_family = AF_INET;
    // 地址設置成0.0.0.0，即任意的地址
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    // 設置port number為7777
    server_addr.sin_port = htons(PORT);
    
    // 創建一個socket，使用IPv4、TCP
    int server_socket = socket(AF_INET,SOCK_STREAM,0);
    // 檢查 socket 是否有創建失敗
    if( server_socket < 0)
    {
        printf("[-]Create socket failed!");
        exit(1);
    }
 
    // 將設定好的address及port number設定置創建好的socket，錯誤回傳-1
    if( bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))
    {
        printf("[-]Server bind port : %d failed!", PORT);
        exit(1);
    }
    // 監聽server socket有無連線請求，最多5個client能連線，錯誤回傳-1
    if ( listen(server_socket, 5) )
    {
        printf("[-]Server listen failed!");
        exit(1);
    }
    // 無限迴圈，使server socket能一直運作
    while (1)
    {
        // 宣告一個client_addr，來存放client端的資訊
        struct sockaddr_in client_addr;
        socklen_t length = sizeof(client_addr);
        // 接收client端的連線，並產出新的socket，專與此client溝通
        int new_server_socket = accept(server_socket,(struct sockaddr*)&client_addr,&length);
        // 若accept返回-1即代表錯誤
        if ( new_server_socket < 0)
        {
             printf("[-]Server accept failed!\n");
             break;
        }
        printf("[+]Client connect successfully!");
        // 創建一個1024格空間的buffer array，並將其清成0
        char buffer[1024];
        bzero(buffer, 1024);
        // server socket將收到的data放進buffer裡面，並回傳收到的位元組數
        length = recv(new_server_socket,buffer,BUFFER_SIZE,0);
        // 若回傳的位元組數小於0則錯誤
        if (length < 0)
        {
             printf("Server recieve data failed!\n");
             break;
        }
        // 創建一個1024大小的array，用來存放client想要下載的檔案名稱
        char file_name[1024];
        // 將array清空
        bzero(file_name, 1024);
        // 將剛剛收到後放在buffer的檔案名稱複製進入file_name array
        strncpy(file_name, buffer, 1024);
        // 創建指向要讓client端下載的檔案指標
        FILE * fp = fopen(file_name,"r");
        // 若該指標為NULL，即代表該檔案不存在
        if(fp == NULL)
        {
            printf("File: %s not found\n", file_name);
        }
        else
        {
            // 若檔案存在，就將buffer清空，準備傳送給client端
            bzero(buffer, BUFFER_SIZE);
            // 宣告一個整數型態的變數，用來接收fread回傳值
            int file_block_length = 0;
            // fread的回傳值為成功有效的讀取fp指向的檔案的元素個數
            while( (file_block_length = fread(buffer,sizeof(char),BUFFER_SIZE,fp))>0)
            {
                // 若元素個數至少有一個即開始傳送
                // 發送buffer中的字串至new_server_socket
                if(send(new_server_socket,buffer,file_block_length,0)<0)
                {
                    printf("Send file: %s failed\n", file_name);
                    break;
                }
                // 將buffer清空
                bzero(buffer, BUFFER_SIZE);
            }
            // 關閉指向要傳輸檔案的指標
            fclose(fp);
            printf("File: %s transfer finished\n",file_name);
         }
         // 關閉與client 端socket的連接
         close(new_server_socket);
    }
    // 關閉server端監聽所使用的socket
    close(server_socket);
    return 0;
}

