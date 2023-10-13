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

/**
 1. 两数之和
 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
 */
vector<int> twoSum(vector<int>& nums, int target);

/**
 50. Pow(x, n)
 实现 pow(x, n) ，即计算 x 的整数 n 次幂函数（即，xn ）。
 */
double myPow(double x, int n);

/**
100. 三角形中最小路径之和
 给定一个三角形 triangle ，找出自顶向下的最小路径和。
 每一步只能移动到下一行中相邻的结点上。相邻的结点 在这里指的是 下标 与 上一层结点下标 相同或者等于 上一层结点下标 + 1 的两个结点。也就是说，如果正位于当前行的下标 i ，那么下一步可以移动到下一行的下标 i 或 i + 1 。
 */
int minimumTotal(vector<vector<int>>& triangle);

/**
 46. 全排列
 给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。
 */
vector<vector<int>> permute(vector<int>& nums);

int majorityElement(vector<int>& nums);

#endif /* String_hpp */
