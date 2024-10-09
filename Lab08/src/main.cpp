#define DO_UNIT_TESTING 0
#include <iostream>
#if DO_UNIT_TESTING
#include <gtest/gtest.h>
#else
#include <unorderedMap.h>
#endif


int main()
{
#if DO_UNIT_TESTING
    // Invoke all google test fixtures we've registered
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
#else

    ssuds::UnorderedMap<std::string, int> map;

    map["John"] = 25;
    map["Alice"] = 30;
    map["Bob"] = 40;
    map["Emma"] = 35;

    for (const auto& pair : map) 
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    auto it = map.find("Bob");
    if (it != map.end()) 
    {
        std::cout << "Found key 'Bob' with value: " << it->second << std::endl;
    }
    else 
    {
        std::cout << "Key 'Bob' not found." << std::endl;
    }

    return 0;
#endif
}
