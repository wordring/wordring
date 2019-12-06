﻿// test/trie/triplet.cpp

#include <algorithm>
#include <iterator>
#include <list>
#include <string>
#include <vector>

#include <iostream>

#include <boost/test/unit_test.hpp>

#include <wordring/trie/triplet.hpp>

BOOST_AUTO_TEST_SUITE(triplet_trie__test)

// symbol_iterator ------------------------------------------------------------

BOOST_AUTO_TEST_CASE(triplet_trie__symbol_iterator__construct__1)
{
	using namespace wordring;
	using symbol_iterator = triplet_trie::symbol_iterator;

	std::vector<std::string> list{ "a", "ac", "b", "cab", "cd" };
	auto t = triplet_trie(list.begin(), list.end());
	symbol_iterator it1(t.begin(), 0), it2(t.end(), 0);
}

BOOST_AUTO_TEST_CASE(triplet_trie__symbol_iterator__construct__2)
{
	using namespace wordring;
	using symbol_iterator = triplet_trie::symbol_iterator;

	std::vector<std::string> list{ "a", "ac", "b", "cab", "cd" };
	auto t = triplet_trie(list.begin(), list.end());
	symbol_iterator it1(t.begin(), 0), it2(t.end(), 0);
	symbol_iterator it3(it1);
}

BOOST_AUTO_TEST_CASE(triplet_trie__symbol_iterator__reference__1)
{
	using namespace wordring;
	using symbol_iterator = triplet_trie::symbol_iterator;

	std::vector<std::string> list{ "a", "ac", "b", "cab", "cd" };
	auto t = triplet_trie(list.begin(), list.end());
	symbol_iterator it1(t.begin(), 0);
	BOOST_CHECK(*it1 == 'a');
}

BOOST_AUTO_TEST_CASE(triplet_trie__symbol_iterator__reference__2)
{
	using namespace wordring;
	using symbol_iterator = triplet_trie::symbol_iterator;

	std::vector<std::string> list{ "a", "ac", "b", "cab", "cd" };
	auto t = triplet_trie(list.begin(), list.end());
	BOOST_CHECK(*symbol_iterator(t.begin(), 0) == 'a');
	BOOST_CHECK((*symbol_iterator(t.begin(), 1)).has_value() == false);
	BOOST_CHECK(*symbol_iterator(std::next(t.begin(), 3), 0) == 'c');
	BOOST_CHECK(*symbol_iterator(std::next(t.begin(), 3), 2) == 'b');
}

BOOST_AUTO_TEST_CASE(triplet_trie__symbol_iterator__increment__1)
{
	using namespace wordring;
	using symbol_iterator = triplet_trie::symbol_iterator;

	std::vector<std::string> list{ "a", "ac", "b", "cab", "cd" };
	auto t = triplet_trie(list.begin(), list.end());
	symbol_iterator it1(t.begin(), 0);
	BOOST_CHECK(*it1 == 'a');
	++it1;
	BOOST_CHECK(*it1 == 'a');
	++it1;
	BOOST_CHECK(*it1 == 'b');
	++it1;
	BOOST_CHECK(*it1 == 'c');
	++it1;
	BOOST_CHECK(*it1 == 'c');
	++it1;
}

BOOST_AUTO_TEST_CASE(triplet_trie__symbol_iterator__increment__2)
{
	using namespace wordring;
	using symbol_iterator = triplet_trie::symbol_iterator;

	std::vector<std::string> list{ "a", "ac", "b", "cab", "cd" };
	auto t = triplet_trie(list.begin(), list.end());
	symbol_iterator it1(t.begin(), 0);
	BOOST_CHECK(*it1++ == 'a');
	BOOST_CHECK(*it1++ == 'a');
	BOOST_CHECK(*it1++ == 'b');
	BOOST_CHECK(*it1++ == 'c');
	BOOST_CHECK(*it1 == 'c');
}

BOOST_AUTO_TEST_CASE(triplet_trie__symbol_iterator__equal__1)
{
	using namespace wordring;
	using symbol_iterator = triplet_trie::symbol_iterator;

	std::vector<std::string> list{ "a", "ac", "b", "cab", "cd" };
	auto t = triplet_trie(list.begin(), list.end());
	symbol_iterator it1(t.begin(), 0);
	symbol_iterator it2(t.begin(), 0);
	BOOST_CHECK(it1 == it2);
	BOOST_CHECK(++it1 == ++it2);
	BOOST_CHECK(++it1 == ++it2);
	BOOST_CHECK(++it1 == ++it2);
	BOOST_CHECK(++it1 == ++it2);
	BOOST_CHECK(++it1 == ++it2);
	symbol_iterator it3(t.begin(), 0);
	symbol_iterator it4(std::next(t.begin(), 1), 0);
	BOOST_CHECK((it3 == it4) == false);
	symbol_iterator it5(t.begin(), 0);
	symbol_iterator it6(t.begin(), 1);
	BOOST_CHECK((it5 == it6) == false);
}

BOOST_AUTO_TEST_CASE(triplet_trie__symbol_iterator__not_equal__1)
{
	using namespace wordring;
	using symbol_iterator = triplet_trie::symbol_iterator;

	std::vector<std::string> list{ "a", "ac", "b", "cab", "cd" };
	auto t = triplet_trie(list.begin(), list.end());
	symbol_iterator it1(t.begin(), 0);
	symbol_iterator it2(t.begin(), 0);
	BOOST_CHECK((it1 != it2) == false);
	BOOST_CHECK((++it1 != ++it2) == false);
	BOOST_CHECK((++it1 != ++it2) == false);
	BOOST_CHECK((++it1 != ++it2) == false);
	BOOST_CHECK((++it1 != ++it2) == false);
	BOOST_CHECK((++it1 != ++it2) == false);
	symbol_iterator it3(t.begin(), 0);
	symbol_iterator it4(std::next(t.begin(), 1), 0);
	BOOST_CHECK(it3 != it4);
	symbol_iterator it5(t.begin(), 0);
	symbol_iterator it6(t.begin(), 1);
	BOOST_CHECK(it5 != it6);
}

BOOST_AUTO_TEST_CASE(triplet_trie__symbol_iterator__minus__1)
{
	using namespace wordring;
	using symbol_iterator = triplet_trie::symbol_iterator;

	std::vector<std::string> list{ "a", "ac", "b", "cab", "cd" };
	auto t = triplet_trie(list.begin(), list.end());
	symbol_iterator it1(t.begin(), 0);
	symbol_iterator it2(t.begin(), 0);
	BOOST_CHECK(it2 - it1 == 0);
	BOOST_CHECK(++it2 - it1 == 1);
	BOOST_CHECK(++it2 - it1 == 2);
	BOOST_CHECK(++it2 - it1 == 3);
	BOOST_CHECK(++it2 - it1 == 4);
	BOOST_CHECK(++it2 - it1 == 5);
	BOOST_CHECK(it2 - symbol_iterator(t.end(), 0) == 0);
}

// node_iterator --------------------------------------------------------------

BOOST_AUTO_TEST_CASE(triplet_trie__node_iterator__construct__1)
{
	using namespace wordring;
	using node_iterator = triplet_trie::node_iterator;

	std::vector<std::string> list{ "a", "ac", "b", "cab", "cd" };
	auto t = triplet_trie(list.begin(), list.end());
	node_iterator it1(t.begin(), 0, std::distance(t.begin(), t.end()), 0);
	node_iterator it3(it1);
}

BOOST_AUTO_TEST_CASE(triplet_trie__node_iterator__reference__1)
{
	using namespace wordring;
	using node_iterator = triplet_trie::node_iterator;

	std::vector<std::string> list{ "a", "ac", "b", "cab", "cd" };
	auto t = triplet_trie(list.begin(), list.end());
	// [a], [a]c
	BOOST_CHECK((*node_iterator(t.begin(), 0, 2, 0)).size() == 1);
	BOOST_CHECK((*node_iterator(t.begin(), 0, 2, 0)).symbol() == 'a');
	// [b]
	BOOST_CHECK((*node_iterator(std::next(t.begin(), 2), 0, 1, 0)).size() == 0);
	// [c]ab, [c]d
	BOOST_CHECK((*node_iterator(std::next(t.begin(), 3), 0, 2, 0)).size() == 2);
	BOOST_CHECK((*node_iterator(std::next(t.begin(), 3), 0, 2, 0)).symbol() == 'c');
}

BOOST_AUTO_TEST_CASE(triplet_trie__node_iterator__increment__1)
{
	using namespace wordring;
	using node_iterator = triplet_trie::node_iterator;

	std::vector<std::string> list{ "a", "ac", "b", "cab", "cd" };
	auto t = triplet_trie(list.begin(), list.end());

	// [a], [a]c
	node_iterator it1(t.begin(), 0, std::distance(t.begin(), t.end()), 0);
	BOOST_CHECK((*it1).size() == 1);
	BOOST_CHECK((*it1).symbol() == 'a');
	// [b]
	++it1;
	BOOST_CHECK((*it1).size() == 0);
	// [c]ab, [c]d
	++it1;
	BOOST_CHECK((*it1).size() == 2);
	BOOST_CHECK((*it1).symbol() == 'c');
}

BOOST_AUTO_TEST_CASE(triplet_trie__node_iterator__increment__2)
{
	using namespace wordring;
	using node_iterator = triplet_trie::node_iterator;

	std::vector<std::string> list{ "a", "ac", "b", "cab", "cd" };
	auto t = triplet_trie(list.begin(), list.end());

	// [a], [a]c
	node_iterator it1(t.begin(), 0, std::distance(t.begin(), t.end()), 0);
	BOOST_CHECK((*it1).size() == 1);
	BOOST_CHECK((*it1++).symbol() == 'a');
	// [b]
	BOOST_CHECK((*it1++).size() == 0);
	// [c]ab, [c]d
	BOOST_CHECK((*it1).size() == 2);
	BOOST_CHECK((*it1).symbol() == 'c');
}

BOOST_AUTO_TEST_CASE(triplet_trie__node_iterator__equal__1)
{
	using namespace wordring;
	using const_iterator = triplet_trie::node::const_iterator;

	std::vector<std::string> list{ "a", "ac", "b", "cab", "cd" };
	auto t = triplet_trie(list.begin(), list.end());
	auto root = t.root();
	
	BOOST_CHECK((std::next(root.begin(), 3) == root.end()));
}


// node -----------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(triplet_trie__node__begin__1)
{
	using namespace wordring;
	using node = triplet_trie::node;

	std::vector<std::string> list{ "a", "ac", "b", "cab", "cd" };
	std::sort(list.begin(), list.end());
	auto t = triplet_trie(list.begin(), list.end());

	// 0層目
	auto root = t.root();
	BOOST_CHECK(root.at(0).symbol() == 'a');
}

BOOST_AUTO_TEST_CASE(triplet_trie__node__at__1)
{
	using namespace wordring;
	using node = triplet_trie::node;

	std::vector<std::string> list{ "a", "ac", "b", "cab", "cd" };
	std::sort(list.begin(), list.end());
	auto t = triplet_trie(list.begin(), list.end());

	// 0層目
	auto root = t.root();
	BOOST_CHECK(root.at(0).symbol() == 'a');
}

BOOST_AUTO_TEST_CASE(triplet_trie__node__size__1)
{
	using namespace wordring;
	using node = triplet_trie::node;

	std::vector<std::string> list{ "a", "ac", "b", "cab", "cd" };
	std::sort(list.begin(), list.end());
	auto t = triplet_trie(list.begin(), list.end());

	// 0層目
	auto root = t.root();
	BOOST_CHECK(root.size() == 3);

	// 1層目
	auto c = root.children();

	auto n0 = node(t.begin(), c.at(0)); // [a], [a]c
	auto n1 = node(t.begin(), c.at(1)); // [b]
	auto n2 = node(t.begin(), c.at(2)); // [c]ab, [c]d
	BOOST_CHECK(n0.size() == 1);
	BOOST_CHECK(n1.size() == 0);
	BOOST_CHECK(n2.size() == 2);

	// 2層目
	c = n0.children();
	auto n3 = node(t.begin(), c.at(0)); // a[c]
	BOOST_CHECK(n3.size() == 0);

	c = n2.children();
	auto n4 = node(t.begin(), c.at(0)); // c[a]b
	auto n5 = node(t.begin(), c.at(1)); // c[d]
	BOOST_CHECK(n4.size() == 1);
	BOOST_CHECK(n5.size() == 0);

	// 3層目
	c = n4.children();
	auto n6 = node(t.begin(), c.at(0)); // ca[b]
	BOOST_CHECK(n6.size() == 0);
}

// フルチェック
BOOST_AUTO_TEST_CASE(triplet_trie__node__children__1)
{
	using namespace wordring;
	using node = triplet_trie::node;

	std::cout << "sizeof(wordring::triplet_trie::node): " << sizeof(triplet_trie::node) << std::endl;
	std::cout << "sizeof(int16_t): " << sizeof(int16_t) << std::endl;

	std::vector<std::string> list{ "a", "ac", "b", "cab", "cd" };
	std::sort(list.begin(), list.end());
	auto t = triplet_trie(list.begin(), list.end());

	// 0層目
	auto root = t.root();
	BOOST_CHECK(root.count() == 5);

	// 1層目
	auto c = root.children();
	BOOST_CHECK(c.size() == 3);

	auto n0 = node(t.begin(), c.at(0)); // [a], [a]c
	auto n1 = node(t.begin(), c.at(1)); // [b]
	auto n2 = node(t.begin(), c.at(2)); // [c]ab, [c]d

	BOOST_CHECK(n0.count() == 2);
	BOOST_CHECK(n1.count() == 1);
	BOOST_CHECK(n2.count() == 2);
	BOOST_CHECK(list.at(n0.first()).substr(n0.depth()) == "a");
	BOOST_CHECK(list.at(n0.first() + 1).substr(n0.depth()) == "ac");
	BOOST_CHECK(list.at(n1.first()).substr(n1.depth()) == "b");
	BOOST_CHECK(list.at(n2.first()).substr(n2.depth()) == "cab");
	BOOST_CHECK(list.at(n2.first() + 1).substr(n2.depth()) == "cd");

	// 2層目
	c = n0.children();
	BOOST_CHECK(c.size() == 1);

	auto n3 = node(t.begin(), c.at(0)); // a[c]
	BOOST_CHECK(list.at(n3.first()).substr(n3.depth()) == "c");

	c = n1.children();
	BOOST_CHECK(c.size() == 0);

	c = n2.children();
	BOOST_CHECK(c.size() == 2);

	auto n4 = node(t.begin(), c.at(0)); // c[a]b
	auto n5 = node(t.begin(), c.at(1)); // c[d]
	BOOST_CHECK(list.at(n4.first()).substr(n4.depth()) == "ab");
	BOOST_CHECK(list.at(n5.first()).substr(n5.depth()) == "d");

	// 3層目
	c = n3.children();
	BOOST_CHECK(c.size() == 0);

	c = n4.children();
	BOOST_CHECK(c.size() == 1);

	auto n6 = node(t.begin(), c.at(0)); // ca[b]
	BOOST_CHECK(list.at(n6.first()).substr(n6.depth()) == "b");

	// 4層目
	c = n6.children();
	BOOST_CHECK(c.size() == 0);
}

// コンテナの型を変更してテスト
BOOST_AUTO_TEST_CASE(triplet_trie__node__children__2)
{
	using namespace wordring;

	std::list<std::vector<char>> list{ { 'a' }, { 'a', 'c' }, { 'b' }, { 'c', 'a', 'b' }, { 'c', 'd' } };
	auto t = triplet_trie(list.begin(), list.end());

	// 0層目
	auto root = t.root();
	BOOST_CHECK(root.count() == 5);
	// 1層目
	auto c = root.children();
	BOOST_CHECK(c.size() == 3);
}

BOOST_AUTO_TEST_CASE(triplet_trie__node__symbol__1)
{
	using namespace wordring;
	using node = triplet_trie::node;

	std::vector<std::string> list{ "a", "ac", "b", "cab", "cd" };
	std::sort(list.begin(), list.end());
	auto t = triplet_trie(list.begin(), list.end());

	// 0層目
	auto root = t.root();
	// 1層目
	auto c = root.children();
	auto n0 = node(t.begin(), c.at(0));
	auto n1 = node(t.begin(), c.at(1));
	auto n2 = node(t.begin(), c.at(2));
	BOOST_CHECK(n0.symbol() == 'a'); // [a], [a]c
	BOOST_CHECK(n1.symbol() == 'b'); // [b]
	BOOST_CHECK(n2.symbol() == 'c'); // [c]ab, [c]d

	// 2層目
	c = n0.children();
	auto n3 = node(t.begin(), c.at(0));
	BOOST_CHECK(n3.symbol() == 'c'); // a[c]

	c = n2.children();
	auto n4 = node(t.begin(), c.at(0));
	auto n5 = node(t.begin(), c.at(1));
	BOOST_CHECK(n4.symbol() == 'a'); // c[a]b
	BOOST_CHECK(n5.symbol() == 'd'); // c[d]

	// 3層目
	c = n4.children();
	auto n6 = node(t.begin(), c.at(0));
	BOOST_CHECK(n6.symbol() == 'b'); // ca[b]
}

BOOST_AUTO_TEST_CASE(triplet_trie__node__is_terminal__1)
{
	using namespace wordring;
	using node = triplet_trie::node;

	std::vector<std::string> list{ "a", "ac", "b", "cab", "cd" };
	std::sort(list.begin(), list.end());
	auto t = triplet_trie(list.begin(), list.end());

	// 0層目
	auto root = t.root();

	// 1層目
	auto c = root.children();
	auto n0 = node(t.begin(), c.at(0));
	auto n1 = node(t.begin(), c.at(1));
	auto n2 = node(t.begin(), c.at(2));
	BOOST_CHECK(n0.is_terminal() == true);  // [a], [a]c
	BOOST_CHECK(n1.is_terminal() == true);  // [b]
	BOOST_CHECK(n2.is_terminal() == false); // [c]ab, [c]d

	// 2層目
	c = n0.children();
	auto n3 = node(t.begin(), c.at(0));
	BOOST_CHECK(n3.is_terminal()); // a[c]
	c = n2.children();
	auto n4 = node(t.begin(), c.at(0));
	auto n5 = node(t.begin(), c.at(1));
	BOOST_CHECK(n4.is_terminal() == false); // c[a]b
	BOOST_CHECK(n5.is_terminal() == true);  // c[d]

	// 3層目
	c = n4.children();
	auto n6 = node(t.begin(), c.at(0));
	BOOST_CHECK(n5.is_terminal() == true); // ca[b]
}


BOOST_AUTO_TEST_CASE(triplet_trie__node__indexes__1)
{
	using namespace wordring;
	using node = triplet_trie::node;

	std::vector<std::string> list{ "a", "ac", "b", "cab", "cd" };
	std::sort(list.begin(), list.end());
	auto t = triplet_trie(list.begin(), list.end());

	std::bitset<256> b{};
	b.set(0x61).set(0x62).set(0x63);
	BOOST_CHECK(t.root().indexes() == b);
}

// 一つの8ビット文字列をinsertし、8ビット記号列として検索出来ることを確認する。
BOOST_AUTO_TEST_CASE(triplet_trie__insert__1)
{
	using namespace wordring;
	using node = triplet_trie::node;

	triplet_trie t{};
	t.insert(t.begin(), "ABCDE");
	std::vector<uint8_t> v1{ 0x41u, 0x42u, 0x43u, 0x44u, 0x45u };
	std::vector<uint8_t> v2{};

	for (auto n = node(t.begin(), t.root().children().at(0)); n.count() != 0;)
	{
		v2.push_back(static_cast<uint8_t>(n.symbol()));
		n = (n.children().size()) ? node(t.begin(), n.children().at(0)) : node();
	}

	BOOST_CHECK(v1 == v2);
}

// 一つの16ビット文字列をinsertし、8ビット記号列として検索出来ることを確認する。
BOOST_AUTO_TEST_CASE(triplet_trie__insert__2)
{
	using namespace wordring;
	using node = triplet_trie::node;

	triplet_trie t{};
	t.insert(t.begin(), u"あいうえお");
	std::vector<uint8_t> v1{ 0x30u, 0x42u, 0x30u, 0x44u, 0x30u, 0x46u, 0x30u, 0x48u, 0x30u, 0x4Au };
	std::vector<uint8_t> v2{};

	for (auto n = node(t.begin(), t.root().children().at(0)); n.count() != 0;)
	{
		v2.push_back(static_cast<uint8_t>(n.symbol()));
		n = (n.children().size()) ? node(t.begin(), n.children().at(0)) : node();
	}

	BOOST_CHECK(v1 == v2);
}

// 標準コンテナにinsertすると、引数として与えた挿入位置と同一の位置が戻り値として返ることを確認。
// ※挿入するとイテレータは無効になるため、同じ位置を指す有効なイテレータが返る。
BOOST_AUTO_TEST_CASE(triplet_trie__insert__3)
{
	using namespace wordring;
	using node = triplet_trie::node;

	std::vector<uint8_t> v1{};
	auto it1 = v1.insert(v1.begin(), 0x30u);
	BOOST_CHECK(it1 == v1.begin());

	std::vector<uint8_t> v2{};
	std::vector<uint8_t> v3{ 0x30u, 0x42u };
	auto it2 = v2.insert(v2.begin(), v3.begin(), v3.end());
	BOOST_CHECK(it2 == v2.begin());
}

// 記号列のリストをinsertし、挿入されていることを確認する。
BOOST_AUTO_TEST_CASE(triplet_trie__insert__4)
{
	using namespace wordring;
	using node = triplet_trie::node;

	triplet_trie t{};
	std::vector<std::u16string> vs1{ u"一あいうえお", u"企かきくけこ" };
	auto it1 = t.insert(t.begin(), vs1.begin(), vs1.end());
	BOOST_CHECK(t.root().count() == 2);

	std::vector<uint8_t> v1{ 0x4Eu, 0x00u, 0x30u, 0x42u, 0x30u, 0x44u, 0x30u, 0x46u, 0x30u, 0x48u, 0x30u, 0x4Au };
	std::vector<uint8_t> v2{};
	for (auto n = node(t.begin(), t.root().children().at(0)); n.count() != 0;)
	{
		v2.push_back(static_cast<uint8_t>(n.symbol()));
		n = (n.children().size()) ? node(t.begin(), n.children().at(0)) : node();
	}
	BOOST_CHECK(v1 == v2);

	std::vector<uint8_t> v3{ 0x4Fu, 0x01u, 0x30u, 0x4Bu, 0x30u, 0x4Du, 0x30u, 0x4Fu, 0x30u, 0x51u, 0x30u, 0x53u };
	std::vector<uint8_t> v4{};
	for (auto n = node(t.begin(), t.root().children().at(1)); n.count() != 0;)
	{
		v4.push_back(static_cast<uint8_t>(n.symbol()));
		n = (n.children().size()) ? node(t.begin(), n.children().at(0)) : node();
	}
	BOOST_CHECK(v3 == v4);
}

// 一つの16ビット文字列をpush_backし、8ビット記号列として挿入されていることを確認する。
BOOST_AUTO_TEST_CASE(triplet_trie__push_back__1)
{
	using namespace wordring;
	using node = triplet_trie::node;

	triplet_trie t{};
	t.push_back(u"あいうえお");
	std::vector<uint8_t> v1{ 0x30u, 0x42u, 0x30u, 0x44u, 0x30u, 0x46u, 0x30u, 0x48u, 0x30u, 0x4Au };
	std::vector<uint8_t> v2{};

	for (auto n = node(t.begin(), t.root().children().at(0)); n.count() != 0;)
	{
		v2.push_back(static_cast<uint8_t>(n.symbol()));
		n = (n.children().size()) ? node(t.begin(), n.children().at(0)) : node();
	}
	BOOST_CHECK(v1 == v2);
}

BOOST_AUTO_TEST_SUITE_END()
