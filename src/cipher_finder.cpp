#include <cstring>
#include <cipher_finder.h>

namespace cipher {

/* Конструктор класса Cipher
 * Во время конструирования пытаемся открыть данный нам файл
 * с текстом.
 *
 * @param file_name: Название файла, в котором текст
 */
CipherFinder::CipherFinder(std::string&& file_name)
    : file_name_(std::move(file_name)) {
    file_stream_.open(file_name_);

    if (!file_stream_.is_open()) {
        throw std::runtime_error("File cannot open");
    }
}

/* Подготовительные работы для корректного исполнения алгоритма.
 * А именно очистка после возможного предыдущего исполнения
 * и установка нового ключа
 *
 * @param key: Новый ключ, по которому ищем шифр
 */
void CipherFinder::WarmUp(std::string_view key) {
    file_stream_.clear();
    file_stream_.seekg(0);
    current_key_ = key;
    buffer_.clear();
}

/* Основная функция нашего класса. Реализует алгоритм поиска слова,
 * с которого начинается данный нам шифр key. Детали работы алгоритма
 * ищите в README.md
 *
 * @param key: ключ (шифр)
 * @return Позицию слова в тексте, если оно есть, или std::nullopt, если
 * ответ найти не удалось
 */
std::optional<size_t> CipherFinder::GetFirstKeyWord(std::string_view key) {
    WarmUp(key);

    FillBuffer();

    bool result = CheckBuffer();
    if (result) {
        return 0;
    }

    return ContinueSearch();
}

/* Функция продолжения поиска нашего слова, с которого начинается шифр
 * выполняется после предварительного заполнения буффера
 */
std::optional<size_t> CipherFinder::ContinueSearch() {
    size_t counter = 1;
    std::string str_buffer;
    while (file_stream_ >> str_buffer) {
        UpdateBuffer(str_buffer);
        if (CheckBuffer()) {
            return counter;
        }
        ++counter;
    }

    return std::nullopt;
}

/* Функция заполнения буффера первыми current_key_
 * словами. При этом, если поток закрылся, то заполение
 * прекратится
 */
void CipherFinder::FillBuffer() {
    std::string str_buffer;
    str_buffer.resize(current_key_.size());

    size_t counter = 0;
    while (file_stream_ >> str_buffer) {
        AddWordToBuffer(str_buffer);
        ++counter;

        if (counter == current_key_.size()) {
            break;
        }
    }
}

/* Функция добавления слова в буффер. По условию задачи нам достаточно
 * добавлять не все слово, а лишь current_key.size() первых символов.
 * Это тут и происходит. При этом, если слово оказалось меньше, чем
 * current_key.size(), буффер дозаполняется нулями. Предполагается, что
 * исходный текст не будет иметь нулей
 *
 * @param str_buffer: слово для добавления
 */
void CipherFinder::AddWordToBuffer(std::string_view str_buffer) {
    for (size_t i = 0; i < std::min(current_key_.size(), str_buffer.size()); ++i) {
        buffer_.push_back(str_buffer[i]);
    }
    for (size_t i = 0; i < current_key_.size() - std::min(current_key_.size(), str_buffer.size()); ++i) {
        buffer_.push_back(0);
    }
}

/* Функция удаления слова и буффера. Просто удаляем current_key.size()
 * символов с начала deque
 */
void CipherFinder::RemoveWordFromBuffer() {
    for (size_t i = 0; i < current_key_.size(); ++i) {
        buffer_.pop_front();
    }
}

/* Убираем слово в начале, добавляем новое слово в конец,
 * как бы смещая буффер
 *
 * @param str_buffer: новое слово, которое нужно добавить
 */
void CipherFinder::UpdateBuffer(std::string_view str_buffer) {
    RemoveWordFromBuffer();
    AddWordToBuffer(str_buffer);
}

/* Проверка на то, что в буффере находятся все слова, определенные
 * буквы которых образуют шифр.
 */
bool CipherFinder::CheckBuffer() const {
    for (size_t i = 0; i < current_key_.size(); ++i) {
        if (buffer_[i + i * current_key_.size()] != current_key_[i]) {
            return false;
        }
    }
    return true;
}

}  // namespace cipher

