#include <iostream>
#include <string>
#include "../lib_list/list.h"  // Assuming this is the correct path to the list library
#include "ITable.h"   // Assuming this is the correct path to the header file

int main() {
    std::cout << "UnorderedTable example:" << std::endl;
    UnorderedTable<int, std::string> unorderedTable;
    unorderedTable.pushback(1, "One");
    unorderedTable.pushback(2, "Two");
    unorderedTable.pushback(3, "Three");
    unorderedTable.printtable();

    unorderedTable.replace(2, "Two updated");
    std::cout << "After replacement:" << std::endl;
    unorderedTable.printtable();

    std::cout << "Popped element: Key: " << unorderedTable.popback().key << std::endl;
    unorderedTable.printtable();

    // Using UnorderedTableOnArray
    std::cout << "\nUnorderedTableOnArray example:" << std::endl;
    UnorderedTableOnArray<int, std::string> unorderedTableOnArray(5);
    unorderedTableOnArray.pushback(1, "One");
    unorderedTableOnArray.pushback(2, "Two");
    unorderedTableOnArray.pushback(3, "Three");
    unorderedTableOnArray.printtable();

    unorderedTableOnArray.replace(2, "Two updated");
    std::cout << "After replacement:" << std::endl;
    unorderedTableOnArray.printtable();

    std::cout << "Popped element: Key: " << unorderedTableOnArray.popup().key << std::endl;
    unorderedTableOnArray.printtable();

    return 0;
}
