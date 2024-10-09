#define DO_TIMING_TESTS 1
#if DO_TIMING_TESTS
#include <array_list_utility.h>
#include <fstream>
#include <chrono>
#include <random>
#else
#include <gtest/gest.h>
#endif

int main()
{
#if DO_TIMING_TESTS
	// Part 4 code
	std::chrono::steady_clock::time_point start, end;

	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution(-5.0f, 25.0f);
	std::mt19937 mt(generator);

	std::ofstream fp("data.csv");
	fp << "TestSize, ShuffleTime, CopyTime, RecordTime, QSortTime, QSortOps, BubbleSortTime, BubbleSortOps, BinarySearchTime, BinarySearchOps, LinearSearchTime, LinearSearchOps\n";

	unsigned int test_size;
	for (test_size = 1000; test_size <= 250000; test_size += 5000)
	{
		if (test_size > 1000 && test_size < 10000)
		{
			test_size -= 1000;
		}
		std::cout << test_size << std::endl;
		ssuds::ArrayList<float> arr;

		for (unsigned int i = 0; i < test_size; ++i)
		{
			float num = distribution(mt);
			arr.append(num);
		}

		std::cout << "Started Shuffle" << std::endl;
		start = std::chrono::steady_clock::now();
		ssuds::shuffle(arr);
		end = std::chrono::steady_clock::now();
		auto ShuffleTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		std::cout << "Finished" << std::endl;

		std::cout << "Making copy" << std::endl;
		start = std::chrono::steady_clock::now();
		ssuds::ArrayList<float> copyarr(arr);
		end = std::chrono::steady_clock::now();
		auto CopyTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		std::cout << "Finished" << std::endl;

		std::cout << "Recording Value" << std::endl;
		start = std::chrono::steady_clock::now();
		float firstVal = arr[0];
		end = std::chrono::steady_clock::now();
		auto RecordTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		std::cout << "Finished" << std::endl;

		std::cout << "Started Quicksort" << std::endl;
		start = std::chrono::steady_clock::now();
		unsigned int qSortOps = 0;
		ssuds::quickSort(arr, 0, arr.size() - 1,ssuds::SortOrder::ASCENDING, qSortOps);
		end = std::chrono::steady_clock::now();
		auto qSortTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		std::cout << "Finished" << std::endl;

		std::cout << "Started Bubblesort" << std::endl;
		start = std::chrono::steady_clock::now();
		int bubbleSortOps = ssuds::bubblesort(copyarr, ssuds::SortOrder::ASCENDING);
		end = std::chrono::steady_clock::now();
		auto bubbleSortTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		std::cout << "Finished" << std::endl;

		std::cout << "Started BinarySearch" << std::endl;
		start = std::chrono::steady_clock::now();
		unsigned int binarySearchOps = 0;
		ssuds::binarySearch(arr, firstVal, binarySearchOps);
		end = std::chrono::steady_clock::now();
		auto binarySearchTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		std::cout << "Finished" << std::endl;

		std::cout << "Started linearSearch" << std::endl;
		start = std::chrono::steady_clock::now();
		unsigned int linearSearchOps = 0;
		arr.find(firstVal, linearSearchOps);
		end = std::chrono::steady_clock::now();
		auto linearSearchTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		std::cout << "Finished" << std::endl;


		fp << test_size << ", " << ShuffleTime << ", " << CopyTime << ", " << RecordTime << ", " << qSortTime << ", " << qSortOps << ", " << bubbleSortTime << ", " << bubbleSortOps << ", "
			<< binarySearchTime << ", " << binarySearchOps << ", " << linearSearchTime << ", " << linearSearchOps << "\n";
	}
	fp.close();
#else
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
#endif
}