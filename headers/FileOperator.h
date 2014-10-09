#ifndef FILEOPERATOR_H
#define FILEOPERATOR_H

#include <stdio.h>

#define WRITE_CREATE_MODE "a+b"

#include <fcntl.h>
#include <string>

class FileOperator
{
    public:
        FileOperator();
        ~FileOperator();
        bool Open(const char* fileName,const char* option);
        int WriteToFile(const std::string& buffer);
        int ReadFromFile(std::string& buffer);
        void Close();

    private:
        FILE* filePtr;
};

#endif