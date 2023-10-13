//
//  String.cpp
//  Practice
//
//  Created by iSteven on 2023/10/9.
//

#include "String.hpp"
#include <vector>
#include <stack>
#include <unordered_map>

string reverseWords(string s) {
    // 分割方法
    auto split = [](string s, char del) -> vector<string> {
        vector<string> list;
        string word;
        for (char c : s) {
            if (c != del) {
                word += c;
            } else {
                // 这步去除了多余空格
                if (!word.empty()) {
                    list.emplace_back(move(word));
                    word.clear();
                }
            }
        }
        //
        if (!word.empty()) {
            list.emplace_back(move(word));
        }
        return list;
    };
    
    // 分割出单词列表
    vector<string> list = split(s,' ');
    string ans;
    
    // 倒序组装新的字符串
    for (int i = (int)list.size() - 1; i >= 0; i--) {
        ans += list[i];
        if (i != 0) {
            ans += " ";
        }
    }
    return ans;
}

string simplifyPath(string path) {
    // 分割方法
    auto split = [](string& path, char del) -> vector<string> {
        vector<string> ans;
        string cur;
        for (char c : path) {
            if (c == del) {
                ans.push_back(move(cur));
                cur.clear();
            } else {
                cur += c;
            }
        }
        ans.push_back(move(cur));
        return ans;
    };
    
    // 分割出各级目录名称
    vector<string> names = split(path, '/');
    // 处理 .. 和 . （丢弃 或 返回上层目录）
    stack<string> sk;
    for (string &s : names) {
        if (s == "..") {
            if (!sk.empty()) {
                sk.pop();
            }
        } else if(!s.empty() && s != ".") {
            sk.push(s);
        }
    }
    //
    string res;
    if (sk.empty()) {
        res = "/";
    } else {
        while(!sk.empty()) {
            res += "/" + sk.top();
            sk.pop();
        }
    }
    return res;
}

int lengthOfPalindrom(string s, int left, int right) {
    while(left > 0 && right < s.size() && s[left] == s[right]) {
        left--;
        right++;
    }
    return (right - left -1);
}

string longestPalindrome(string s) {
    int maxLen = 0, start = 0;
    for (int i = 0; i < s.size(); i ++) {
        // 奇数
        int len1 = lengthOfPalindrom(s, i, i);
        if (len1 > maxLen) {
            maxLen = len1;
            start = i - maxLen / 2;
        }
        
        // 偶数
        int len2 = lengthOfPalindrom(s, i, i+1);
        if (len2 > maxLen) {
            maxLen = len2;
            start = i - maxLen / 2 + 1;
        }
    }
    
    return s.substr(start, maxLen);
}

int lengthOfLongestSubstring(string s) {
    int length = (int)s.size();
    if (length <= 1) {
        return length;
    }
    // abcadh
    unordered_map<char, int>hashmap;
    // left 始终指向不重复子串的前一个位置
    int left = -1, right = 0;
    int maxlen = 0;
    while (right < length) {
        char c = s[right];
        auto it = hashmap.find(c);
        if (it != hashmap.end()) {
            left = max(left, it->second);
        }
        hashmap[c] = right;
        maxlen = max(maxlen, right - left);
        right++;
    }
    return maxlen;
}

string zConvert(string s, int numRows) {
    if (numRows <= 1) {
        return s;
    }

    vector<string> vec(numRows, "");
    int flag = -1, index = 0;
    for (int i = 0; i<s.size(); i++) {
        if (i == 0 || i == numRows -1) {
            flag = -flag;
        }
        vec[index] += s[i];
        index += flag;
    }

    string ans;
    for (string str : vec) {
        ans += str;
    }
    return ans;
}

vector<int> twoSum(vector<int>& nums, int target) {
    // O(n2)
//    for (int i = 0; i < nums.size()-1; i++) {
//        for (int j = i + 1; j < nums.size(); j++) {
//            if (nums[i] + nums[j] == target) {
//                return {i, j};
//            }
//        }
//    }

    // O(n)
    unordered_map<int, int> has;
    for (int i = 0; i < nums.size(); i++) {
        int otherNum = target - nums[i];
        auto iter = has.find(otherNum);
        if (iter != has.end()) {
            return { iter->second, i };
        } else {
            has[nums[i]] = i;
        }
    }
    return {-1, -1};
}

double myPow(double x, int n) {
    if (x == 0) {
        return x;
    }

    double result = 1;
    for (int i = n; i != 0; i /= 2 ) {
        if (i % 2 != 0) {
            result *= x;
        }
        x *= x;
    }
    if (n < 0) {
        return 1.0 / result;
    }
    return result;
}

int minimumTotal(vector<vector<int>>& triangle) {
    int n = (int)triangle.size();
    vector<vector<int>> min_sum(n, vector<int>(n));
    min_sum[0][0] = triangle[0][0];
    for (int i = 1; i < n; ++i) {
        min_sum[i][0] = min_sum[i - 1][0] + triangle[i][0];
        for (int j = 1; j < i; ++j) {
            // 上一行临近两个值中最小值 + 当前值
            min_sum[i][j] = min(min_sum[i - 1][j - 1], min_sum[i - 1][j]) + triangle[i][j];
        }
        min_sum[i][i] = min_sum[i - 1][i - 1] + triangle[i][i];
    }
    int result = min_sum[n-1][0];
    for (int i = 1; i < n; i ++) {
        if (result > min_sum[n-1][i]) {
            result = min_sum[n-1][i];
        }
    }
    return result;
//    return *min_element(f[n - 1].begin(), f[n - 1].end());

}

void backtrack(vector<vector<int>>& res, vector<int>& out, int first, int length) {
    if (first == length) {
        res.push_back(out);
        return;
    }

    for (int i = first; i < length; i++) {
        swap(out[i], out[first]);
        backtrack(res, out, first + 1, length);
        swap(out[i], out[first]);
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> result;
    backtrack(result, nums, 0, (int)nums.size());
    return result;
}

int majorityElement(vector<int>& nums) {
        int length = (int)nums.size();
        unordered_map<int, int> hashMap;
        int result = -1;
        for (int i = 0; i < length; i++) {
            int num = nums[i];
            unordered_map<int, int>::iterator it = hashMap.find(num);
            if (it != hashMap.end()) {
                int count = (it->second);
                count++;
                if (count > length / 2) {
                    result = num;
                }
                hashMap[num] = count;
            } else {
                hashMap[num] = 1;
            }
        }
        return -1;
}

