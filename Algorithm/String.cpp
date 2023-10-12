//
//  String.cpp
//  Practice
//
//  Created by iSteven on 2023/10/9.
//

#include "String.hpp"
#include <vector>
#include <stack>

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


