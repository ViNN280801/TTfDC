#include "CustomString.hpp"
#include <thread>
#include <mutex>

class ThreadsManipulations : public CustomString{
private:
    std::mutex* syncMutex;
    std::string buffer;

public:
    ThreadsManipulations() { this->syncMutex = new std::mutex; }
    virtual ~ThreadsManipulations() { this->syncMutex = nullptr; }

    inline std::string getBuffer() { return this->buffer; }
    inline void setBuffer(std::string newBuffer) { this->buffer = newBuffer; }

    std::string checkThreadWork(std::string str, ThreadsManipulations threadManipulation){
        std::lock_guard<std::mutex> lock(*syncMutex);
        threadManipulation.setUserString(str);
        str = threadManipulation.complexCheckAndModifyString(threadManipulation.getUserString());
        threadManipulation.setBuffer(str);

        return threadManipulation.getBuffer();
    }

    inline unsigned int sumThreadWork(ThreadsManipulations threadManipulation){
        std::lock_guard<std::mutex> lock(*syncMutex);
        std::string newBuffer = threadManipulation.getBuffer();
        threadManipulation.setBuffer(" ");

        return threadManipulation.sumOfAllDigitsInStrToUINT(newBuffer);
    }
};
