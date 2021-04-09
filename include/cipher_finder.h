#pragma once

#include <deque>
#include <fstream>
#include <optional>

namespace cipher {

/* Класс CipherFinder. Реализует алгоритм поиска первого слова,
 * который является частью данного ключа.
 * Алгоритм реализации см. в README.md
 */
class CipherFinder {
public:
    explicit CipherFinder(std::string&& file_name);
    std::optional<size_t> GetFirstKeyWord(std::string_view key);

private:
    void WarmUp(std::string_view key);

    void AddWordToBuffer(std::string_view new_word);
    void RemoveWordFromBuffer();

    std::optional<size_t> ContinueSearch();
    void FillBuffer();
    void UpdateBuffer(std::string_view new_word);

    [[nodiscard]] bool CheckBuffer() const;

private:
    std::deque<char> buffer_;
    std::string file_name_;
    std::string_view current_key_;

    std::ifstream file_stream_;
};

}  // namespace cipher