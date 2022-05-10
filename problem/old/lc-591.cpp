//
// Created by jyh on 1月22日.
//
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <sstream>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

typedef long long LL;

class Solution {
public:
    bool isValid(string code) {
        return parseClosedTag(code, 0) == code.size();
    }
private:
    // parseClosedTag 从 begin 下标开始读取一个 closed tag 并返回总长度。
    // 如果不合法，返回 -1
    int parseClosedTag(const string &code, int begin) {
        int len = 0;
        if (!isStartTag(code, begin)) {
            return -1;
        }
        int read = parseStartTag(code, begin);
        if (read < 0) {
            return -1;
        } else {
            len += read;
        }
        auto tagName = code.substr(begin + 1, read - 2);
        while (begin + len < code.size()) {
            if (code[begin + len] != '<') {
                len++;
                continue;
            }
            if (isStartTag(code, begin + len)) {
                auto ret = parseClosedTag(code, begin + len);
                if (ret < 0) {
                    return -1;
                } else {
                    len += ret;
                }
            } else if (isStartCData(code, begin + len)) {
                auto ret = parseCData(code, begin + len);
                if (ret < 0) {
                    return false;
                } else {
                    len += ret;
                }
            } else if (isEndTag(code, begin + len, tagName)) {
                return len + 3 + tagName.size();
            } else {
                return -1;
            }
        }
        return -1;
    }
    int parseCData(const string &code, int begin) {
        if (!isStartCData(code, begin)) {
            return -1;
        }
        int read = parseStartCData(code, begin);
        if (read < 0) {
            return -1;
        }
        auto pos = findEndCData(code, begin);
        if (pos < 0) {
            return -1;
        }
        read = parseEndCData(code, pos);
        if (read < 0) {
            return -1;
        }
        return pos + read - begin;
    }
    // parseStartTag 从 begin 下标开始读取一个 begin tag 并返回总长度。
    // <TAG_NAME>
    // 如果不合法，返回 -1
    int parseStartTag(const string &code, int begin) {
        int len = 0;
        if (code[begin + len] != '<') {
            return -1;
        } else {
            len++;
        }
        while (begin + len < code.size() && code[begin + len] != '>') {
            if (code[begin + len] < 'A' || code[begin + len] > 'Z') {
                return -1;
            }
            len++;
        }
        if (begin + len >= code.size() || code[begin + len] != '>') {
            return -1;
        } else {
            len++;
        }
        if (len < 2 + 1 || len > 2 + 9) {
            return -1;
        }
        return len;
    }
    int parseStartCData(const string &code, int begin) {
        const string pattern = "<![CDATA[";
        if (code.substr(begin, pattern.size()) == pattern) {
            return pattern.size();
        } else {
            return -1;
        }
    }
    int parseEndCData(const string &code, int begin) {
        const string pattern = "]]>";
        if (code.substr(begin, pattern.size()) == pattern) {
            return pattern.size();
        } else {
            return -1;
        }
    }
//    // isValidTagContent 检查code从begin到end是否是一个完整的 tag content。
//    // end 是最后一个内容的下一个。
//    // 如果合法，返回true。
//    bool isValidTagContent(const string &code, int begin, int end) {
//        for (int now = begin; now <= end;) {
//            if (now == end) {
//                return true;
//            }
//            if (isStartTag(code, now)) {
//                auto ret = parseClosedTag(code, now);
//                if (ret < 0) {
//                    return false;
//                } else {
//                    now += ret;
//                }
//            } else if (isStartCData(code, now)) {
//                auto ret = parseCData(code, now);
//                if (ret < 0) {
//                    return false;
//                } else {
//                    now += ret;
//                }
//            } else if (code[now] == '<') {
//                return false;
//            } else {
//                now++;
//            }
//        }
//        return false;
//    }
    // isEndTag 判断从code的begin开始是否是 tagName 的endTag
    bool isEndTag(const string &code, int begin, const string &tagName) {
        auto pattern = string("</") + tagName + ">";
        return code.substr(begin, pattern.size()) == pattern;
    }
    // findEndCData 从code的begin开始查找 cdata 的end，并返回end的首字节下标。
    // 如果没找到，返回-1
    int findEndCData(const string &code, int begin) {
        static const string pattern = "]]>";
        auto pos = code.find(pattern, begin);
        if (pos == code.size()) {
            return -1;
        } else {
            return pos;
        }
    }
    // isStartCData 判断code从begin开始是否是CData的开始标志
    bool isStartCData(const string &code, int begin) {
        static const string pattern = "<![CDATA[";
        return code.substr(begin, pattern.size()) == pattern;
    }
    // isStartTag 判断code从begin开始是否是startTag的开始标志
    bool isStartTag(const string &code, int begin) {
        return begin + 1 < code.size() && code[begin] == '<' && code[begin + 1] >= 'A' && code[begin + 1] <= 'Z';
    }
};

int main() {
//    cout << Solution().isValid(string("<DIV>This is the first line <![CDATA[<div>]]></DIV>")) << endl;
//    cout << Solution().isValid(string("<TRUE><![CDATA[wahaha]]]><![CDATA[]> wahaha]]></TRUE>")) << endl;
//    cout << Solution().isValid(string("<A><A>/A></A></A>")) << endl;
    cout << Solution().isValid(string("<A>  <B> </A>   </B>")) << endl;
    return 0;
}
