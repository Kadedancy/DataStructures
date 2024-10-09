#include <gtest/gtest.h>
#include <array_list_utility.h>

TEST(BubbleSortSwapsTest, SortAscending)
{
    ssuds::ArrayList<int> arr = { 4, 2, 7, 1, 9, 5 };
    unsigned int swaps = ssuds::bubblesort(arr, ssuds::SortOrder::ASCENDING);
    EXPECT_EQ(swaps, 8);
}

TEST(BubbleSortSwapsTest, SortDescending)
{
    ssuds::ArrayList<int> arr = { 4, 2, 7, 1, 9, 5 };
    unsigned int swaps = ssuds::bubblesort(arr, ssuds::SortOrder::DESCENDING);
    EXPECT_EQ(swaps, 7);
}

TEST(QuickSortSwapsTest, SortAscending)
{
    ssuds::ArrayList<int> arr = { 4, 2, 7, 1, 9, 5 };
    unsigned int swaps = 0;
    ssuds::quickSort(arr, 0, arr.size() - 1, ssuds::SortOrder::ASCENDING, swaps);
    EXPECT_EQ(swaps, 8);
}

TEST(QuickSortSwapsTest, SortDescending)
{
    ssuds::ArrayList<int> arr = { 4, 2, 7, 1, 9, 5 };
    unsigned int swaps = 0;
    ssuds::quickSort(arr, 0, arr.size() - 1, ssuds::SortOrder::DESCENDING, swaps);
    EXPECT_EQ(swaps, 7);
}

TEST(ShuffleTest, CheckShuffling)
{
    ssuds::ArrayList<int> arr = { 1, 2, 3, 4, 5, 6 };
    ssuds::ArrayList<int> original = arr;
    ssuds::shuffle(arr);

    bool elementsChanged = false;
    for (unsigned int i = 0; i < arr.size(); ++i) 
    {
        if (arr[i] != original[i])
        {
            elementsChanged = true;
            break;
        }
    }

    EXPECT_TRUE(elementsChanged);
}

TEST(BinarySearchTest, FindElement)
{
    ssuds::ArrayList<int> arr = { 1, 2, 3, 4, 5, 6 };
    unsigned int comparisons = 0;
    int index = ssuds::binarySearch(arr, 3, comparisons);
    EXPECT_EQ(index, 2);
}