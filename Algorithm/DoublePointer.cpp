//
//  DoublePointer.cpp
//  Practice
//
//  Created by iSteven on 2023/10/12.
//

#include "DoublePointer.hpp"

//bool increasingTriplet(vector<int>& nums) {
//    int left = 0, right = 1;
//    int length = (int)nums.size();
//    while (right < length) {
//        if (nums[right] <= nums[right-1]) {
//            left = right;
//        }
//        if (right - left >= 2) {
//            return true;
//        }
//        right++;
//    }
//
//    return false;
//}

int removeDuplicates(vector<int>& nums) {
    int size = (int)nums.size();
    if (size <= 1) {
        return size;
    }
    
    int left = 0, right = 1;
    while (right < size) {
        // 不相等，下个赋右值
        if (nums[right] != nums[left]) {
            left++;
            nums[left] = nums[right];
        }
        right++;
    }
    return left+1;
}

int maxArea(vector<int>& height) {
    int size = (int)height.size();
    if (size <= 1) {
        return 0;
    }
    int left = 0, right = size-1;
    int maxArea = 0;
    while (left < right) {
        // 当前区间面积
        int area = min(height[left], height[right]) * (right - left);
        
        // 替换最大
        maxArea = max(maxArea, area);
        
        // 移动区间（边界小的移动）
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    return maxArea;
}

vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> ans;
    int size = (int)nums.size();
    if (size < 3) {
        return ans;
    }
    
    sort(nums.begin(), nums.end());
    
    for (int i = 0; i<size; i++) {
        // [0, 0, 0] 也可以，起始值大于0，和不可能等于0
        if (nums[i] > 0) {
            break;
        }
        
        // 与前一个值相同，直接跳过
        if (i>0 && nums[i] == nums[i-1]) {
            continue;
        }
        
        int left = i+1, right = size-1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0) {
                ans.push_back({nums[i], nums[left], nums[right]});
                // 与前一个值相同，直接跳过
                while (left < right && nums[left] == nums[left+1]) {
                    left++;
                }
                // 与前一个值相同，直接跳过
                while (left < right && nums[right] == nums[right-1]) {
                    right--;
                }
                left++;
                right--;
            } else if (sum > 0){
                right--;
            } else {
                left++;
            }
        }
    }
    
    return ans;
}

int minSubArrayLen(int target, vector<int>& nums) {
    int size = (int)nums.size();
    int left = 0, right = 0;
    int sum = 0, min_cnt = INT_MAX;
    while (right < size) {
        sum += nums[right];
        while (sum >= target) {
            min_cnt = min(min_cnt, right-left+1);
            sum -= nums[left];
            left++;
        }
        right++;
    }
    
    if (min_cnt == INT_MAX) {
        return 0;
    }
    return min_cnt;
}



