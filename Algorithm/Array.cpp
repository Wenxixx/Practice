//
//  Array.cpp
//  Practice
//
//  Created by iSteven on 2023/10/12.
//

#include "Array.hpp"

vector<int> productExceptSelf(vector<int>& nums) {
    int size = (int)nums.size();
    if (size == 0) {
        return {};
    }
    vector<int> left(size), right(size, 0);
    left[0] = 1; right[size-1] = 1;
    for (int i = 1; i < size; i++) {
        left[i] = nums[i-1] * left[i-1];
    }
    
    for (int i = size - 2; i >=0; i--) {
        right[i] = nums[i+1] * right[i+1];
    }
    
    vector<int> ans(size);
    for (int i = 0; i< size; i++) {
        ans[i] = left[i] * right[i];
    }
    
    return ans;
}

bool increasingTriplet(vector<int>& nums) {
    int size = (int)nums.size();
    int s = INT_MAX, m = INT_MAX;
    
    for (int i = 0; i < size; i++) {
        if (nums[i] <= s) {
            s = nums[i];
        } else if (nums[i] <= m) {
            m = nums[i];
        } else {
            return true;
        }
    }
    return false;
}

int lengthOfLIS(vector<int>& nums) {
    int size = (int)nums.size();
    if (nums.size() == 0) {
        return 0;
    }
    
    vector<int> dp(size, 0);
    for (int i = 0; i < size; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    
    return *max_element(dp.begin(), dp.end());
}
