#include "include/array_list.h"
#include <iostream>

int main()
{
	ssuds::ArrayList a;
	a.append("Bob");
	a.append("Sue");
	std::cout << a.size() << "\n";		// 2
	std::cout << a.get(1) << "\n";		// Sue
	a.insert("Johnny", 1);
	std::cout << a.size() << "\n";		//3
	std::cout << a.get(1) << "\n";		// Johnny
	a.remove(0);
	std::cout << a.size() << "\n";		// 2
	std::cout << a.get(1) << "\n";		// Sue
	a.remove_all("Johnny");
	std::cout << a.size() << "\n";		// 1
	std::cout << a.get(0) << "\n";		// Sue
	std::cout << a.find("Sue", 0);      // 0
}