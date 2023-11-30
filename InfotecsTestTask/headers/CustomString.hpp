#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <functional>

#define ERRMSG "ERROR: "
#define BUFF_SIZE 63

class CustomString{
private:
    std::string str;
    char chStr[BUFF_SIZE];

public:
    CustomString() {}

    virtual ~CustomString() {}

    inline std::string getUserString() { return this->str; }
    inline void setUserString(std::string newStr) { this->str = newStr; }

    inline char* getUserCharString() { return this->chStr; }
    inline void setUserCharString(char* newStr) { strcpy(this->chStr, newStr); }

    inline std::string isEmpty(std::string str){
        if(!str.empty()){
            return str;
        }
        else{
            std::cout << ERRMSG << "your string is empty." << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    inline bool isLE64Symbols(std::string str){
        if(str.length() <= BUFF_SIZE){
            return true;
        }
        else if(str.length() > BUFF_SIZE){
            std::cout << ERRMSG << "count of symbols is bigger than " << BUFF_SIZE + 1 << std::endl;

            return false;
        }
        else{
            std::cout << ERRMSG << "unknown error." << std::endl;
            return false;
        }
    }

    inline bool isLE64Symbols(const char* str){
        if(strlen(str) <= BUFF_SIZE){
            return true;
        }
        else if(strlen(str) > BUFF_SIZE){
            std::cout << ERRMSG << "count of symbols is bigger than " << BUFF_SIZE + 1 << std::endl;

            return false;
        }
        else{
            std::cout << ERRMSG << "unknown error." << std::endl;
            return false;
        }
    }

    inline bool isLE64Symbols(char* str){
        if(strlen(str) <= BUFF_SIZE){
            return true;
        }
        else if(strlen(str) > BUFF_SIZE){
            std::cout << ERRMSG << "count of symbols is bigger than " << BUFF_SIZE + 1 << std::endl;

            return false;
        }
        else{
            std::cout << ERRMSG << "unknown error." << std::endl;
            return false;
        }
    }

    inline bool isOnlyDigits(std::string str){
        if(!(std::all_of(str.begin(), str.end(), ::isdigit)))
            std::cout << ERRMSG << "your string does not consist only of digits." << std::endl;

        return std::all_of(str.begin(), str.end(), ::isdigit);
    }

    inline bool isOnlyDigits(const char* str){
        bool flag = false;

        for(size_t i = 0; i < strlen(str); i++){
            flag = isdigit(*(str + i));

            if(flag <= 0){
                std::cout << ERRMSG << "your string does not consist only of digits." << std::endl;

                return false;
            }
        }
        return flag;
    }

    inline bool isOnlyDigits(char* str){
        bool flag = false;

        for(size_t i = 0; i < strlen(str); i++){
            flag = isdigit(*(str + i));

            if(flag <= 0){
                std::cout << ERRMSG << "your string does not consist only of digits." << std::endl;

                return false;
            }
        }
        return flag;
    }

    std::string sortStringDescendingOrder(std::string str){
        char newSymbol = ' ';

        for(size_t i = 0; i < str.length() - 1; i++){
            for(size_t j = 0; j < str.length() - i - 1; j++){
                if(str[j] < str[j + 1]){
                    newSymbol = str[j];
                    str[j] = str[j + 1];
                    str[j + 1] = newSymbol;
                }
            }
        }

        return str;
    }

    void sortStringDescendingOrder(const char* str){
        char* newString = new char(strlen(str));
        strcpy(newString, str);

        char newSymbol = ' ';

        for(size_t i = 0; i < strlen(newString) - 1; i++){
            for(size_t j = 0; j < strlen(newString) - i - 1; j++){
                if(newString[j] < newString[j + 1]){
                    newSymbol = newString[j];
                    newString[j] = newString[j + 1];
                    newString[j + 1] = newSymbol;
                }
            }
        }

        delete[] newString;
        newString = nullptr;
    }

    void sortStringDescendingOrder(char* str){
        char* newString = new char(strlen(str));
        strcpy(newString, str);

        char newSymbol = ' ';

        for(size_t i = 0; i < strlen(newString) - 1; i++){
            for(size_t j = 0; j < strlen(newString) - i - 1; j++){
                if(newString[j] < newString[j + 1]){
                    newSymbol = newString[j];
                    newString[j] = newString[j + 1];
                    newString[j + 1] = newSymbol;
                }
            }
        }

        delete[] newString;
        newString = nullptr;
    }

    std::string evenElementsAreReplacedToKB(std::string str){
        for(size_t i = 0; i < str.length(); i++){
            if(str[i] % 2 == 0){
                std::replace(str.begin(), str.end(), str[i], 'K');
                str.insert(++i, "B");
            }
        }
        return str;
    }

    void evenElementsAreReplacedToKB(const char* str){
        size_t evenCount = 0, sizeOfStr = strlen(str);

        for(size_t i = 0; i < strlen(str); i++){
            if(*(str + i) % 2 == 0){
                evenCount++;
            }
        }

        size_t sizeOfNewStr = sizeOfStr + evenCount;
        char* newStr = new char[sizeOfNewStr];

        std::string newStringStr = str;
        strcpy(newStr, (char*)((evenElementsAreReplacedToKB(newStringStr)).c_str()));

        *(newStr + sizeOfNewStr) = '\0';

        delete[] newStr;
        newStr = nullptr;
    }

    char* evenElementsAreReplacedToKB(char* str){
        size_t evenCount { 0L };
        for(size_t i = 0; i < strlen(str); i++)
            if(*(str + i) % 2 == 0)
                evenCount++;

        char* newStr = (char*)calloc(strlen(str) + evenCount, sizeof(char));
        if(newStr == NULL){
            free(newStr);
            exit(EXIT_FAILURE);
        }

        strcpy(newStr, str);

        std::string newStringStr = newStr;
        strcpy(newStr, ((evenElementsAreReplacedToKB(newStringStr)).c_str()));

        return newStr;
    }

    std::string complexCheckAndModifyString(std::string str){
        std::string newStr = isEmpty(str);

        if(isOnlyDigits(newStr) && isLE64Symbols(newStr)){
            newStr = sortStringDescendingOrder(newStr);
            newStr = evenElementsAreReplacedToKB(newStr);
        }
        else exit(EXIT_FAILURE);

        return newStr;
    }

    inline std::string sumOfAllDigitsInStrToStdString(std::string str){
        unsigned int sum { 0 };
        size_t i { 0 };

        do{
            if(isdigit(str[i]) != 0){
                sum += str[i] - '0';
            }
            i++;
        }while(str[i] != '\0');

        return std::to_string(sum);
    }

    inline unsigned int sumOfAllDigitsInStrToUINT(std::string str){
        unsigned int sum { 0 };
        size_t i { 0 };

        while(str[i] != '\0'){
            if(isdigit(str[i]) != 0){
                sum += str[i] - '0';
            }
            i++;
        }

        return sum;
    }

    bool isGreater2SymbolsAndMultipleOf32(std::string str, unsigned int sum){
        if((str.length() > 2) && ((sum % 32) == 0)){
            std::cout << "We are have recieved your message." << std::endl;
            return true;
        }
        else if(str.length() < 3){
            std::cout << ERRMSG << "your sum have to consist of two symbols." << std::endl;
            return false;
        }
        else if((sum % 32) != 0){
            std::cout << ERRMSG << "your sum not divisible to 32." << std::endl;
        }
        else{
            std::cout << ERRMSG << "unknown error." << std::endl;
            return false;
        }

        return false;
    }

#ifdef __for_checking_the_correctness__
    void allInOneFunc(std::string str){
        str = complexCheckAndModifyString(str);
        std::string sum = sumOfAllDigitsInStrToStdString(str);
        unsigned int sumStr { sumOfAllDigitsInStrToUINT(str) };
        std::cout << sum << std::endl;
        isGreater2SymbolsAndMultipleOf32(sum, sumStr);
    }
#endif
};
