#include "../src/algoutils/algoutils.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9};

    /* 排序 */
    std::sort(numbers.begin(), numbers.end());

    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    /* 交换位置 */
    int a = 60, b = 50;
    std::cout << "Before: " << "a = " << a << " and b = " << b << "\n";
    std::swap(a, b);
    std::cout << "After: " << "a = " << a << " and b = " << b;
    std::cout << std::endl;

    /* 翻转 */
    std::reverse(numbers.begin(), numbers.end());
    for (auto value : numbers)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    /* 两数之和 */
    int target1 = 2;
    std::vector<int> result = AlgoUtils::twoSum(numbers, target1);
    if (result.empty()) {
        std::cout << "No two numbers found that sum to the target." << std::endl;
    } else {
        std::cout << "Indices of the two numbers: " << result[0] << ", " << result[1] << std::endl;
    }

    /* 二分查找 */
    int target2 = 5;
    int index = AlgoUtils::binarySearch(numbers, target2);
    if (index != -1) {
        std::cout << "目标值 " << target2 << " 的索引为 " << index << std::endl;
    } else {
        std::cout << "没有找到目标值 " << target2 << std::endl;
    }

    return 0;
}