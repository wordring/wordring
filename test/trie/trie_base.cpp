﻿// test/trie/trie_base.cpp

#include <boost/test/unit_test.hpp>

#include "trie_base.hpp"

#include <wordring/trie/trie_base.hpp>

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>


BOOST_AUTO_TEST_SUITE(trie_base__test)

// ----------------------------------------------------------------------------
// trie_base
// ----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(trie_base__constrcut__1)
{
	using namespace wordring;
	trie_base trie{};
}

// void assign(InputIterator first, InputIterator last)
BOOST_AUTO_TEST_CASE(trie_base__assign__1)
{
	test_trie_base trie{};

	std::vector<std::string> words;
	words.emplace_back("");

	trie.assign(words.begin(), words.end());

	BOOST_CHECK(trie.count() == 0);
}

BOOST_AUTO_TEST_CASE(trie_base__assign__2)
{
	test_trie_base trie{};

	std::vector<std::string> words;
	words.emplace_back("a");
	words.emplace_back("ac");
	words.emplace_back("b");
	words.emplace_back("cab");
	words.emplace_back("cd");

	trie.assign(words.begin(), words.end());

	BOOST_CHECK(trie.count() == 5);
	BOOST_CHECK(trie.find(std::string("a")) != trie.end());
	BOOST_CHECK(trie.find(std::string("ac")) != trie.end());
	BOOST_CHECK(trie.find(std::string("b")) != trie.end());
	BOOST_CHECK(trie.find(std::string("cab")) != trie.end());
	BOOST_CHECK(trie.find(std::string("cd")) != trie.end());
}

BOOST_AUTO_TEST_CASE(trie_base__assign__3)
{
	test_trie_base trie{};

	std::vector<std::string> words;
	words.emplace_back("a");
	words.emplace_back("cab");
	words.emplace_back("ac");
	words.emplace_back("b");
	words.emplace_back("cab");
	words.emplace_back("cd");
	words.emplace_back("");
	words.emplace_back("");

	trie.assign(words.begin(), words.end());

	BOOST_CHECK(trie.count() == 5);
	BOOST_CHECK(trie.find(std::string("a")) != trie.end());
	BOOST_CHECK(trie.find(std::string("ac")) != trie.end());
	BOOST_CHECK(trie.find(std::string("b")) != trie.end());
	BOOST_CHECK(trie.find(std::string("cab")) != trie.end());
	BOOST_CHECK(trie.find(std::string("cd")) != trie.end());
}

// 要素アクセス ----------------------------------------------------------------

// value_type at(Key const& key)
BOOST_AUTO_TEST_CASE(trie_base__at__1)
{
	test_trie_base trie{};
	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	auto v1 = trie.at(std::string("a"));
	BOOST_CHECK(v1 == 0);

	v1 = 10;

	auto v2 = trie.at(std::string("a"));
	BOOST_CHECK(v2 == 10);

	BOOST_CHECK(trie.count() == 5);
}

BOOST_AUTO_TEST_CASE(trie_base__at__2)
{
	test_trie_base trie{};
	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	auto v1 = trie.at(std::string("ac"));
	BOOST_CHECK(v1 == 0);

	v1 = 10;

	auto v2 = trie.at(std::string("ac"));
	BOOST_CHECK(v2 == 10);

	BOOST_CHECK(trie.count() == 5);
}

BOOST_AUTO_TEST_CASE(trie_base__at__3)
{
	test_trie_base trie{};
	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	BOOST_CHECK_THROW(trie.at(std::string("d")), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(trie_base__at__4)
{
	test_trie_base trie{};
	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	BOOST_CHECK_THROW(trie.at(std::string("a")) = -1, std::invalid_argument);
}

// value_type const at(Key const& key) const
BOOST_AUTO_TEST_CASE(trie_base__at__5)
{
	test_trie_base trie{};
	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	auto const& t1 = trie;

	auto v1 = t1.at(std::string("a"));
	BOOST_CHECK(v1 == 0);
}

// value_type operator[](Key const& key)
BOOST_AUTO_TEST_CASE(trie_base__at__6)
{
	test_trie_base trie{};
	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	auto v1 = trie[std::string("a")];
	BOOST_CHECK(v1 == 0);

	v1 = 10;

	auto v2 = trie[std::string("a")];
	BOOST_CHECK(v2 == 10);

	BOOST_CHECK(trie.count() == 5);
}

BOOST_AUTO_TEST_CASE(trie_base__at__7)
{
	test_trie_base trie{};
	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	auto v1 = trie[std::string("ac")];
	BOOST_CHECK(v1 == 0);

	v1 = 10;

	auto v2 = trie[std::string("ac")];
	BOOST_CHECK(v2 == 10);

	BOOST_CHECK(trie.count() == 5);
}

BOOST_AUTO_TEST_CASE(trie_base__at__8)
{
	test_trie_base trie{};
	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	BOOST_CHECK(trie.count() == 5);

	auto v1 = trie[std::string("d")];
	BOOST_CHECK(v1 == 0);

	v1 = 10;

	auto v2 = trie[std::string("d")];
	BOOST_CHECK(v2 == 10);

	BOOST_CHECK(trie.count() == 6);
}

// value_type const operator[](Key const& key) const
BOOST_AUTO_TEST_CASE(trie_base__at__9)
{
	test_trie_base trie{};
	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	auto v1 = trie[std::string("d")];
	BOOST_CHECK(v1 == 0);
	BOOST_CHECK(trie.count() == 6);
}

// イテレータ ------------------------------------------------------------------

// const_iterator begin() const noexcept
BOOST_AUTO_TEST_CASE(trie_base__begin__1)
{
	test_trie_base trie{};
	BOOST_CHECK(trie.begin() != trie.end());
}

// const_iterator cbegin() const noexcept
BOOST_AUTO_TEST_CASE(trie_base__cbegin__1)
{
	test_trie_base trie{};
	BOOST_CHECK(trie.cbegin() != trie.cend());
}

// const_iterator end() const noexcept
BOOST_AUTO_TEST_CASE(trie_base__end__1)
{
	test_trie_base trie{};
	BOOST_CHECK(trie.begin() != trie.end());
}

// const_iterator cend() const noexcept
BOOST_AUTO_TEST_CASE(trie_base__cend__1)
{
	test_trie_base trie{};
	BOOST_CHECK(trie.cbegin() != trie.cend());
}

// 容量 -----------------------------------------------------------------------

// bool empty() const noexcept
BOOST_AUTO_TEST_CASE(trie_base__empty__1)
{
	test_trie_base trie{};
	BOOST_CHECK(trie.empty());
}

BOOST_AUTO_TEST_CASE(trie_base__empty__2)
{
	test_trie_base trie{};
	trie.insert(std::string("abc"));
	BOOST_CHECK(trie.empty() == false);
}

// size_type size() const noexcept
BOOST_AUTO_TEST_CASE(trie_base__size__1)
{
	test_trie_base trie{};
	BOOST_CHECK(trie.size() == 0);
}

BOOST_AUTO_TEST_CASE(trie_base__size__2)
{
	test_trie_base trie{};
	trie.insert(std::string("abc"));
	BOOST_CHECK(trie.size() == 1);
	trie.insert(std::string("abc"));
	BOOST_CHECK(trie.size() == 1);
}

// size_type max_size() const noexcept
BOOST_AUTO_TEST_CASE(trie_base__max_size__1)
{
	test_trie_base trie{};
	BOOST_CHECK(trie.max_size());
}

// 変更 -----------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(trie_base__clear__1)
{
	test_trie_base trie{};

	trie.insert(std::string("\1"));
	trie.insert(std::string("\1\3"));
	trie.insert(std::string("\2"));
	trie.insert(std::string("\3\1\2"));
	trie.insert(std::string("\3\4"));

	BOOST_CHECK(trie.count() == 5);
	BOOST_CHECK(trie.size() == 5);

	trie.clear();

	BOOST_CHECK(trie.count() == 0);
	BOOST_CHECK(trie.size() == 0);
}

// aにacを追加
BOOST_AUTO_TEST_CASE(trie_base__insert__1)
{
	test_trie_base trie{};
	trie.m_c.clear();

	trie.m_c.emplace_back(0, 0); // 0
	trie.m_c.emplace_back(1, 0); // 1
	trie.m_c.emplace_back(0, 1); // 2

	BOOST_CHECK(trie.count_s() == 2);

	test_iterator it = trie.insert(std::string("\1\3"));
	
	BOOST_CHECK(it.m_index == 4);
	BOOST_CHECK(trie.count_s() == 4);

	BOOST_CHECK(trie.m_c[1].m_base == 1);
	BOOST_CHECK(trie.m_c[1].m_check == 0);
	BOOST_CHECK(trie.m_c[2].m_base == 1);
	BOOST_CHECK(trie.m_c[2].m_check == 1);
	BOOST_CHECK(trie.m_c[4].m_check == 2);
	BOOST_CHECK(trie.m_c[257].m_check == 2);
}

// acにaを追加
BOOST_AUTO_TEST_CASE(trie_base__insert__2)
{
	test_trie_base trie{};

	test_iterator it1 = trie.insert(std::string("\1\3"));

	BOOST_CHECK(trie.count_s() == 3);
	BOOST_CHECK(it1.m_index == 4);

	BOOST_CHECK(trie.m_c[1].m_base == 1);
	BOOST_CHECK(trie.m_c[1].m_check == 0);
	BOOST_CHECK(trie.m_c[2].m_base == 1);
	BOOST_CHECK(trie.m_c[2].m_check == 1);
	BOOST_CHECK(trie.m_c[4].m_check == 2);

	test_iterator it2 = trie.insert(std::string("\1"));

	BOOST_CHECK(trie.count_s() == 4);
	BOOST_CHECK(it2.m_index == 2);

	BOOST_CHECK(trie.m_c[1].m_base == 1);
	BOOST_CHECK(trie.m_c[1].m_check == 0);
	BOOST_CHECK(trie.m_c[2].m_base == 1);
	BOOST_CHECK(trie.m_c[2].m_check == 1);
	BOOST_CHECK(trie.m_c[4].m_check == 2);
	BOOST_CHECK(trie.m_c[257].m_check == 2);
}

BOOST_AUTO_TEST_CASE(trie_base__insert__3)
{
	test_trie_base trie{};

	trie.insert(std::string("\1"));
	trie.insert(std::string("\1\3"));
	trie.insert(std::string("\2"));
	trie.insert(std::string("\3\1\2"));
	trie.insert(std::string("\3\4"));

	BOOST_CHECK(trie.count() == 5);
	BOOST_CHECK(trie.find(std::string("\1")) != trie.cend());
	BOOST_CHECK(trie.find(std::string("\1\3")) != trie.cend());
	BOOST_CHECK(trie.find(std::string("\2")) != trie.cend());
	BOOST_CHECK(trie.find(std::string("\3\1\2")) != trie.cend());
	BOOST_CHECK(trie.find(std::string("\3\4")) != trie.cend());
}

BOOST_AUTO_TEST_CASE(trie_base__insert__4)
{
	test_trie_base trie{};
	trie.insert(std::string("\1"));
	trie.insert(std::string("\1\3"));

	BOOST_CHECK(trie.count() == 2);
	BOOST_CHECK(trie.find(std::string("\1")) != trie.cend());
	BOOST_CHECK(trie.find(std::string("\1\3")) != trie.cend());
}

BOOST_AUTO_TEST_CASE(trie_base__insert__5)
{
	test_trie_base trie{};
	trie.insert(std::string("\1\3"));
	trie.insert(std::string("\1"));

	BOOST_CHECK(trie.count() == 2);
	BOOST_CHECK(trie.find(std::string("\1")) != trie.cend());
	BOOST_CHECK(trie.find(std::string("\1\3")) != trie.cend());
}

BOOST_AUTO_TEST_CASE(trie_base__insert__6)
{
	test_trie_base trie{};
	auto it = trie.insert(std::string(""));

	BOOST_CHECK(trie.count() == 0);
	BOOST_CHECK(it == trie.cend());
}

BOOST_AUTO_TEST_CASE(trie_base__insert__7)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	BOOST_CHECK(trie.count() == 5);

	auto it = trie.insert(std::string(""));

	BOOST_CHECK(it == trie.cend());
	BOOST_CHECK(trie.count() == 5);
}

// 0を挿入してみる
BOOST_AUTO_TEST_CASE(trie_base__insert__8)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	BOOST_CHECK(trie.count() == 5);

	auto it = trie.insert(std::string(1, '\0'));

	BOOST_CHECK(*it == '\0');
	BOOST_CHECK(trie.count() == 6);
}

// void insert(InputIterator first, InputIterator last)
BOOST_AUTO_TEST_CASE(trie_base__insert__9)
{
	test_trie_base trie{};

	std::vector<std::string> words;
	words.emplace_back("a");
	words.emplace_back("ac");
	words.emplace_back("b");
	words.emplace_back("cab");
	words.emplace_back("cd");

	trie.insert(words.begin(), words.end());

	BOOST_CHECK(trie.count() == 5);
	BOOST_CHECK(trie.find(std::string("a")) != trie.end());
	BOOST_CHECK(trie.find(std::string("ac")) != trie.end());
	BOOST_CHECK(trie.find(std::string("b")) != trie.end());
	BOOST_CHECK(trie.find(std::string("cab")) != trie.end());
	BOOST_CHECK(trie.find(std::string("cd")) != trie.end());
}

BOOST_AUTO_TEST_CASE(trie_base__insert__10)
{
	test_trie_base trie{};

	std::vector<std::string> words;
	words.emplace_back("a");
	words.emplace_back("ac");
	words.emplace_back("b");
	words.emplace_back("cab");
	words.emplace_back("cd");

	trie.insert(words.begin(), words.end());

	words.emplace_back("cb");

	trie.insert(words.begin(), words.end());

	BOOST_CHECK(trie.count() == 6);
	BOOST_CHECK(trie.find(std::string("a")) != trie.end());
	BOOST_CHECK(trie.find(std::string("ac")) != trie.end());
	BOOST_CHECK(trie.find(std::string("b")) != trie.end());
	BOOST_CHECK(trie.find(std::string("cab")) != trie.end());
	BOOST_CHECK(trie.find(std::string("cd")) != trie.end());
	BOOST_CHECK(trie.find(std::string("cb")) != trie.end());
}

// void erase(const_iterator pos)
BOOST_AUTO_TEST_CASE(trie_base__erase__1)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));
	trie.insert(std::string(1, '\0'));

	BOOST_CHECK(trie.count() == 6);

	trie.erase(trie.find(std::string(1, '\0')));

	BOOST_CHECK(trie.count() == 5);
	BOOST_CHECK(trie.find(std::string("a")) != trie.cend());
	BOOST_CHECK(trie.find(std::string("ac")) != trie.cend());
	BOOST_CHECK(trie.find(std::string("b")) != trie.cend());
	BOOST_CHECK(trie.find(std::string("cab")) != trie.cend());
	BOOST_CHECK(trie.find(std::string("cd")) != trie.cend());
	BOOST_CHECK(trie.find(std::string(1, '\0')) == trie.cend());
}

BOOST_AUTO_TEST_CASE(trie_base__erase__2)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));
	trie.insert(std::string(1, '\0'));

	BOOST_CHECK(trie.count() == 6);

	trie.erase(trie.find(std::string("a")));

	BOOST_CHECK(trie.count() == 5);
	BOOST_CHECK(trie.find(std::string("a")) == trie.cend());
	BOOST_CHECK(trie.find(std::string("ac")) != trie.cend());
	BOOST_CHECK(trie.find(std::string("b")) != trie.cend());
	BOOST_CHECK(trie.find(std::string("cab")) != trie.cend());
	BOOST_CHECK(trie.find(std::string("cd")) != trie.cend());
	BOOST_CHECK(trie.find(std::string(1, '\0')) != trie.cend());
}

BOOST_AUTO_TEST_CASE(trie_base__erase__3)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));
	trie.insert(std::string(1, '\0'));

	BOOST_CHECK(trie.count() == 6);

	trie.erase(trie.find(std::string("ac")));

	BOOST_CHECK(trie.count() == 5);

	BOOST_CHECK(trie.find(std::string("a")) != trie.cend());
	BOOST_CHECK(trie.find(std::string("ac")) == trie.cend());
	BOOST_CHECK(trie.find(std::string("b")) != trie.cend());
	BOOST_CHECK(trie.find(std::string("cab")) != trie.cend());
	BOOST_CHECK(trie.find(std::string("cd")) != trie.cend());
	BOOST_CHECK(trie.find(std::string(1, '\0')) != trie.cend());
}

BOOST_AUTO_TEST_CASE(trie_base__erase__4)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));
	trie.insert(std::string(1, '\0'));

	BOOST_CHECK(trie.count() == 6);

	trie.erase(trie.find(std::string("cab")));

	BOOST_CHECK(trie.count() == 5);
	BOOST_CHECK(trie.find(std::string("a")) != trie.cend());
	BOOST_CHECK(trie.find(std::string("ac")) != trie.cend());
	BOOST_CHECK(trie.find(std::string("b")) != trie.cend());
	BOOST_CHECK(trie.find(std::string("cab")) == trie.cend());
	BOOST_CHECK(trie.find(std::string("cd")) != trie.cend());
	BOOST_CHECK(trie.find(std::string(1, '\0')) != trie.cend());

	BOOST_CHECK(trie.find(std::string("ca")) == trie.cend());
}

BOOST_AUTO_TEST_CASE(trie_base__erase__5)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));
	trie.insert(std::string(1, '\0'));

	BOOST_CHECK(trie.count() == 6);

	trie.erase(trie.find(std::string("a")));
	trie.erase(trie.find(std::string("ac")));
	trie.erase(trie.find(std::string("b")));
	trie.erase(trie.find(std::string("cab")));
	trie.erase(trie.find(std::string("cd")));
	trie.erase(trie.find(std::string(1, '\0')));

	BOOST_CHECK(trie.count() == 0);
	BOOST_CHECK(trie.find(std::string("a")) == trie.cend());
	BOOST_CHECK(trie.find(std::string("ac")) == trie.cend());
	BOOST_CHECK(trie.find(std::string("b")) == trie.cend());
	BOOST_CHECK(trie.find(std::string("cab")) == trie.cend());
	BOOST_CHECK(trie.find(std::string("cd")) == trie.cend());
	BOOST_CHECK(trie.find(std::string(1, '\0')) == trie.cend());
}

BOOST_AUTO_TEST_CASE(trie_base__erase__6)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));
	trie.insert(std::string(1, '\0'));

	BOOST_CHECK(trie.count() == 6);

	trie.erase(trie.begin());

	BOOST_CHECK(trie.count() == 6);
}

BOOST_AUTO_TEST_CASE(trie_base__erase__7)
{
	test_trie_base trie{};
	BOOST_CHECK(trie.count() == 0);

	trie.erase(trie.begin());

	BOOST_CHECK(trie.count() == 0);
}

BOOST_AUTO_TEST_CASE(trie_base__erase__8)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));
	trie.insert(std::string(1, '\0'));

	BOOST_CHECK(trie.count() == 6);

	trie.erase(trie.end());

	BOOST_CHECK(trie.count() == 6);
}

BOOST_AUTO_TEST_CASE(trie_base__erase__9)
{
	test_trie_base trie{};
	BOOST_CHECK(trie.count() == 0);

	trie.erase(trie.end());

	BOOST_CHECK(trie.count() == 0);
}

BOOST_AUTO_TEST_CASE(trie_base__erase__10)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));
	trie.insert(std::string(1, '\0'));

	BOOST_CHECK(trie.count() == 6);

	trie.erase(std::string("a"));

	BOOST_CHECK(trie.count() == 5);
}

BOOST_AUTO_TEST_CASE(trie_base__erase__11)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));
	trie.insert(std::string(1, '\0'));

	BOOST_CHECK(trie.count() == 6);

	trie.erase(std::string(""));

	BOOST_CHECK(trie.count() == 6);
}

BOOST_AUTO_TEST_CASE(trie_base__erase__12)
{
	test_trie_base trie{};
	BOOST_CHECK(trie.count() == 0);

	trie.erase(std::string(""));

	BOOST_CHECK(trie.count() == 0);
}

// 検索 -----------------------------------------------------------------------

// auto search(Iterator first, Iterator last) const->std::pair<Iterator, const_iterator>
BOOST_AUTO_TEST_CASE(trie_base__search__1)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	std::string s{ "d" };
	auto p = trie.search(s.begin(), s.end());

	BOOST_CHECK(p.first == trie.end());
	BOOST_CHECK(p.second == s.begin());
}

BOOST_AUTO_TEST_CASE(trie_base__search__2)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	std::string s{ "c" };
	auto p = trie.search(s.begin(), s.end());

	BOOST_CHECK(*p.first == 'c');
	BOOST_CHECK(p.second == s.end());
}

BOOST_AUTO_TEST_CASE(trie_base__search__3)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	std::string s{ "cb" };
	auto p = trie.search(s.begin(), s.end());

	BOOST_CHECK(*p.first == 'c');
	BOOST_CHECK(*p.second == 'b');
}

BOOST_AUTO_TEST_CASE(trie_base__search__4)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	std::string s{ "a" };
	auto p = trie.search(s.begin(), s.end());

	BOOST_CHECK(*p.first == 'a');
	BOOST_CHECK(p.second == s.end());
}

BOOST_AUTO_TEST_CASE(trie_base__search__5)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	std::string s{ "cab" };
	auto p = trie.search(s.begin(), s.end());

	BOOST_CHECK(*p.first == 'b');
	BOOST_CHECK(p.second == s.end());
}

BOOST_AUTO_TEST_CASE(trie_base__search__6)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	std::string s{ "" };
	auto p = trie.search(s.begin(), s.end());

	BOOST_CHECK(p.first == trie.end());
	BOOST_CHECK(p.second == s.begin());
}

BOOST_AUTO_TEST_CASE(trie_base__search__7)
{
	test_trie_base trie{};

	std::string s{ "" };
	auto p = trie.search(s.begin(), s.end());

	BOOST_CHECK(p.first == trie.end());
	BOOST_CHECK(p.second == s.begin());
}

// const_iterator search(Key const& key) const
BOOST_AUTO_TEST_CASE(trie_base__search__8)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	auto it = trie.search(std::string{ "" });

	BOOST_CHECK(it == trie.cend());
}

BOOST_AUTO_TEST_CASE(trie_base__search__9)
{
	test_trie_base trie{};

	auto it = trie.search(std::string{ "a" });

	BOOST_CHECK(it == trie.cend());
}

BOOST_AUTO_TEST_CASE(trie_base__search__10)
{
	test_trie_base trie{};

	auto it = trie.search(std::string{ "" });

	BOOST_CHECK(it == trie.cend());
}

BOOST_AUTO_TEST_CASE(trie_base__search__11)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	auto it = trie.search(std::string{ "c" });

	BOOST_CHECK(*it == 'c');
}

BOOST_AUTO_TEST_CASE(trie_base__search__12)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	auto it = trie.search(std::string{ "cab" });

	BOOST_CHECK(*it == 'b');
}

// const_iterator find(Key const& key) const
BOOST_AUTO_TEST_CASE(trie_base__find__1)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	auto it = trie.find(std::string{ "c" });

	BOOST_CHECK(it == trie.cend());
}

BOOST_AUTO_TEST_CASE(trie_base__find__2)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	auto it = trie.find(std::string{ "" });

	BOOST_CHECK(it == trie.cend());
}

BOOST_AUTO_TEST_CASE(trie_base__find__3)
{
	test_trie_base trie{};

	auto it = trie.find(std::string{ "c" });

	BOOST_CHECK(it == trie.cend());
}

BOOST_AUTO_TEST_CASE(trie_base__find__4)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));

	auto it = trie.find(std::string{ "a" });
	BOOST_CHECK(*it == 'a');

	it = trie.find(std::string{ "ac" });
	BOOST_CHECK(*it == 'c');

	it = trie.find(std::string{ "b" });
	BOOST_CHECK(*it == 'b');

	it = trie.find(std::string{ "cab" });
	BOOST_CHECK(*it == 'b');

	it = trie.find(std::string{ "cd" });
	BOOST_CHECK(*it == 'd');
}

// 0を検索してみる
BOOST_AUTO_TEST_CASE(trie_base__find__5)
{
	test_trie_base trie{};

	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));
	trie.insert(std::string(1, '\0'));

	BOOST_CHECK(trie.count() == 6);
	auto it = trie.find(std::string(1, '\0'));
	BOOST_CHECK(*it == '\0');
}

// 内部 -----------------------------------------------------------------------

// index_type modify(const_iterator parent, label_vector& labels)
BOOST_AUTO_TEST_CASE(trie_base__modify__1)
{
	test_trie_base trie{};
	trie.insert(std::string("a"));
	trie.insert(std::string("ac"));
	trie.insert(std::string("acb"));
	trie.insert(std::string("ab"));
	trie.insert(std::string("b"));
	trie.insert(std::string("cab"));
	trie.insert(std::string("cd"));
	trie.insert(std::string("cd"));

	BOOST_CHECK(trie.count() == 7);

	trie.insert(std::string("d"));

	BOOST_CHECK(trie.count() == 8);
}

BOOST_AUTO_TEST_CASE(trie_base__modify__2)
{
	BOOST_WARN(false);
}

// void add(const_iterator parent, label_vector const& labels)
// 静的構築
BOOST_AUTO_TEST_CASE(trie_base__add__1)
{
	using namespace wordring;

	test_trie_base trie{};
	trie.add(test_iterator(trie.m_c, 1), { 1, 2, 3 });
	trie.add(test_iterator(trie.m_c, 2), { 0, 3 });
	trie.add(test_iterator(trie.m_c, 4), { 1, 4 });
	trie.add(test_iterator(trie.m_c, 6), 2);

	BOOST_CHECK(trie.m_c[1].m_base == 1);
	BOOST_CHECK(trie.m_c[1].m_check == 0);
	BOOST_CHECK(trie.m_c[2].m_base == 5);
	BOOST_CHECK(trie.m_c[2].m_check == 1);
	BOOST_CHECK(trie.m_c[3].m_check == 1);
	BOOST_CHECK(trie.m_c[4].m_base == 5);
	BOOST_CHECK(trie.m_c[4].m_check == 1);
	BOOST_CHECK(trie.m_c[5].m_check == 2);
	BOOST_CHECK(trie.m_c[6].m_base == 5);
	BOOST_CHECK(trie.m_c[6].m_check == 4);
	BOOST_CHECK(trie.m_c[7].m_check == 6);
	BOOST_CHECK(trie.m_c[8].m_check == 2);
	BOOST_CHECK(trie.m_c[9].m_check == 4);
}

// 動的構築
BOOST_AUTO_TEST_CASE(trie_base__add__2)
{
	using namespace wordring;

	test_trie_base trie{};
	trie.add(test_iterator(trie.m_c, 1), { 1, 2, 3 });
	trie.add(test_iterator(trie.m_c, 2), { 0, 3 });
	trie.add(test_iterator(trie.m_c, 4), { 1, 4 });
	trie.add(test_iterator(trie.m_c, 6), 2);

	trie.add(test_iterator(trie.m_c, 2), 5);

	BOOST_CHECK(trie.count());

	BOOST_CHECK(trie.m_c[1].m_base == 1);
	BOOST_CHECK(trie.m_c[1].m_check == 0);
	BOOST_CHECK(trie.m_c[2].m_base == 5);
	BOOST_CHECK(trie.m_c[2].m_check == 1);
	BOOST_CHECK(trie.m_c[3].m_check == 1);
	BOOST_CHECK(trie.m_c[4].m_base == 5);
	BOOST_CHECK(trie.m_c[4].m_check == 1);
	BOOST_CHECK(trie.m_c[5].m_check == 2);
	BOOST_CHECK(trie.m_c[6].m_base == 5);
	BOOST_CHECK(trie.m_c[6].m_check == 4);
	BOOST_CHECK(trie.m_c[7].m_check == 6);
	BOOST_CHECK(trie.m_c[8].m_check == 2);
	BOOST_CHECK(trie.m_c[9].m_check == 4);

	BOOST_CHECK(trie.m_c[10].m_check == 2);
}

// 動的構築
BOOST_AUTO_TEST_CASE(trie_base__add__3)
{
	using namespace wordring;

	test_trie_base trie{};
	trie.add(test_iterator(trie.m_c, 1), { 1, 2, 3 });
	trie.add(test_iterator(trie.m_c, 2), { 0, 3 });
	trie.add(test_iterator(trie.m_c, 4), { 1, 4 });
	trie.add(test_iterator(trie.m_c, 6), 2);

	trie.add(test_iterator(trie.m_c, 2), 4);

	BOOST_CHECK(trie.m_c[1].m_base == 1);
	BOOST_CHECK(trie.m_c[1].m_check == 0);
	BOOST_CHECK(trie.m_c[2].m_base == 10);
	BOOST_CHECK(trie.m_c[2].m_check == 1);
	BOOST_CHECK(trie.m_c[3].m_check == 1);
	BOOST_CHECK(trie.m_c[4].m_base == 5);
	BOOST_CHECK(trie.m_c[4].m_check == 1);
	BOOST_CHECK(trie.m_c[6].m_base == 5);
	BOOST_CHECK(trie.m_c[6].m_check == 4);
	BOOST_CHECK(trie.m_c[7].m_check == 6);
	BOOST_CHECK(trie.m_c[9].m_check == 4);

	BOOST_CHECK(trie.m_c[10].m_check == 2);
	BOOST_CHECK(trie.m_c[13].m_check == 2);
	BOOST_CHECK(trie.m_c[14].m_check == 2);
}

// 入出力 ---------------------------------------------------------------------

// inline std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, trie_base<Allocator>& trie)

BOOST_AUTO_TEST_CASE(trie_base__stream__1)
{
	test_trie_base t1{};

	t1.insert(std::string("a"));
	t1.insert(std::string("ac"));
	t1.insert(std::string("b"));
	t1.insert(std::string("cab"));
	t1.insert(std::string("cd"));

	std::stringstream s;
	s << t1;

	test_trie_base t2{};
	s >> t2;

	BOOST_CHECK(t1.m_c == t2.m_c);
	BOOST_CHECK(t1.size() == t2.size());

	BOOST_CHECK(*t2.find(std::string("a")) == 'a');
	BOOST_CHECK(*t2.find(std::string("ac")) == 'c');
	BOOST_CHECK(*t2.find(std::string("b")) == 'b');
	BOOST_CHECK(*t2.find(std::string("cab")) == 'b');
	BOOST_CHECK(*t2.find(std::string("cd")) == 'd');

	BOOST_CHECK(t2.size() == 5);
	BOOST_CHECK(t2.count() == 5);
}

BOOST_AUTO_TEST_CASE(trie_base__stream__2)
{
	test_trie_base t1{};

	std::stringstream s;
	s << t1;

	test_trie_base t2{};
	s >> t2;

	BOOST_CHECK(t1.m_c == t2.m_c);
	BOOST_CHECK(t1.size() == t2.size());

	BOOST_CHECK(t2.size() == 0);
	BOOST_CHECK(t2.count() == 0);
}

BOOST_AUTO_TEST_CASE(trie_base__stream__3)
{
	std::vector<std::string> words{};
	{
		std::string buf{};
		std::ifstream is(english_words_path);
		BOOST_REQUIRE(is.is_open());
#ifdef NDEBUG
		while (std::getline(is, buf)) words.push_back(buf);
#else
		for (size_t i = 0; i < 1000 && std::getline(is, buf); ++i) words.push_back(buf);
		std::mt19937 mt;
		std::shuffle(words.begin(), words.end(), mt);
#endif
	}

	std::cout << "trie_base__stream__3" << std::endl;

	test_trie_base t1{};
	t1.assign(words.begin(), words.end());

	std::stringstream s;

	auto start = std::chrono::system_clock::now();
	s << t1;
	auto duration = std::chrono::system_clock::now() - start;

	std::cout << "output: " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;

	test_trie_base t2{};
	start = std::chrono::system_clock::now();
	s >> t2;
	duration = std::chrono::system_clock::now() - start;

	std::cout << "input: " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;

	std::cout << "node  : " << t2.m_c.size() << std::endl;
	std::cout << "count : " << t2.count() << std::endl;
	std::cout << "size  : " << t2.size() << std::endl;
	std::cout << "vector: " << words.size() << std::endl;
}

BOOST_AUTO_TEST_CASE(trie_base__stream__4)
{
	std::vector<std::string> words{};
	{
		std::string buf{};
		std::ifstream is(english_words_path);
		BOOST_REQUIRE(is.is_open());
		for (size_t i = 0; i < 1000 && std::getline(is, buf); ++i) words.push_back(buf);
		std::mt19937 mt;
		std::shuffle(words.begin(), words.end(), mt);
	}

	test_trie_base t1{};
	t1.assign(words.begin(), words.end());

	std::stringstream s;
	s << t1;

	test_trie_base t2{};

	auto start = std::chrono::system_clock::now();

	s >> t2;

	auto duration = std::chrono::system_clock::now() - start;

	std::cout << "trie_base__stream__4" << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;
	std::cout << "node  : " << t2.m_c.size() << std::endl;
	std::cout << "count : " << t2.count() << std::endl;
	std::cout << "size  : " << t2.size() << std::endl;
	std::cout << "vector: " << words.size() << std::endl;
}

BOOST_AUTO_TEST_CASE(trie_base__serialize__1)
{
	std::vector<std::string> words{};
	{
		std::string buf{};
		std::ifstream is(english_words_path);
		BOOST_REQUIRE(is.is_open());
#ifdef NDEBUG
		while (std::getline(is, buf)) words.push_back(buf);
#else
		for (size_t i = 0; i < 1000 && std::getline(is, buf); ++i) words.push_back(buf);
		std::mt19937 mt;
		std::shuffle(words.begin(), words.end(), mt);
#endif
	}

	std::cout << "trie_base__serialize__1" << std::endl;

	test_trie_base t1{};
	t1.assign(words.begin(), words.end());

	std::vector<std::uint8_t> v;

	auto start = std::chrono::system_clock::now();
	v << t1;
	auto duration = std::chrono::system_clock::now() - start;

	std::cout << "output: " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;
	std::cout << "buffer size: " << v.size() << std::endl;

	test_trie_base t2{};
	start = std::chrono::system_clock::now();
	v >> t2;
	duration = std::chrono::system_clock::now() - start;

	std::cout << "input: " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;

	std::cout << "node  : " << t2.m_c.size() << std::endl;
	std::cout << "count : " << t2.count() << std::endl;
	std::cout << "size  : " << t2.size() << std::endl;
	std::cout << "vector: " << words.size() << std::endl;
}

// inline std::vector<std::uint32_t>& operator<<(std::vector<std::uint32_t>& v, trie_base<Allocator1> const& trie)
// inline std::vector<std::uint32_t>& operator>>(std::vector<std::uint32_t>& v, trie_base<Allocator1>& trie)
BOOST_AUTO_TEST_CASE(trie_base__serialize__2)
{
	std::vector<std::string> words{};
	{
		std::string buf{};
		std::ifstream is(english_words_path);
		BOOST_REQUIRE(is.is_open());
#ifdef NDEBUG
		while (std::getline(is, buf)) words.push_back(buf);
#else
		for (size_t i = 0; i < 1000 && std::getline(is, buf); ++i) words.push_back(buf);
		std::mt19937 mt;
		std::shuffle(words.begin(), words.end(), mt);
#endif
	}

	std::cout << "trie_base__serialize__2" << std::endl;

	test_trie_base t1{};
	t1.assign(words.begin(), words.end());

	std::vector<std::uint32_t> v;

	auto start = std::chrono::system_clock::now();
	v << t1;
	auto duration = std::chrono::system_clock::now() - start;

	std::cout << "output: " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;
	std::cout << "buffer size: " << v.size() << std::endl;

	test_trie_base t2{};
	start = std::chrono::system_clock::now();
	v >> t2;
	duration = std::chrono::system_clock::now() - start;

	std::cout << "input: " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;

	std::cout << "node  : " << t2.m_c.size() << std::endl;
	std::cout << "count : " << t2.count() << std::endl;
	std::cout << "size  : " << t2.size() << std::endl;
	std::cout << "vector: " << words.size() << std::endl;
}

// ----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(trie_base__english_words_txt__1)
{
	std::vector<std::string> words{};
	{
		std::string buf{};
		std::ifstream is(english_words_path);
		BOOST_REQUIRE(is.is_open());
#ifdef NDEBUG
		while (std::getline(is, buf)) words.push_back(buf);
#else
		for (size_t i = 0; i < 1000 && std::getline(is, buf); ++i) words.push_back(buf);
		std::mt19937 mt;
		std::shuffle(words.begin(), words.end(), mt);
#endif
	}

	test_trie_base trie{};

	auto start = std::chrono::system_clock::now();

	for (auto const& s : words) trie.insert(s);

	auto duration = std::chrono::system_clock::now() - start;

	std::cout << "trie_base__english_words_txt__1 (dynamic insert.)" << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;
	std::cout << "node  : " << trie.m_c.size() << std::endl;
	std::cout << "count : " << trie.count() << std::endl;
	std::cout << "size  : " << trie.size() << std::endl;
	std::cout << "vector: " << words.size() << std::endl;

	BOOST_CHECK(trie.count() == words.size());
	BOOST_CHECK(trie.size() == words.size());
}

BOOST_AUTO_TEST_CASE(trie_base__english_words_txt__2)
{
	std::vector<std::string> words{};
	{
		std::string buf{};
		std::ifstream is(english_words_path);
		BOOST_REQUIRE(is.is_open());
#ifdef NDEBUG
		while (std::getline(is, buf)) words.push_back(buf);
#else
		for (size_t i = 0; i < 1000 && std::getline(is, buf); ++i) words.push_back(buf);
		std::mt19937 mt;
		std::shuffle(words.begin(), words.end(), mt);
#endif
	}

	test_trie_base trie{};

	auto start = std::chrono::system_clock::now();

	trie.assign(words.begin(), words.end());

	auto duration = std::chrono::system_clock::now() - start;

	std::cout << "trie_base__english_words_txt__2 (static assign.)" << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;
	std::cout << "node  : " << trie.m_c.size() << std::endl;
	std::cout << "count : " << trie.count() << std::endl;
	std::cout << "size  : " << trie.size() << std::endl;
	std::cout << "vector: " << words.size() << std::endl;

	BOOST_CHECK(trie.count() == words.size());
	BOOST_CHECK(trie.size() == words.size());
}

BOOST_AUTO_TEST_CASE(trie_base__english_words_txt__3)
{
	std::vector<std::string> words{};
	{
		std::string buf{};
		std::ifstream is(english_words_path);
		BOOST_REQUIRE(is.is_open());
		for (size_t i = 0; i < 5000 && std::getline(is, buf); ++i) words.push_back(buf);
		std::mt19937 mt;
		std::shuffle(words.begin(), words.end(), mt);
	}

	test_trie_base trie{};

	auto start = std::chrono::system_clock::now();

	for (auto const& s : words) trie.insert(s);

	auto duration = std::chrono::system_clock::now() - start;

	std::cout << "trie_base__english_words_txt__3 (dynamic insert.)" << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;
	std::cout << "node  : " << trie.m_c.size() << std::endl;
	std::cout << "count : " << trie.count() << std::endl;
	std::cout << "size  : " << trie.size() << std::endl;
	std::cout << "vector: " << words.size() << std::endl;

	BOOST_CHECK(trie.count() == words.size());
	BOOST_CHECK(trie.size() == words.size());
}

BOOST_AUTO_TEST_CASE(trie_base__english_words_txt__4)
{
	std::vector<std::string> words{};
	{
		std::string buf{};
		std::ifstream is(english_words_path);
		BOOST_REQUIRE(is.is_open());
		for (size_t i = 0; i < 5000 && std::getline(is, buf); ++i) words.push_back(buf);
		std::mt19937 mt;
		std::shuffle(words.begin(), words.end(), mt);
	}

	test_trie_base trie{};

	auto start = std::chrono::system_clock::now();

	trie.assign(words.begin(), words.end());

	auto duration = std::chrono::system_clock::now() - start;

	std::cout << "trie_base__english_words_txt__4 (static assign.)" << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;
	std::cout << "node  : " << trie.m_c.size() << std::endl;
	std::cout << "count : " << trie.count() << std::endl;
	std::cout << "size  : " << trie.size() << std::endl;
	std::cout << "vector: " << words.size() << std::endl;

	BOOST_CHECK(trie.count() == words.size());
	BOOST_CHECK(trie.size() == words.size());
}

BOOST_AUTO_TEST_CASE(trie_base__english_words_txt__5)
{
	std::vector<std::string> words{};
	{
		std::string buf{};
		std::ifstream is(english_words_path);
		BOOST_REQUIRE(is.is_open());
		for (size_t i = 0; i < 10000 && std::getline(is, buf); ++i) words.push_back(buf);
		std::mt19937 mt;
		std::shuffle(words.begin(), words.end(), mt);
	}

	test_trie_base trie{};

	auto start = std::chrono::system_clock::now();

	for (auto const& s : words) trie.insert(s);

	auto duration = std::chrono::system_clock::now() - start;

	std::cout << "trie_base__english_words_txt__5 (dynamic insert.)" << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;
	std::cout << "node  : " << trie.m_c.size() << std::endl;
	std::cout << "count : " << trie.count() << std::endl;
	std::cout << "size  : " << trie.size() << std::endl;
	std::cout << "vector: " << words.size() << std::endl;

	BOOST_CHECK(trie.count() == words.size());
	BOOST_CHECK(trie.size() == words.size());
}

BOOST_AUTO_TEST_CASE(trie_base__english_words_txt__6)
{
	std::vector<std::string> words{};
	{
		std::string buf{};
		std::ifstream is(english_words_path);
		BOOST_REQUIRE(is.is_open());
		for (size_t i = 0; i < 10000 && std::getline(is, buf); ++i) words.push_back(buf);
		std::mt19937 mt;
		std::shuffle(words.begin(), words.end(), mt);
	}

	test_trie_base trie{};

	auto start = std::chrono::system_clock::now();

	trie.assign(words.begin(), words.end());

	auto duration = std::chrono::system_clock::now() - start;

	std::cout << "trie_base__english_words_txt__6 (static assign.)" << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;
	std::cout << "node  : " << trie.m_c.size() << std::endl;
	std::cout << "count : " << trie.count() << std::endl;
	std::cout << "size  : " << trie.size() << std::endl;
	std::cout << "vector: " << words.size() << std::endl;

	BOOST_CHECK(trie.count() == words.size());
	BOOST_CHECK(trie.size() == words.size());
}

BOOST_AUTO_TEST_CASE(trie_base__english_words_benchmark__1)
{
	std::vector<std::string> words{};
	{
		std::string buf{};
		std::ifstream is(english_words_path);
		BOOST_REQUIRE(is.is_open());
#ifdef NDEBUG
		while (std::getline(is, buf)) words.push_back(buf);
#else
		for (size_t i = 0; i < 1000 && std::getline(is, buf); ++i) words.push_back(buf);
		std::mt19937 mt;
		std::shuffle(words.begin(), words.end(), mt);
#endif
	}

	std::uint32_t error = 0;

	std::cout << "trie_base__english_words_benchmark__1" << std::endl;

	test_trie_base trie{};
	auto start = std::chrono::system_clock::now();
	trie.assign(words.begin(), words.end());
	auto duration = std::chrono::system_clock::now() - start;

	std::cout << "trie assign." << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;
	std::cout << "node  : " << trie.m_c.size() << std::endl;
	std::cout << "size  : " << trie.size() << std::endl;
	std::cout << std::endl;

	std::set<std::string> set{};
	start = std::chrono::system_clock::now();
	set.insert(words.begin(), words.end());
	duration = std::chrono::system_clock::now() - start;

	std::cout << "std::set insert." << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;
	std::cout << std::endl;

	std::unordered_set<std::string> uset{};
	start = std::chrono::system_clock::now();
	uset.insert(words.begin(), words.end());
	duration = std::chrono::system_clock::now() - start;

	std::cout << "std::unordered_set insert." << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;
	std::cout << std::endl;

	start = std::chrono::system_clock::now();
	for (auto const& s : words) if(trie.find(s) == trie.end()) ++error;
	duration = std::chrono::system_clock::now() - start;

	std::cout << "trie find." << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;
	std::cout << std::endl;

	start = std::chrono::system_clock::now();
	for (auto const& s : words) if(set.find(s) == set.cend()) ++error;
	duration = std::chrono::system_clock::now() - start;

	std::cout << "std::set find." << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;
	std::cout << std::endl;

	start = std::chrono::system_clock::now();
	for (auto const& s : words) if(uset.find(s) == uset.cend()) ++error;
	duration = std::chrono::system_clock::now() - start;

	std::cout << "std::unordered_set find." << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms" << std::endl;
	std::cout << std::endl;

	BOOST_CHECK(error == 0);
}

BOOST_AUTO_TEST_SUITE_END()
