#include <iostream>
#include "C:\DataStructures\Lab03\Lab03\include\array_list.h"

int main()
{
    // The basic test program (for floats)
    ssuds::ArrayList<float> float_list;
    float_list.append(2.1f);
    float_list.append(3.6f);
    std::cout << float_list.size() << std::endl;                  // 2
    std::cout << float_list[0] << std::endl;                      // 2.1
    std::cout << float_list[1] << std::endl;                      // 3.6
    float_list.insert(1.8f, 0);
    float_list.insert(4.2f, 3);
    float_list.insert(2.0f, 1);
    for (int i = 0; i < float_list.size(); i++)                   // 1.8 2 2.1 3.6 4.2
        std::cout << float_list[i] << " ";
    std::cout << std::endl;
    float_list.append(2.0f);                                      // <= a capacity increase should be triggered here
    float_list.append(2.0f);
    for (int i = 0; i < float_list.size(); i++)                   // 1.8 2 2.1 3.6 4.2 2 2
        std::cout << float_list[i] << " ";
    std::cout << std::endl;
    std::cout << float_list.remove_all(2.0f) << std::endl;        // 3 <= a capacity decrease should be triggered here
    for (int i = 0; i < float_list.size(); i++)                   // 1.8 2.1 3.6 4.2
        std::cout << float_list[i] << " ";
    std::cout << std::endl;

    // Test the stream operator
    std::cout << float_list << std::endl;                         // [1.8, 2.1, 3.6, 4.2]

    // Test the = operator
    ssuds::ArrayList<float> float_list_copy = float_list;         // (will call the copy-constructor)
    std::cout << float_list_copy << std::endl;                    // [1.8, 2.1, 3.6, 4.2]
    float_list_copy.remove(1);
    std::cout << float_list_copy << std::endl;                    // [1.8, 3.6, 4.2]
    std::cout << float_list << std::endl;                         // [1.8, 2.1, 3.6, 4.2]

    float_list_copy = float_list;                                 // (will call the = operator)
    std::cout << float_list_copy << std::endl;                    // [1.8, 2.1, 3.6, 4.2]

    // Use iterator to traverse the ArrayList
    for (auto it = float_list.begin(); it != float_list.end(); ++it)
    {
        std::cout << *it << " ";
    }

    // Just for the sake of argument -- make sure it'll work with custom-types too
    //std::vector<Foo> foo_vec;
    //foo_vec.push_back(Foo(5, "Bob"));
    ssuds::ArrayList<testing::Foo> foo_test;
    foo_test.append(testing::Foo(5, "Bob"));
    foo_test.insert(testing::Foo(4, "Abe"), 0);
    foo_test.append(testing::Foo(7, "Carl"));
    std::cout << foo_test << std::endl;                           // [<FOO:4:Abe>, <FOO:5:Bob>, <FOO:7:Carl>]

    testing::InitGoogleTest();
    return RUN_ALL_TESTS();

}
