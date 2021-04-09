#include <cstring>
#include <cipher_finder.h>

namespace cipher {

CipherFinder::CipherFinder(std::string&& file_name)
    : file_name_(std::move(file_name)) {}

void CipherFinder::WarmUp(std::string_view key) {
    current_key_ = key;
    buffer_.clear();
}

std::optional<size_t> CipherFinder::GetFirstKeyWord(std::string_view key) {
    WarmUp(key);

    std::ifstream file(file_name_);
    FillBuffer(file);

    bool result = CheckBuffer(key);
    if (result) {
        return 0;
    }

    size_t counter = 1;
    std::string str_buffer;
    while (file >> str_buffer) {
        UpdateBuffer(str_buffer);
        if (CheckBuffer(key)) {
            return counter;
        }
        ++counter;
    }

    return std::nullopt;
}

void CipherFinder::FillBuffer(std::ifstream& file) {
    std::string str_buffer;

    size_t counter = 0;
    while (file >> str_buffer) {
        AddWordToBuffer(str_buffer);
        ++counter;

        if (counter == current_key_.size()) {
            break;
        }
    }
}

void CipherFinder::AddWordToBuffer(std::string_view str_buffer) {
    for (size_t i = 0; i < std::min(current_key_.size(), str_buffer.size()); ++i) {
        buffer_.push_back(str_buffer[i]);
    }
    for (size_t i = 0; i < current_key_.size() - std::min(current_key_.size(), str_buffer.size()); ++i) {
        buffer_.push_back(0);
    }
}

void CipherFinder::RemoveWordFromBuffer() {
    for (size_t i = 0; i < current_key_.size(); ++i) {
        buffer_.pop_front();
    }
}

void CipherFinder::UpdateBuffer(std::string_view str_buffer) {
    RemoveWordFromBuffer();
    AddWordToBuffer(str_buffer);
}

bool CipherFinder::CheckBuffer(std::string_view key) const {
    for (size_t i = 0; i < key.size(); ++i) {
        if (buffer_[i + i * key.size()] != key[i]) {
            return false;
        }
    }
    return true;
}

}  // namespace cipher

