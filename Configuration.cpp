//
// Created by HP on 27.03.2018.
//

#include "Configuration.h"

const std::string &Configuration::getFileReadToken() const {
    return fileReadToken;
}

const std::string &Configuration::getFileWriteSortedByLettersToken() const {
    return fileWriteSortedByLettersToken;
}

const std::string &Configuration::getFileWriteSortedByAmountToken() const {
    return fileWriteSortedByAmountToken;
}

const std::string &Configuration::getThreadsToken() const {
    return ThreadsToken;
}

const std::string &Configuration::getFileRead() const {
    return fileRead;
}

void Configuration::setFileRead(const std::string &fileRead) {
    Configuration::fileRead = fileRead;
}

const std::string &Configuration::getFileWriteSortedByLetters() const {
    return fileWriteSortedByLetters;
}

void Configuration::setFileWriteSortedByLetters(const std::string &fileWriteSortedByLetters) {
    Configuration::fileWriteSortedByLetters = fileWriteSortedByLetters;
}

const std::string &Configuration::getFileWriteSortedByAmount() const {
    return fileWriteSortedByAmount;
}

void Configuration::setFileWriteSortedByAmount(const std::string &fileWriteSortedByAmount) {
    Configuration::fileWriteSortedByAmount = fileWriteSortedByAmount;
}



std::string Configuration::parseString(std::string input) {
        char* endPtr;
        int i=0;
        while (input.at(i) != '\"'){
            i++;
            if(input.at(i)=='\"'){
                i++;
                std::string s(input, i, input.size());
                s.erase(s.size()-1, 1);
                return s;

            }
            if(i>=input.size()){
                std::cout<<"Error with parsing string "<<input
                << "\n.You missed \"param\"\nCorrect string must look like: "
                <<"File from:\"text.txt\"\nCorrect it and restart program"<<std::endl;
                throw EIO;
            }
        }

    }

std::ostream &operator<<(std::ostream &os, const Configuration &configuration) {
    os << "\nfileRead: "
       << configuration.fileRead << "\nfileWriteSortedByLetters: " << configuration.fileWriteSortedByLetters
       << "\nfileWriteSortedByAmount: " << configuration.fileWriteSortedByAmount << "\nThreads: "
       << configuration.Threads;
    return os;
}

int Configuration::getThreads() const {
    return Threads;
}

void Configuration::setThreads(int Threads) {
    Configuration::Threads = Threads;
}


