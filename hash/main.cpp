#include <fstream>
#include <string>
#include <iostream>

#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include <cryptopp/md5.h>

//Функция хэширования сообщения
std::string Hash(const std::string& massage) // message входное сообщение
{
    CryptoPP::Weak::MD5 hash; //Создает экземпляр класса для вычисления хэша
    
    std::string resultHash; //результат хэширования
    
    CryptoPP::StringSource(massage, true,  new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(resultHash)))); 
    
    return resultHash;
}

//Функция чтения сообщения из файла
std::string ReadFile(std::string filename) 
{
    std::ifstream file(filename);
    std::string massage;
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла " << filename << ": " << strerror(errno) << std::endl;
        return ""; // Возвращаем пустую строку, если файл не может быть открыт
    }

    if (file.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "Файл пуст" << std::endl;
        file.close();
        return "";
    }

    while (std::getline(file, line)) 
    {
        massage += line + "\n";
    }

    file.close();
    return massage;
}

int main() {
    std::string filename = "input.txt"; 
    std::string message = ReadFile(filename);

    if (message.empty()) {
        // Обработка случая, когда файл пуст
        std::cout << "Файл пуст" << std::endl;
    } 
    else {
    std::string hashedMessage = Hash(message);

        // Выводим хэш сообщения
        std::cout << "Хэш сообщения: " << hashedMessage << std::endl;
    }

    return 0;
}
