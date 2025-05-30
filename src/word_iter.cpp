#include "word_iter.h"
// #define LOG_LVL LogLevel::Debug
#include "logger.h"

WordIterator::WordIterator() : _stream(nullptr), _end_reached(true) {}

WordIterator::WordIterator(std::istream& is) : _stream(&is), _end_reached(false) { ++(*this); }

WordIterator::reference WordIterator::operator*() const { return _current_word; }

WordIterator::pointer WordIterator::operator->() const { return &_current_word; }

WordIterator& WordIterator::operator++() {
    log_enter();
    _current_word.clear();
    while (!_end_reached) {
        char tmp;
        _stream->get(tmp);
        if (_stream->bad()) {
            log_error("Stream error occurred: ", _stream->rdstate());
            throw std::ios_base::failure("Stream error occurred");
        } else if (_stream->eof()) {
            _end_reached = _current_word.empty();
            break;
        }

        if (std::isalpha(tmp)) {
            _current_word += tmp;
        } else {
            if (!_current_word.empty()) {
                break;
            }
        }
    }
    log_debug("Current word: '", _current_word,
              "', end reached: ", _end_reached ? "true" : "false");
    return *this;
}

WordIterator WordIterator::operator++(int) {
    WordIterator temp = *this;
    ++(*this);
    return temp;
}

bool WordIterator::operator==(const WordIterator& other) const {
    return _end_reached == other._end_reached;
}

bool WordIterator::operator!=(const WordIterator& other) const { return !(*this == other); }

Words::Words(std::istream& is) : _is(is) {}

WordIterator Words::begin() { return WordIterator(_is); }

WordIterator Words::end() { return WordIterator(); }
