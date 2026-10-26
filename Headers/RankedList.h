#ifndef RANKEDLIST_H
#define RANKEDLIST_H

INCLUDE <vector>
INCLUDE <stdexcept>
INCLUDE <algorithm>

TEMPLATE <typename T>
CLASS RankedList
PRIVATE :
items: vector<T>
STATIC CONSTEXPR MAX_SIZE = 5

PUBLIC :
    add(item : T, position : int)
    IF position < 1 OR position > MAX_SIZE
    THROW out_of_range("Position must be 1-5")
    IF item already exists in items(using == )
    THROW invalid_argument("Already ranked")
    IF position - 1 > items.size()
    THROW out_of_range("Fill earlier positions first")
    insert item at index(position - 1)
    IF items.size() > MAX_SIZE
    remove last item

    removeAt(position: int)
    IF position < 1 OR position > items.size() THROW out_of_range
    erase item at(position - 1)

    getAll() const->vector<T>
    size() const -> int
    clear()

#endif
