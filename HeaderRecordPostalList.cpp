#include "HeaderRecordPostalList.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

/**
 * @brief Add a HeaderRecordPostalCodeItem to the list.
 * @param item The HeaderRecordPostalCodeItem to be added.
 */
void HeaderRecordPostalList::addItem(const HeaderRecordPostalCodeItem &item)
{
    items.push_back(item);
}

/**
 * @brief Get a HeaderRecordPostalCodeItem by index.
 * @param index The index of the item to retrieve.
 * @return The HeaderRecordPostalCodeItem at the specified index.
 * @throws out_of_range if the index is invalid.
 */
HeaderRecordPostalCodeItem HeaderRecordPostalList::getItem(int index) const
{
    if (index < items.size())
    {
        return items[index];
    }
    throw out_of_range("Index out of range in HeaderRecordPostalList::getItem");
}

/**
 * @brief Find a HeaderRecordPostalCodeItem by its ZIP code.
 * @param zip The ZIP code to search for.
 * @return A pointer to the HeaderRecordPostalCodeItem if found, nullptr otherwise.
 * @note The returned pointer is valid as long as the HeaderRecordPostalList object exists and is not modified.
 */
const HeaderRecordPostalCodeItem *HeaderRecordPostalList::findByZip(int zip) const
{
    for (const auto &item : items)
    {
        if (item.getZip() == zip)
        {
            return &item;
        }
    }
    return nullptr;
}

/**
 * @brief Get the number of items in the list.
 * @return The number of HeaderRecordPostalCodeItem objects in the list.
 */
int HeaderRecordPostalList::size() const
{
    return items.size();
}

/**
 * @brief Print all HeaderRecordPostalCodeItems in the list.
 * Each item's information is printed followed by a separator line.
 * @note The order of items is the same as the order they were added.
 */
void HeaderRecordPostalList::printAll() const
{
    for (int i = 0; i < items.size(); i++)
    {
        items[i].printInfo();
        cout << "-----------------------------------------------------------------------------------------------" << endl;
    }
}

/**
 * @brief Print HeaderRecordPostalCodeItems sorted by ZIP code.
 * Each item's information is printed followed by a separator line.
 * @note Items are sorted in ascending order by ZIP code.
 */
void HeaderRecordPostalList::printSortedByZip() const
{
    // Make a copy so original order is preserved
    vector<HeaderRecordPostalCodeItem> sortedItems = items;

    sort(sortedItems.begin(), sortedItems.end(),
         [](const HeaderRecordPostalCodeItem &a, const HeaderRecordPostalCodeItem &b)
         {
             return a.getZip() < b.getZip();
         });

    for (const auto &item : sortedItems)
    {
        item.printInfo();
        cout << "-----------------------------------------------------------------------------------------------" << endl;
    }
}

/**
 * @brief Print HeaderRecordPostalCodeItems sorted by state and then by ZIP code.
 * Each item's information is printed followed by a separator line.
 * @note Items are sorted first by state (alphabetically) and then by ZIP code (numerically) within each state.
 */
void HeaderRecordPostalList::printSortedByState() const
{
    // Copy items so we don’t change the internal order
    vector<HeaderRecordPostalCodeItem> sortedItems = items;

    sort(sortedItems.begin(), sortedItems.end(),
         [](const HeaderRecordPostalCodeItem &a, const HeaderRecordPostalCodeItem &b)
         {
             if (a.getState() == b.getState())
             {
                 return a.getZip() < b.getZip(); // secondary sort by ZIP
             }
             return a.getState() < b.getState();
         });

    for (const auto &item : sortedItems)
    {
        item.printInfo();
        cout << "-----------------------------------------------------------------------------------------------" << endl;
    }
}