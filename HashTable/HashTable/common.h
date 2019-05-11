#pragma once

template<class K>
class HashFunc
{
public:
	int operator()(const K& key)
	{
		return key;
	}
};

template<>
class HashFunc<std::string>
{
public:
	int operator()(const std::string& key)
	{
		int seed = 131;
		int hashret = 0;
		for (const auto& it : key)
		{
			hashret = hashret*seed + it;
		}
		return hashret;
	}
};