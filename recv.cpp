#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <vector>
#include <mutex>
#include <fstream>

#define PORT 8080
#define BUFFER_SIZE 1024
#define NUM_TEXTS 3

std::mutex mtx;
std::vector<std::string> receivedTexts;

// 线程参数结构体
struct ThreadArgs
{
    int socketFd;
    int threadId;
};

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
        std::cout << "Client thread " << threadId << " received: " << receivedData << "\n";
        std::lock_guard<std::mutex> lock(mtx);
        receivedTexts.emplace_back(receivedData);
    }
    else
    {
        std::cout << "Client thread " << threadId << " received unexpected data.\n";
    }

    pthread_exit(NULL);
}

int main()
{
    int socketFd;
    struct sockaddr_in serverAddr;

    // 创建socket
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd == -1)
    {
        std::cerr << "Socket creation failed.\n";
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 连接服务端
    if (connect(socketFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        std::cerr << "Connect failed.\n";
        close(socketFd);
        return 1;
    }

    std::vector<pthread_t> receiveThreads(NUM_TEXTS);
    std::vector<ThreadArgs> receiveArgs(NUM_TEXTS);

    // 创建接收线程
    for (int i = 0; i < NUM_TEXTS; ++i)
    {
        receiveArgs[i].socketFd = socketFd;
        receiveArgs[i].threadId = i;
        pthread_create(&receiveThreads[i], NULL, receiveData, &receiveArgs[i]);
    }

    // 等待接收线程完成
    for (int i = 0; i < NUM_TEXTS; ++i)
    {
        pthread_join(receiveThreads[i], NULL);
    }
    std::ofstream outputFile("received_texts.txt");
    if (!outputFile.is_open())
    {
        std::cerr << "Failed to open file for writing.\n";
        close(socketFd);
        return 1;
    }

    for (const auto &text : receivedTexts)
    {
        outputFile << text << std::endl;
    }

    outputFile.close();
    close(socketFd);
    return 0;
}
