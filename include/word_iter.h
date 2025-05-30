#ifndef INCLUDE_WORD_ITER_H
#define INCLUDE_WORD_ITER_H

#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>

/**
 * @brief An iterator class for reading words from an input stream.
 */
class WordIterator {
   public:
    using iterator_category = std::input_iterator_tag;
    using value_type = std::string;
    using difference_type = std::ptrdiff_t;
    using pointer = const std::string*;
    using reference = const std::string&;
    /**
     * @brief Default constructor for WordIterator, initializes the end state.
     */
    WordIterator();
    /**
     * @brief Constructs a WordIterator that reads from the provided input stream.
     * @param is The input stream to read words from.
     */
    explicit WordIterator(std::istream& is);

    /**
     * @brief Dereference operator to get the current word.
     * @return A reference to the current word as a string.
     */
    reference operator*() const;

    /**
     * @brief Arrow operator to get a pointer to the current word.
     * @return A pointer to the current word as a string.
     */
    pointer operator->() const;

    /**
     * @brief Pre-increment operator to move to the next word.
     * @return A reference to the current WordIterator after incrementing.
     */
    WordIterator& operator++();

    /**
     * @brief Post-increment operator to move to the next word.
     * @return A copy of the current WordIterator before incrementing.
     */
    WordIterator operator++(int);

    /**
     * @brief Equality operator to compare two WordIterators.
     * @param other The other WordIterator to compare with.
     * @return True if both iterators are at the end.
     * @note All end iterators are considered equal.
     */
    bool operator==(const WordIterator& other) const;

    /**
     * @brief Inequality operator to compare two WordIterators.
     * @param other The other WordIterator to compare with.
     * @return True if the iterators are not equal (i.e., one is at the end and the other is not).
     */
    bool operator!=(const WordIterator& other) const;

   private:
    std::istream* _stream;
    std::string _current_word;
    bool _end_reached;
};

/**
 * @brief A class that provides an iterator interface for reading words from an input stream.
 * @note This class consumes the passed iterator; it should not be used after construction.
 */
class Words {
   public:
    /**
     * @brief Constructs a Words object that reads words from the provided input stream.
     */
    Words(std::istream& is);

    /**
     * @brief Returns an iterator to the beginning of the words in the stream.
     * @return A WordIterator pointing to the first word in the stream.
     */
    WordIterator begin();

    /**
     * @brief Returns an iterator to the end of the words in the stream.
     * @return A WordIterator that represents the end of the stream.
     */
    WordIterator end();

   private:
    std::istream& _is;
};

#endif  // INCLUDE_WORD_ITER_H
