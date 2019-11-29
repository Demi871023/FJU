#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444
#define HELLO_WORLD_SERVER_PORT 6666
#define LENGTH_OF_LISTEN_QUEUE 20
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512

int main()
{
    int sockfd, ret;
    // 宣告一個serverAddr來設定server socket的資訊
    struct sockaddr_in serverAddr;
    int newSocket;
    struct sockaddr_in newAddr;
    socklen_t addr_size;

    char buffer[1024];
    pid_t childpid;
    // 創建一個socket，使用IPv4、TCP
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // 若回傳值小於0，即創建錯誤
    if(sockfd < 0){
        printf("[-]Error in connection.\n");
        exit(1);
    }
    printf("[+]Server Socket is created.\n");
    // 先將serverAddr清空
    memset(&serverAddr, '\0', sizeof(serverAddr));
    // 設定成IPv4
    serverAddr.sin_family = AF_INET;
    // 將server port number設為4444
    serverAddr.sin_port = htons(PORT);
    // 將server address設置成loopback address 127.0.0.1
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // 將設定好的server address和port number等資訊綁在server socket上
    ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    // 若bind回傳值小於0的時候即代表發生錯誤
    if(ret < 0){
    	printf("[-]Error in binding.\n");
    	exit(1);
    }
    printf("[+]Bind to port %d\n", 4444);
    // server socket監聽是否有連線請求，且規定最多有五個client連至server
    if(listen(sockfd, 5) == 0)
    {
    		printf("[+]Listening....\n");
    }
    else
    {
		    printf("[-]Error in binding.\n");
    }
    // 無限迴圈，使server socket能一直運作
    int num = 1;
    while(1){
    	// 接收client端的連線，並產出新的socket，專與此client溝通
    	newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
    	// 若 accept 回傳的數值小於0，即server socket 接收連線請求發生錯誤
    	if(newSocket < 0){
    		exit(1);
    	}
    	printf("Client %d connection accepted from %s:%d\n", num++, inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
    	// fork 將當前的 process分支出另一個 process，並回傳子程序的pid 0
    	if((childpid = fork()) == 0){
    		close(sockfd);
            while(1){
                // 從newSocket中取得client端輸入的字串並放置於buffer
                recv(newSocket, buffer, 1024, 0);
              	// 比較buffer和字串exit;，若回傳值為0，則兩者字串相同
                if(strcmp(buffer, "exit;") == 0){
                // 若client輸入的是exit;，則break結束與該client的連線
                    printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
                    break;
                }
                // 比較buffer和字串download;，若回傳值為0則兩者字串相同
                else if(strcmp(buffer, "download;") == 0){
                    // 創建一個指向要下載檔案的指標
                    FILE * fp = fopen("HW2.txt","r");
                    // 若fp回傳為等於NULL，即為找不到此檔 
                    if(fp == NULL)
                    {
                        printf("File:HW2.txt Not Found\n");
                    }
                    else
                    {
                        // 將buffer清空
                        bzero(buffer, 1024);
                        // 宣告一個整數型態的變數，用來接收fread回傳值
                        int file_block_length = 0;
                        // fread的回傳值為成功有效的讀取fp指向的檔案的元素個數
                        while( (file_block_length = fread(buffer,sizeof(char),1024,fp))>0)
                        {	
    					    if(send(newSocket,buffer,file_block_length,0)<0)
                            {
                                // 若元素個數至少有一個即開始傳送
                                // 發送buffer中的字串至newSocket
                                // 若將buffer的東西傳送出去回傳的數值小於 0，即發生錯誤
                                printf("Send File:HW2.txt Failed\n");
                                break;
                            }
                            bzero(buffer, 1024);
                        }
                        // 關閉指向要寫入的檔案的檔案指標
                        fclose(fp);
                        printf("File:HW2 Transfer Finished\n");
                        break;
                    }		
                }
            }
	   }
    }
    // 關閉用來與該client溝通及處理的socket
    close(newSocket);
    return 0;
}

