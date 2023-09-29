#include "String.h"

String::String()
{
	length = 0;
	sVal = nullptr;
}

String::~String()
{
	delete[] sVal;
}

String::String(const String &s)
{
	length = strlen(s.CStr());
	sVal = new char[length + 1];
	strcpy(sVal, s.CStr());
}

String::String(const char *s)
{
	length = strlen(s);
	sVal = new char[length + 1];
	strcpy(sVal, s);
	// 将s中的内容复制到sVal中
	// 将字符数组的最后一个元素设置为空字符
}

String &String::operator=(const String &s)
{
	if (&s != this)
	{
		delete[] sVal;
		length = strlen(s.CStr());
		sVal = new char[length + 1];
		strcpy(sVal, s.CStr());
	}
	return *this;
}

String &String::operator=(const char *s)
{
	if (this->sVal != s)
	{
		delete[] sVal;
		length = strlen(s);
		sVal = new char[length + 1];
		strcpy(sVal, s);
	}
	return *this;
}

int String::GetLength() const
{
	return length;
}

bool String::IsEmpty() const
{
	return length == 0;
}

const char *String::CStr() const
{
	return (const char *)sVal;
}

char &String::operator[](int index) const
{
	return sVal[index];
}

void Display(const String &s)
{
	cout << s.CStr() << endl;
}

void Copy(String &s1, const String &s2)
{
	const char *cs2 = s2.CStr();
	char *cs1 = new char[strlen(cs2) + 1];
	strcpy(cs1, cs2);
	s1 = cs1;
	delete[] cs1;
}

void Copyn(String &s1, const String &s2, int n)
{
	const char *cs2 = s2.CStr();
	int len = strlen(cs2) < n ? strlen(cs2) : n;
	char *cs1 = new char[len + 1];
	strncpy(cs1, cs2, n);
	// strncpy只是将cs2的前n个字符复制给cs1
	// 不会给cs1最后一个元素设置为'\0'
	// strcpy也只是将src的所有字符（包括最后一个元素'\0'）复制给dest
	cs1[len] = '\0';
	s1 = cs1;
	delete[] cs1;
}

Status Insert(String &s1, const String &s2, int p)
{
	const char *cs1 = s1.CStr();
	const char *cs2 = s2.CStr();

	if (p >= 0 && p < strlen(cs1))
	{
		int len = strlen(cs1) + strlen(cs2);
		char *cs = new char[len + 1];
		// 手动开辟的字符串不会自动在末尾添加'\0'
		cs[len] = '\0';
		strncpy(cs, cs1, p); // 将串s1位置p前的内容复制给cs
		cs[p] = '\0';
		// strcat需要识别到前一个字符串（数组）末尾为'\0'
		// 连接时会将前一个字符串末尾的'\0'用后一个字符串的第一个字符覆盖
		// 并且strcat、strncat在连接时都会在后一个字符串连带'\0'
		// 方便后续连接
		strcat(cs, cs2); // 连接s2的内容
		int j = p + strlen(cs2);
		for (int i = p; i < strlen(cs1); i++, j++)
			cs[j] = cs1[i]; // 添加s1剩下的内容
		s1 = cs;
		delete[] cs;
		return true;
	}
	else
		return false;
}

Status Delete(String &s, int p, int n)
{
	const char *cs = s.CStr();
	if (p >= 0 && (p + n) < strlen(cs))
	{
		int len = strlen(cs) - n;
		char *news = new char[len + 1];
		strncpy(news, cs, p);
		int j = p + n;
		for (int i = p; i < len; i++, j++)
			news[i] = cs[j];
		news[len] = '\0';
		s = news;
		delete[] news;
		return true;
	}
	else
		return false;
}

String SubString(const String &s, int p, int n)
{
	if (p >= 0 && p + n <= s.GetLength() && n >= 0)
	{
		char *sub = new char[n + 1];
		const char *strp = s.CStr();
		strncpy(sub, strp + p, n);
		sub[n] = '\0';
		String subs(sub);
		delete[] sub;
		return subs;
	}
	else
	{
		return String("");
	}
}

String operator+(const String &s1, const String &s2)
{
	const char *cs1 = s1.CStr();
	const char *cs2 = s2.CStr();
	int len = strlen(cs1) + strlen(cs2);
	char *cs = new char[len + 1];
	strcpy(cs, cs1);
	strcat(cs, cs2);
	String s(cs);
	delete[] cs;
	return s;
}

bool operator==(const String &s1, const String &s2)
{
	return (strcmp(s1.CStr(), s2.CStr()) == 0);
}
