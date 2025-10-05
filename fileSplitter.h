#ifndef FILESPLITTER_H
#define FILESPLITTER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

long long getFileSize(const std::string &filename)
{
    // 以二进制模式打开文件（避免文本模式下换行符转换影响大小计算）
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "无法打开文件：" << filename << std::endl;
        return -1;
    }

    // 1. 定位到文件末尾（ios::end 表示文件末尾位置）
    file.seekg(0, std::ios::end);

    // 2. 获取当前位置（即文件起始到末尾的偏移量，也就是文件大小）
    long long fileSize = file.tellg();

    // 3. 关闭文件（也可依赖 ifstream 析构自动关闭）
    file.close();

    return fileSize;
}
bool searchFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }
    file.close();
    return true;
}

std::vector<std::string> fileSplitter(const std::string &filename, int thread)
{
    if (!searchFile(filename))
    {
        std::cerr << "file doesn't exist";
        return {};
    }
    std::fstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "open filed or file is empty" << std::endl;
        return {};
    }
    std::vector<std::string> res;
    int fileSize = getFileSize(filename);
    int n = fileSize / thread;
    int remaining = fileSize % thread;

    for (int i = 0; i < thread; ++i)
    {
        //
        char buffer[n + (i == thread - 1 ? remaining : 0)];
        file.read(buffer, n + (i == thread - 1 ? remaining : 0));
        std::string meg(buffer, file.gcount());
        res.push_back(meg);
    }
    // 打印测试
    //  for (int i = 0; i < thread; ++i)
    //  {
    //      std::cout << "The NO." << i << " file is:" << res[i] << std::endl;
    //  }
    return res;
}
#endif