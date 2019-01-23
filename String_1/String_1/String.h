#ifndef __string_h__
#define __string_h__

#include <iostream>
#include <assert.h>

namespace qiyu
{
	class String
	{
	public:
		typedef char* iterator;
		iterator begin();
		iterator end();

		typedef const char* const_iterator;
		const_iterator cbegin() const;
		const_iterator cend() const;
		const_iterator begin() const;
		const_iterator end() const;


		String(const char *str);
		~String();
		String(const String& s);
		String& operator=(String s);
		void Swap(String& s);

		const char *C_str() const;
		char& operator[](size_t pos);  /*返回引用，可读可改*/
		size_t Size();
		size_t Capacity();

		void Reserve(size_t n);
		void Pushback(char ch);
		void Append(const char *str);


		String& operator+=(char ch);
		String& operator+=(const char* str);
		void Insert(size_t pos, char ch);
		void Insert(size_t pos, const char* str);

		void Erase(size_t pos, size_t len);
		size_t Find(char ch, size_t pos) const;
		size_t Find(const char* str, size_t pos) const;

		bool operator<(const String& s) const;
		bool operator>(const String& s) const;
		bool operator<=(const String& s) const;
		bool operator>=(const String& s) const;
		bool operator==(const String& s) const;
		bool operator!=(const String& s) const;

		//friend ostream& operator<<(ostream& out, const String& s);



	private:
		char *_str;
		size_t _size;
		size_t _capacity;
		static size_t npos;
	};

	void testString();
}






#endif //__string_h__