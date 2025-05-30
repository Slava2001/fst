#ifndef INCLUDE_INVERTED_INDEX_H
#define INCLUDE_INVERTED_INDEX_H

#include <map>
#include <string>
#include <vector>

#include "types.h"

#ifndef TEST_FRIENDS
#define TEST_FRIENDS
#endif

/**
 * @brief This structure represents an entry in the inverted index, containing a document ID and the
 * count of a specific word in that document.
 */
struct Entry {
    DocId doc_id;
    size_t count;

    /**
     * @brief Constructs an Entry with the given document ID and word count.
     * @param id The document ID.
     * @param cnt The count of the word in the document.
     */
    Entry(DocId id, size_t cnt);
    bool operator==(const Entry& other) const;
    bool operator!=(const Entry& other) const;
};

/**
 * @brief Inverted index class for managing a collection of documents and their word frequencies.
 */
class InvertedIndex {
   public:
    /**
     * @brief Default constructor for InvertedIndex.
     */
    InvertedIndex() = default;

    /**
     * @brief Constructs an InvertedIndex from files.
     * @param files A vector of file paths to read documents from.
     * @return An InvertedIndex object populated with documents from the specified files.
     */
    static InvertedIndex FromFiles(const std::vector<std::string>& files);

    /**
     * @brief Updates the document base with a new set of documents.
     * @param doc The document index to update.
     * @param words A map containing unique words and their counts in the documents.
     * @note This method will replace the existing document at the specified index.
     */
    void UpdateDocumentBase(DocId doc, std::map<std::string, size_t> words);

    /**
     * @brief Get word count for a specific word in each document.
     * @param word The word to search for in the documents.
     * @return A vector of Entry objects containing the document ID and count of the word in each
     * document.
     */
    std::vector<Entry> GetWordCount(const std::string& word) const;

    /**
     * @brief Get the frequency dictionary for a specific document.
     * @param id The document ID for which to retrieve the frequency dictionary.
     * @return A map where keys are words and values are their counts in the specified document.
     *         If the document ID does not exist, an empty map is returned.
     */
    std::map<std::string, size_t> GetDocWords(DocId id) const;

   private:
    std::map<DocId, std::map<std::string, size_t>> _docs;
    std::map<std::string, std::vector<Entry>> _freq_dictionary;
    TEST_FRIENDS;
};

#endif  // INCLUDE_INVERTED_INDEX_H
