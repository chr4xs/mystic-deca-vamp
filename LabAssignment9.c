#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 100 // Choose an appropriate size for your hash table
#define PRIME_MULTIPLIER 131 // Choose a prime number for the hash function

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
    struct RecordType* next;
};

// HashType with linked lists
struct HashType
{
    struct RecordType* records[HASH_SIZE];
};

// Compute the hash function
int hash(int x)
{
    // A better hash function to distribute data evenly in the array
    return (x * PRIME_MULTIPLIER) % HASH_SIZE;
}

// parses input file to an integer array and stores records in the hash table using separate chaining
int parseData(char* inputFileName, struct HashType* pHash)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType* pRecord;
    struct RecordType* recordPool;
    int recordPoolSize = 0;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        for (i = 0; i < HASH_SIZE; ++i)
        {
            pHash->records[i] = NULL;
        }

        // Allocate memory for all records in one contiguous block
        recordPool = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
        if (recordPool == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }

        // Implement parse data block
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = &recordPool[recordPoolSize++];
            pRecord->next = NULL;

            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;

            int index = hash(pRecord->id);
            if (pHash->records[index] == NULL)
            {
                // If the slot is empty, add the record directly
                pHash->records[index] = pRecord;
            }
            else
            {
                // If the slot is already occupied, add the record to the linked list (separate chaining)
                struct RecordType* current = pHash->records[index];
                while (current->next != NULL)
                {
                    current = current->next;
                }
                current->next = pRecord;
            }
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct HashType* pHash)
{
    printf("\nRecords:\n");
    for (int i = 0; i < HASH_SIZE; ++i)
    {
        struct RecordType* current = pHash->records[i];
        while (current != NULL)
        {
            printf("\t%d %c %d\n", current->id, current->name, current->order);
            current = current->next;
        }
    }
    printf("\n\n");
}

int main(void)
{
    struct HashType hashTable;
    int recordSz = 0;

    recordSz = parseData("input.txt", &hashTable);
    printRecords(&hashTable);

    // Free the record pool
    free(hashTable.records[0]); // Since all records are stored in a contiguous block

    return 0;
}
