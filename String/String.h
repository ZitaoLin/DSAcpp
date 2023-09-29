#pragma once
#include <iostream>
#include <string.h>
using namespace std;
typedef bool Status;

class String
{
protected:
	char *sVal;
	int length;

public:
	String();
	virtual ~String();
	String(const String &s);
	String(const char *s);
	String &operator=(const String &s);
	String &operator=(const char *s);

	int GetLength() const;
	bool IsEmpty() const;
	const char *CStr() const;		   // 将字符串转换成字符数组
	char &operator[](int index) const; // 下标运算符重载
};
void Display(const String &s);			 // 字符串输出
void Copy(String &s1, const String &s2); // 将s2的内容复制到s1
void Copyn(String &s1, const String &s2, int n);
// 将s2的前n个字符复制给s1
Status Insert(String &s1, const String &s2, int p);
// 将s2插入到s1的p位置处
Status Delete(String &s, int p, int n);
// 删除s中从位置p开始长度为n的子串
String SubString(const String &s, int p, int n);
// 在s中求从p位置开始长度为n的子串

String operator+(const String &s1, const String &s2);
// 字符串连接
bool operator==(const String &s1, const String &s2);
// 字符串逻辑运算