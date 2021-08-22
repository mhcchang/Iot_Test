# coding:utf-8
'''
author:
function:
param:
other
'''
'''
1、记录一道牛客网题目的解答方式

描述
	计算字符串最后一个单词的长度，单词以空格隔开，字符串长度小于5000。

输入描述：
	输入一行，代表要计算的字符串，非空，长度小于5000。

输出描述：
	输出一个整数，表示输入字符串最后一个单词的长度。

示例1
输入：	
	hello nowcoder
输出：
	8
说明：
	最后一个单词为nowcoder，长度为8
'''
'''
思路：
	1、首先把字符串最后的空格去掉。
	2、从后面开始往前面遍历，如果遇到空格就退出（这种情况是字符串之间含有空格）长度小于0就退出（这种情况是字符串中没有空格）

'''

class Solution:
	def lengthOfLastWord(self, s: str) -> int:
		s = s.rstrip()
		l = len(s)
		count = 0
		while l-1>=0:
			if s[l-1] == ' ':
				break
			else:
				l -= 1
				count +=1
		return count

print(Solution().lengthOfLastWord("day"))

