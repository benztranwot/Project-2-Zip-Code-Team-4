#ifndef POSTAL_LIST_H
#define POSTAL_LIST_H

#include "HeaderRecordPostalCodeItem.h"
#include <vector>

using namespace std;

class HeaderRecordPostalList
{
private:
    vector<HeaderRecordPostalCodeItem> items; /**< Internal storage for postal code entries */

public:
    // Constructors
    HeaderRecordPostalList() = default;

    /**
     * @brief Add a HeaderRecordPostalCodeItem to the list.
     * @param item The HeaderRecordPostalCodeItem to be added.
     */
    void addItem(const HeaderRecordPostalCodeItem &item);

    /**
     * @brief Get a HeaderRecordPostalCodeItem by index.
     * @param index The index of the item to retrieve.
     * @return The HeaderRecordPostalCodeItem at the specified index.
     * @throws out_of_range if the index is invalid.
     */
    HeaderRecordPostalCodeItem getItem(int index) const;

    /**
     * @brief Find a HeaderRecordPostalCodeItem by its ZIP code.
     * @param zip The ZIP code to search for.
     * @return A pointer to the HeaderRecordPostalCodeItem if found, nullptr otherwise.
     * @note The returned pointer is valid as long as the HeaderRecordPostalList object exists and is not modified.
     */
    const HeaderRecordPostalCodeItem *findByZip(int zip) const;

    /**
     * @brief Get the number of items in the list.
     * @return The number of HeaderRecordPostalCodeItem objects in the list.
     */
    int size() const;

    /**
     * @brief Print all HeaderRecordPostalCodeItems in the list.
     * Each item's information is printed followed by a separator line.
     * @note The order of items is the same as the order they were added.
     */
    void printAll() const;

    /**
     * @brief Print HeaderRecordPostalCodeItems sorted by ZIP code.
     * Each item's information is printed followed by a separator line.
     * @note Items are sorted in ascending order by ZIP code.
     */
    void printSortedByZip() const;

    /**
     * @brief Print HeaderRecordPostalCodeItems sorted by state and then by ZIP code.
     * Each item's information is printed followed by a separator line.
     * @note Items are sorted first by state (alphabetically) and then by ZIP code (numerically) within each state.
     */
    void printSortedByState() const;
};

#include "HeaderRecordPostalList.cpp"
#endif