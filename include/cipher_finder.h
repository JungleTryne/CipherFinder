#pragma once

#include <deque>
#include <fstream>
#include <optional>

namespace cipher {

class CipherFinder {
public:
    explicit CipherFinder(std::string&& file_name);
    std::optional<size_t> GetFirstKeyWord(std::string_view key);
private:
    void WarmUp(std::string_view key);

    void AddWordToBuffer(std::string_view new_word);
    void RemoveWordFromBuffer();

    void FillBuffer(std::ifstream& file);
    void UpdateBuffer(std::string_view new_word);
    [[nodiscard]] bool CheckBuffer(std::string_view key) const;

private:
    std::deque<char> buffer_;
    std::string file_name_;
    std::string_view current_key_;
};

}  // namespace cipher