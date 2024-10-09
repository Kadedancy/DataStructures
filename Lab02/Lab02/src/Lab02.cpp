#include "C:\DataStructures\Lab02\Lab02\include\arraylist.h"
#include <sstream>
#include <iostream>

int main()
{
	ssuds::ArrayList<float> A;
	A.append(1.1f);
	A.append(2.2f);
	A.append(3.3f);

	std::cout << A << std::endl;			// [1.1, 2.2, 3.3]

	std::stringstream ss;
    ss << 42 << "abc" << 3.1f << A << std::endl;
	std::string s = ss.str();			// s now holds "42abc3.1[1.1, 2.2, 3.3]"

    ssuds::ArrayList<int> originalList;
    originalList.append(1);
    originalList.append(2);
    originalList.append(3);

    std::cout << "Original ArrayList: " << originalList << std::endl;

    ssuds::ArrayList<int> copiedList(originalList);

    std::cout << "Copied ArrayList: " << copiedList << std::endl;

    originalList.append(4);

    std::cout << "Modified Original ArrayList: " << originalList << std::endl;
    std::cout << "Copied ArrayList (unchanged): " << copiedList << std::endl;

    ssuds::ArrayList<int> assignedList;
    assignedList = originalList;

    std::cout << "Assigned ArrayList: " << assignedList << std::endl;

    testing::Foo foo;
    std::cout << "foo  Val: " << foo.getVal() << ", Str : " << foo.getStr() << std::endl;

    testing::Foo foo2(42, "Hello");
    std::cout << " foo2  Val: " << foo2.getVal() << ", Str: " << foo2.getStr() << std::endl;

    foo.setVal(10);
    foo.setStr("World");
    std::cout << "Updated foo  Val: " << foo.getVal() << ", Str: " << foo.getStr() << std::endl;


}