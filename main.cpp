#include <iostream>
#include <cipher_finder.h>

int main() {
    cipher::CipherFinder finder("text.txt");
    std::cout << finder.GetFirstKeyWord("Lpl").value();
    return 0;
}
