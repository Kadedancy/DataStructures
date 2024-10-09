#define DO_UNIT_TESTING 1
#include <iostream>
#if DO_UNIT_TESTING
#include <gtest/gtest.h>
#else
#include <orderedset.h>
#endif


int main()
{
#if DO_UNIT_TESTING
    // Invoke all google test fixtures we've registered
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
#else
    ssuds::OrderedSet<int> orderedSet;

    orderedSet.insert(5);
    orderedSet.insert(3);
    orderedSet.insert(7);
    orderedSet.insert(2);
    orderedSet.insert(4);
    orderedSet.insert(6);
    orderedSet.insert(8);
    orderedSet.insert(1);
    orderedSet.insert(9);

    std::cout << "Tree String Representation:" << std::endl;
    std::cout << orderedSet.tree_string() << std::endl;

    return 0;
#endif
}
