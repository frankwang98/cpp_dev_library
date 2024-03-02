// algoutils.hpp

#include <vector>
#include <algorithm>
#include <unordered_map>

class AlgoUtils
{
public:
    /**
     * @brief 两数之和（数组中两数之和等于目标值，并返回索引）
    */
    static std::vector<int> twoSum(std::vector<int>& nums, int target)
    {
        std::unordered_map<int, int> numMap; // 存储数字及其索引
        std::vector<int> result;

        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i]; // 目标值与当前元素的差值

            // 查找差值是否存在于 map 中
            if (numMap.find(complement) != numMap.end()) {
                result.push_back(numMap[complement]); // 存在，则将索引存入结果集中
                result.push_back(i);
                break;
            }

            numMap[nums[i]] = i; // 将当前元素存入 map
        }

        return result;
    }

    /**
     * @brief 二分查找算法（返回目标值的索引）
    */
    static int binarySearch(const std::vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                return mid;  // 找到目标值，返回索引
            } else if (nums[mid] < target) {
                left = mid + 1;  // 目标值在右边，继续在右半部分查找
            } else {
                right = mid - 1;  // 目标值在左边，继续在左半部分查找
            }
        }

        return -1;  // 没有找到目标值，返回 -1
    }

};