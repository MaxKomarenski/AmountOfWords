//
// Created by HP on 27.03.2018.
//

#ifndef AMOUNTOFWORDS_CONFIGURATION_H
#define AMOUNTOFWORDS_CONFIGURATION_H
#include <string>
#include <iostream>


class Configuration {

private:
    const std::string fileReadToken = "File from:";
    const std::string fileWriteSortedByLettersToken = "Out by a:";
    const std::string fileWriteSortedByAmountToken = "Out by n:";
    const std::string ThreadsToken = "Threads:";
    std::string fileRead;
    std::string fileWriteSortedByLetters;
    std::string fileWriteSortedByAmount;
    int  Threads = 1;

public:
    const std::string &getFileReadToken() const;

    const std::string &getFileWriteSortedByLettersToken() const;

    const std::string &getFileWriteSortedByAmountToken() const;

    const std::string &getThreadsToken() const;

    const std::string &getFileRead() const;

    void setFileRead(const std::string &fileRead);

    const std::string &getFileWriteSortedByLetters() const;

    void setFileWriteSortedByLetters(const std::string &fileWriteSortedByLetters);

    const std::string &getFileWriteSortedByAmount() const;

    void setFileWriteSortedByAmount(const std::string &fileWriteSortedByAmount);

    int getThreads() const;

    void setThreads(int Threads);


    std::string parseString(std::string input);

    friend std::ostream &operator<<(std::ostream &os, const Configuration &configuration);

};


#endif //AMOUNTOFWORDS_CONFIGURATION_H
