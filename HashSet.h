#ifndef LAB7_HASHSET_H
#define LAB7_HASHSET_H
#include "LinkedList.h"
 
unsigned hashFunction(const string& item)
{
    unsigned hashIndex = 0;
    for (unsigned i = 0; i < item.size(); i++)
    {
        hashIndex *= 31;
        hashIndex += item[i];
    }
    return hashIndex;
}
 
template <typename ItemType>
 
class HashSet {
private:
 
    LinkedList<string>* table;
    int tableSize = 0;
    int itemsStored = 0;
 
 
public:
    HashSet()
    {
        tableSize = 0;
        table = new LinkedList<string>[tableSize];
    }
    ~HashSet()
    {
        delete[] table;
    }
 
    void add(const ItemType& item) {
 
        if (find(item)) {
            return;
        }
 
        else {
            if (tableSize == itemsStored) {
                rehash();
            }
            unsigned index = hashFunction(item) % tableSize;
            table[index].insert(table[index].getSize(),item);
            itemsStored++;
        }
 
    }
 
    void remove(const ItemType& item) {
        if(!find(item))
        {
            return;
        }
        else
        {
            unsigned index = hashFunction(item) % tableSize;
            table[index].remove(table[index].find(item));
            itemsStored--;
            if (itemsStored <= tableSize/2)
            {
                rehash();
            }
        }
    }
 
    bool find(const ItemType& item) {
 
        if (tableSize == 0) {
            return false;
        }
        unsigned index = hashFunction(item) % tableSize;
        if (itemsStored == 0)
        {
            return false;
        }
        else if (table[index].itemExists(item))
        {
            return true;
        }
        else {
            return false;
        }
 
 
    }
    void clear(){
        delete[] table;
        tableSize = 0;
        itemsStored = 0;
        table = new LinkedList<string>[tableSize];
        return;
    }
    void print(ofstream& out)
    {
        if (itemsStored == 0)
        {
            return;
        }
        int printed = 0;
        for (unsigned i = 0; i < tableSize; i++)
        {
            out << "hash " << i << ": ";
            for (unsigned j = 0; j < table[i].getSize(); j++)
            {
                if (table[i].getItem(j) != "-1") {
                    if (printed % 8 == 0 && printed >= 8) {
                        out << "\nhash " << i << ": " << table[i].getItem(j) << " ";
                    }
                    else {
                        out << table[i].getItem(j) << " ";
 
                    }
                    printed++;
                }
 
            }
            out << "\n";
            printed = 0;
        }
    }
    void rehash()
    {
        int old_size = tableSize;
        if (tableSize == itemsStored) {
            tableSize = tableSize * 2 + 1;
        }
 
        else if (itemsStored <= tableSize/2) {
            tableSize = tableSize / 2;
        }
            LinkedList<string>* newTable = new LinkedList<string>[tableSize];
            for (int i = 0; i < old_size; ++i)
            {
                int table_size = 0;
                table_size = table[i].getSize();
                if(table_size != 0) {
                    for (int j = 0; j < table_size; ++j) {
                            unsigned index = hashFunction(table[i].getItem(j)) % tableSize;
                            newTable[index].insert(newTable[index].getSize(), table[i].getItem(j));
 
                    }
                }
            }
            LinkedList<string>* temp = table;
            table = newTable;
            delete [] temp;
 
    }
};
#endif
