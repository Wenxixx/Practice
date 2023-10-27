//
//  String.hpp
//  Practice
//
//  Created by iSteven on 2023/10/9.
//

#ifndef String_hpp
#define String_hpp

#include <stdio.h>
#include <string>
using namespace std;

// leetcode#151 反转字符串中的单词
string reverseWords(string s);

// leetcode#71 简化路径
string simplifyPath(string path);

// leetcode#5 最长回文子串
string longestPalindrome(string s);

// leetcode#3 无重复字符最长子串
int lengthOfLongestSubstring(string s);

// leetcode#6 Z字形变换
string zConvert(string s, int numRows);

/** 1. 两数之和 */
vector<int> twoSum(vector<int>& nums, int target);

/** 50. Pow(x, n)  */
double myPow(double x, int n);

/** 100. 三角形中最小路径之和 */
int minimumTotal(vector<vector<int>>& triangle);

/** 46. 全排列 */
vector<vector<int>> permute(vector<int>& nums);

// leetcode#394 字符串解码
string decodeString(string s);

int majorityElement(vector<int>& nums);

/** 12. 整数转罗马数字 */
string intToRoman(int num);

/** 13. 罗马数字转整数 */
int romanToInt(string s);

#endif /* String_hpp */
