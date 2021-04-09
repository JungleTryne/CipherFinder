#include <iostream>
#include <cipher_finder.h>

[[noreturn]] void Run(std::string filename) {
    cipher::CipherFinder finder(std::move(filename));
    while (true) {
        std::cout << "Введите шифр, завершение программы -- Ctrl+C";
        std::string key;
        std::cin >> key;
        auto result = finder.GetFirstKeyWord(key);

        if (result.has_value()) {
            std::cout << "Ответ:" << result.value() << std::endl;
        } else {
            std::cout << "Не нашли :(" << std::endl;
        }
    }
}

int main() {
    std::string filename;
    std::cout << "Введите путь к файлу, в котором лежит текст";
    std::cin >> filename;
    Run(std::move(filename));
}
