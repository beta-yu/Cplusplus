#ifndef __string_h__
#define __string_h__

#include <iostream>
#include <assert.h>

namespace qiyu
{
	class String
	{
	public:
		typedef char *iterator;
		iterator begin();
		iterator end();

		String(char *str);
		~String();
		String(const String& s);
		String& operator=(const String& s);
		void Swap(String& s);

		char *C_str();
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
		size_t Find(char ch, size_t pos);
		size_t Find(const char* str, size_t pos);

		bool operator<(const String& s);
		bool operator>(const String& s);
		bool operator<=(const String& s);
		bool operator>=(const String& s);
		bool operator==(const String& s);
		bool operator!=(const String& s);

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