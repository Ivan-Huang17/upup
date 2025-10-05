#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <vector>
#include <mutex>
#include "fileSplitter.h"

#define PORT 8080
#define BUFFER_SIZE 1024
#define NUM_TEXTS 3

std::mutex mtx;

// 线程参数结构体
struct ThreadArgs
{
    int socketFd;
    int threadId;
    const char *text;
};

// 发送线程函数
void *sendData(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;
    int socketFd = args->socketFd;
    int threadId = args->threadId;
    const char *text = args->text;

    // 在数据头部添加threadId标识
    char sendBuffer[BUFFER_SIZE + sizeof(int)];
    *((int *)sendBuffer) = threadId;
    std::strcpy(sendBuffer + sizeof(int), text);

    send(socketFd, sendBuffer, std::strlen(text) + sizeof(int), 0);
    std::cout << "Server thread " << threadId << " sent data.\n";
    pthread_exit(NULL);
}

// 接收线程函数
void *receiveData(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;
    int socketFd = args->socketFd;
    int threadId = args->threadId;
    char buffer[BUFFER_SIZE + sizeof(int)];
    int bytesRead = recv(socketFd, buffer, sizeof(buffer), 0);
    if (bytesRead <= 0)
    {
        std::cerr << "Receive failed.\n";
        pthread_exit(NULL);
    }

    int receivedThreadId = *((int *)buffer);
    if (receivedThreadId == threadId)
    {
        std::string receivedData(buffer + sizeof(int));
        std::cout << "Server thread " << threadId << " received: " << receivedData << "\n";
    }
    else
    {
        std::cout << "Server thread " << threadId << " received unexpected data.\n";
    }

    pthread_exit(NULL);
}
void assignStrings(const std::vector<std::string> &strVec, char **charPtrArray)
{
    for (size_t i = 0; i < strVec.size(); ++i)
    {
        // 为每个字符指针分配足够的内存，包括字符串结束符 '\0'
        charPtrArray[i] = new char[strVec[i].size() + 1];
        // 将字符串从std::string复制到字符数组
        std::strcpy(charPtrArray[i], strVec[i].c_str());
    }
}

int main()
{
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // 创建socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        std::cerr << "Socket creation failed.\n";
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // 绑定socket
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        std::cerr << "Bind failed.\n";
        close(serverSocket);
        return 1;
    }

    // 监听连接
    if (listen(serverSocket, 5) == -1)
    {
        std::cerr << "Listen failed.\n";
        close(serverSocket);
        return 1;
    }

    std::cout << "Server is listening on port " << PORT << "...\n";

    // 接受客户端连接
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (clientSocket == -1)
    {
        std::cerr << "Accept failed.\n";
        close(serverSocket);
        return 1;
    }

    std::vector<pthread_t> sendThreads(NUM_TEXTS);
    std::vector<pthread_t> receiveThreads(NUM_TEXTS);
    std::vector<ThreadArgs> sendArgs(NUM_TEXTS);
    std::vector<ThreadArgs> receiveArgs(NUM_TEXTS);

    std::vector<std::string> res(3);
    res=fileSplitter("test.txt",3);
    for(int i=0;i<3;++i){
        std::cout<<res[i]<<std::endl;
    }
    char **texts = new char *[res.size()];
    assignStrings(res,texts);
    // const char *texts[NUM_TEXTS] = {
    //     "Text from server 1",
    //     "Text from server 2",
    //     "Text from server 3"};

    // 创建发送线程
    for (int i = 0; i < NUM_TEXTS; ++i)
    {
        sendArgs[i].socketFd = clientSocket;
        sendArgs[i].threadId = i;
        sendArgs[i].text = texts[i];
        pthread_create(&sendThreads[i], NULL, sendData, &sendArgs[i]);
    }

    // 创建接收线程
    for (int i = 0; i < NUM_TEXTS; ++i)
    {
        receiveArgs[i].socketFd = clientSocket;
        receiveArgs[i].threadId = i;
        pthread_create(&receiveThreads[i], NULL, receiveData, &receiveArgs[i]);
    }

    // 等待发送线程完成
    for (int i = 0; i < NUM_TEXTS; ++i)
    {
        pthread_join(sendThreads[i], NULL);
    }

    // 等待接收线程完成
    for (int i = 0; i < NUM_TEXTS; ++i)
    {
        pthread_join(receiveThreads[i], NULL);
    }

    close(clientSocket);
    close(serverSocket);
    return 0;
}
