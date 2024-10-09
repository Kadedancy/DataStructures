#pragma once
#include <algorithm>
#include <array_list.h>

namespace ssuds
{
	enum class SortOrder { ASCENDING, DESCENDING };

	template<class T>
	unsigned int bubblesort(ArrayList<T>& arr, SortOrder order)
	{
		int n = arr.size();
		unsigned int swapAmount = 0;

		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < n - i - 1; j++)
			{
				bool shouldSwap;

				if (order == SortOrder::ASCENDING) 
				{
					shouldSwap = (arr[j] > arr[j + 1]);
				}
				else
				{
					shouldSwap = (arr[j] < arr[j + 1]);
				}
				if (shouldSwap)
				{
					std::swap(arr[j], arr[j + 1]);
					swapAmount++;
				}
			}
		}
		return swapAmount;
	}

	template <class T>
	void shuffle(ArrayList<T>& arr)
	{
		int n = arr.size();
		std::srand(static_cast<unsigned int>(std::time(0)));

		for (int i = n -1; i > 0; i--)
		{
			int j = std::rand() % (i + 1);
			std::swap(arr[i],arr[j]);
		}
	}

	template <class T>
	int binarySearch(const ArrayList<T>& arr, const T& x, unsigned int& comparisons) 
	{
		int low = 0;
		int high = arr.size() - 1;

		while (low <= high) 
		{
			int mid = (high + low) / 2;
			comparisons++;
			if (arr[mid] == x)
			{
				return mid;
			}
			else if (arr[mid] > x)
			{
				high = mid -1;
			}
			else
			{
				low = mid + 1;
			}
		}
		return -1;
	}

	template<class T>
	unsigned int partition(ArrayList<T>& arr, int start, int end, SortOrder order, unsigned int& swaps)
	{
		int pivot = (start + end) / 2;
		T pivot_value = arr[pivot];

		std::swap(arr[pivot], arr[end]);

		int count = start;

		for (int i = start; i < end; i++)
		{
			if ((order == SortOrder::ASCENDING && arr[i] <= pivot_value) ||
				(order == SortOrder::DESCENDING && arr[i] >= pivot_value))
			{
				swaps++;
				std::swap(arr[i], arr[count]);
				count++;
			}
		}
		std::swap(arr[count], arr[end]);
		swaps++;
		return count;
	}
	template <class T>
	void quickSort(ArrayList<T>& arr, int start, int end, SortOrder order, unsigned int& swaps)
	{
		while (start < end)
		{
			int pivotIndex = partition(arr, start, end, order, swaps);

			if (pivotIndex - start < end - pivotIndex)
			{
				quickSort(arr, start, pivotIndex - 1, order, swaps);
				start = pivotIndex + 1;
			}
			else
			{
				quickSort(arr, pivotIndex + 1, end, order, swaps);
				end = pivotIndex - 1;
			}
		}
	}
}