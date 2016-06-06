#pragma once
#include <string>
#include "Shared/Utility.hpp"

/*
	String class, extends std::string
*/
template<typename T>
class StringBase : public std::basic_string<T>
{
public:
	using std::basic_string<T>::basic_string;
	StringBase() = default;
	StringBase(const T* cs);
	StringBase(const std::basic_string<T>& ss);
	StringBase(const StringBase&) = default;
	StringBase& operator=(const StringBase&) = default;
	StringBase& operator=(const T* cs);
	StringBase& operator=(const std::basic_string<T>& ss);
	const T* operator*() const;
	bool Split(const StringBase& delim, StringBase* l, StringBase* r) const;
	bool SplitLast(const StringBase& delim, StringBase* l, StringBase* r) const;
	void TrimFront(T c);
	void TrimBack(T c);
	void Trim(T c = ' ');
	T* GetData();
	const T* GetData() const;
};

/* String class, extends std::string */
typedef StringBase<char> String;
typedef StringBase<wchar_t> WString;

namespace Utility
{
	template<typename I>
	I SprintfArgFilter(const I& in)
	{
		return in;
	}
	const char* SprintfArgFilter(const String& in);
	template<typename I>
	I WSprintfArgFilter(const I& in)
	{
		return in;
	}
	const wchar_t* WSprintfArgFilter(const WString& in);

	// Helper function that perorms the c standard sprintf but returns a managed object instead
	// Max Output length = 8000
	template<typename... Args>
	String Sprintf(const char* fmt, Args... args)
	{
		static char buffer[8000];
		sprintf_s(buffer, fmt, SprintfArgFilter(args)...);
		return String(buffer);
	}

	// Helper function that perorms the c standard sprintf but returns a managed object instead
	// Max Output length = 8000
	template<typename... Args>
	WString WSprintf(const wchar_t* fmt, Args... args)
	{
		static wchar_t buffer[8000];
		wsprintf(buffer, fmt, WSprintfArgFilter(args)...);
		return WString(buffer);
	}

	String ConvertToANSI(const WString& unicodeString);
	WString ConvertToUnicode(const String& ansiString);
}

/* Template string function implementations */
template<typename T>
StringBase<T>::StringBase(const T* cs) : std::basic_string<T>(cs)
{

}
template<typename T>
StringBase<T>::StringBase(const std::basic_string<T>& ss)
{
	dynamic_cast<std::basic_string<T>&>(*this) = ss;
}
template<typename T>
StringBase<T>& StringBase<T>::operator=(const T* cs)
{
	dynamic_cast<std::basic_string<T>&>(*this) = cs;
	return *this;
}
template<typename T>
StringBase<T>& StringBase<T>::operator=(const std::basic_string<T>& ss)
{
	dynamic_cast<std::basic_string<T>&>(*this) = ss;
	return *this;
}
template<typename T>
const T* StringBase<T>::operator*() const
{
	return c_str();
}
template<typename T>
bool StringBase<T>::Split(const StringBase& delim, StringBase* l, StringBase* r) const
{
	size_t f = find(delim);
	if(f == -1)
		return false;
	StringBase selfCopy = *this;
	if(r)
	{
		*r = selfCopy.substr(f + delim.length());
	}
	if(l)
	{
		*l = selfCopy.substr(0, f);
	}

	return true;
}
template<typename T>
bool StringBase<T>::SplitLast(const StringBase& delim, StringBase* l, StringBase* r) const
{
	size_t f = find_last_of(delim);
	if(f == -1)
		return false;
	if(l)
	{
		*l = substr(0, f);
	}
	if(r)
	{
		*r = substr(f + delim.length());
	}

	return true;
}
template<typename T>
void StringBase<T>::TrimFront(T c)
{
	StringBase& s = (*this);
	while(length() > 0)
	{
		if(front() != c)
			break;
		this->erase(begin());
	}
}
template<typename T>
void StringBase<T>::TrimBack(T c)
{
	StringBase& s = (*this);
	while(length() > 0)
	{
		if(back() != c)
			break;
		this->erase(--end());
	}
}
template<typename T>
void StringBase<T>::Trim(T c)
{
	TrimFront(c);
	TrimBack(c);
}
template<typename T>
T* StringBase<T>::GetData()
{
	if(empty())
		return nullptr;
	return &front();
}
template<typename T>
const T* StringBase<T>::GetData() const
{
	if(empty())
		return nullptr;
	return &front();
}