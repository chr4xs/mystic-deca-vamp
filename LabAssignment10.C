#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie node structure
struct TrieNode
{
    struct TrieNode* children[26];
    int count;
};

// Trie structure
struct Trie
{
    struct TrieNode* root;
};

// Function to create a new trie node
struct TrieNode* createTrieNode()
{
    struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    if (newNode)
    {
        for (int i = 0; i < 26; ++i)
            newNode->children[i] = NULL;
        newNode->count = 0;
    }
    return newNode;
}

// Function to initialize a trie structure
struct Trie* createTrie()
{
    struct Trie* newTrie = (struct Trie*)malloc(sizeof(struct Trie));
    if (newTrie)
    {
        newTrie->root = createTrieNode();
    }
    return newTrie;
}

// Function to insert a word into the trie
void insert(struct Trie* pTrie, char* word)
{
    if (!pTrie || !word)
        return;

    struct TrieNode* current = pTrie->root;
    for (int i = 0; word[i] != '\0'; ++i)
    {
        int index = word[i] - 'a';
        if (!current->children[index])
        {
            current->children[index] = createTrieNode();
        }
        current = current->children[index];
    }
    current->count++;
}

// Function to compute the number of occurrences of a word in the trie
int numberOfOccurrences(struct Trie* pTrie, char* word)
{
    if (!pTrie || !word)
        return 0;

    struct TrieNode* current = pTrie->root;
    for (int i = 0; word[i] != '\0'; ++i)
    {
        int index = word[i] - 'a';
        if (!current->children[index])
        {
            return 0;
        }
        current = current->children[index];
    }
    return current->count;
}

// Function to deallocate the trie structure
void deallocateTrieNode(struct TrieNode* node)
{
    if (node)
    {
        for (int i = 0; i < 26; ++i)
        {
            if (node->children[i])
                deallocateTrieNode(node->children[i]);
        }
        free(node);
    }
}

struct Trie* deallocateTrie(struct Trie* pTrie)
{
    if (pTrie)
    {
        deallocateTrieNode(pTrie->root);
        free(pTrie);
    }
    return NULL;
}

// Function to read the dictionary from a file and store words in pInWords array
// Returns the number of words in the dictionary
int readDictionary(char* filename, char** pInWords)
{
    int numWords = 0;
    FILE* file = fopen(filename, "r");
    if (file)
    {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file) != NULL)
        {
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n')
                buffer[len - 1] = '\0';
            pInWords[numWords] = strdup(buffer);
            numWords++;
        }
        fclose(file);
    }
    return numWords;
}

int main(void)
{
    char* inWords[256];

    // read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct Trie* pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }

    // parse line by line, and insert each word to the trie data structure
    char* pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }

    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");

    // Free memory allocated for words in the dictionary
    for (int i = 0; i < numWords; ++i)
    {
        free(inWords[i]);
    }

    return 0;
}
