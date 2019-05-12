﻿// generator/whatwg/encoding/encoding.cpp

#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#define STRING(str) #str
#define TO_STRING(str) STRING(str)

struct index
{
	std::string name;
	std::vector<std::string> data;
};

struct range
{
	std::string name;
	std::vector<std::pair<std::string, std::string>> data;
};

struct pointer
{
	std::string name;
	std::multimap<uint32_t, uint16_t> data;
};

int main()
{
	// コードポイント索引表を構築
	std::vector<index> indexes_code_point{};
	range gb18030_code_point{};
	{
		boost::property_tree::ptree pt;
		boost::property_tree::read_json(TO_STRING(INDEXES_JSON_PATH), pt);

		// 索引名を収集
		std::vector<std::string> names{};
		for (auto const& child : pt) names.push_back(child.first);

		// 各索引項目を収集
		for (auto const& name : names)
		{
			std::string cpp_name{ name };
			std::replace(cpp_name.begin(), cpp_name.end(), '-', '_');

			if (name == "gb18030-ranges")
			{
				gb18030_code_point.name = cpp_name;

				for (auto& v : pt.get_child(name))
				{
					std::vector<std::string> array{};
					for (auto& val : v.second) array.push_back(val.second.data());
					assert(array.size() == 2);
					assert(array[1] != "0");
					gb18030_code_point.data.push_back(std::make_pair(array[0], array[1]));
				}
			}
			else
			{
				indexes_code_point.push_back(index());
				index& current = indexes_code_point.back();
				current.name = cpp_name;

				for (auto& v : pt.get_child(name))
				{
					std::string val = v.second.data();
					if (val == "null") val = "4294967295";

					current.data.push_back(val);
				}
			}
		}
	}

	// ポインタ索引表を構築
	std::vector<pointer> indexes_pointer{};
	for (auto const& idx : indexes_code_point)
	{
		pointer p{};
		p.name = idx.name;
		if (p.name == "big5")
		{
			for (uint32_t i = 0; i < idx.data.size(); i++)
			{
				if (i < (0xA1 - 0x81) * 157) continue;
				uint32_t cp = static_cast<uint32_t>(std::stoul(idx.data.at(i)));
				if (cp == 0xFFFFFFFFu) continue;
				if (!(cp == 0x2550 || cp == 0x255E || cp == 0x2561 || cp == 0x256A || cp == 0x5341 || cp == 0x5345))
				{
					if (p.data.find(cp) != p.data.end()) continue;
				}
				p.data.emplace(cp, i);
			}
		}
		else
		{
			for (uint32_t i = 0; i < idx.data.size(); i++)
			{
				uint32_t cp = static_cast<uint32_t>(std::stoul(idx.data.at(i)));
				if (cp == 0xFFFFFFFFu) continue;
				if (p.data.find(cp) != p.data.end()) continue;
				p.data.emplace(cp, i);
			}
		}
		indexes_pointer.push_back(p);
	}

	pointer gb18030_pointer{};
	{
		gb18030_pointer.name = gb18030_code_point.name;
		for (auto const& pair : gb18030_code_point.data)
		{
			uint32_t pointer = static_cast<uint32_t>(std::stoul(pair.first));
			uint32_t cp = static_cast<uint32_t>(std::stoul(pair.second));
			if (cp == 0xFFFFFFFFu) continue;
			gb18030_pointer.data.emplace(cp, pointer);
		}
	}

	// indexes.hpp を作成
	{
		std::ofstream hpp{};
		hpp.open(TO_STRING(INDEXES_HPP_PATH), std::ios::out);

		// 導入部
		hpp << "#pragma once" << std::endl;
		hpp << u8"// generated by wordring_cpp/generator/whatwg/encoding/encoding.cpp" << std::endl;
		hpp << std::endl;
		hpp << "#include <map>" << std::endl;
		hpp << "#include <vector>" << std::endl;
		hpp << std::endl;

		hpp << "namespace wordring::whatwg::encoding" << std::endl;
		hpp << "{" << std::endl;

		// index code point部
		for (auto const& idx : indexes_code_point) hpp << "\textern std::vector<uint32_t> const index_code_point_" << idx.name << "; // " << idx.data.size() << std::endl;
		hpp << std::endl;
		hpp << "\textern std::multimap<uint32_t, uint32_t> const index_code_point_" << gb18030_code_point.name << "; // " << gb18030_code_point.data.size() << std::endl;
		hpp << std::endl;

		// index pointer部
		for (auto const& idx : indexes_pointer)
		{
			hpp << "\textern std::vector<uint32_t> const index_pointer_" << idx.name << "_0; //" << idx.data.size() << std::endl;
			hpp << "\textern std::vector<uint16_t> const index_pointer_" << idx.name << "_1; //" << idx.data.size() << std::endl;
		}
		hpp << std::endl;
		hpp << "\textern std::multimap<uint32_t, uint32_t> const index_pointer_" << gb18030_pointer.name << "; // " << gb18030_pointer.data.size() << std::endl;
		hpp << std::endl;

		hpp << "\textern std::vector<uint32_t> const index_pointer_Shift_JIS_0;" << std::endl;
		hpp << "\textern std::vector<uint16_t> const index_pointer_Shift_JIS_1;" << std::endl;

		hpp << "}" << std::endl;
		hpp << std::endl;
	}

	// indexes_code_point.cpp を作成
	{
		std::ofstream cpp{};
		cpp.open(TO_STRING(INDEXES_CODE_POINT_CPP_PATH), std::ios::out);

		// 導入部
		cpp << u8"// generated by wordring_cpp/generator/whatwg/encoding/encoding.cpp" << std::endl;
		cpp << std::endl;
		cpp << "#include \"indexes.hpp\"" << std::endl;
		cpp << std::endl;

		// index code point部
		for (auto const& idx : indexes_code_point)
		{
			cpp << "static std::vector<uint32_t> const wordring::whatwg::encoding::index_code_point_" << idx.name << " { ";
			for (auto const& n : idx.data) cpp << n << "u, ";
			cpp << "};" << std::endl;
		}
		cpp << std::endl;

		cpp << "static std::multimap<uint32_t, uint32_t> const wordring::whatwg::encoding::index_code_point_" << gb18030_code_point.name << " {{ ";
		for (auto const& pair : gb18030_code_point.data) cpp << "{ " << pair.first << "u, " << pair.second << "u }, ";
		cpp << " }};" << std::endl;
		cpp << std::endl;
	}

	// indexes_pointer.cpp を作成
	{
		std::ofstream cpp{};
		cpp.open(TO_STRING(INDEXES_POINTER_CPP_PATH), std::ios::out);

		// 導入部
		cpp << u8"// generated by wordring_cpp/generator/whatwg/encoding/encoding.cpp" << std::endl;
		cpp << std::endl;
		cpp << "#include \"indexes.hpp\"" << std::endl;
		cpp << std::endl;

		// index pointer部
		for (auto const& idx : indexes_pointer)
		{
			cpp << "static std::vector<uint32_t> const wordring::whatwg::encoding::index_pointer_" << idx.name << "_0 { ";
			for (auto const& pair : idx.data) cpp << pair.first << "u, ";
			cpp << "};" << std::endl;
			cpp << "static std::vector<uint16_t> const wordring::whatwg::encoding::index_pointer_" << idx.name << "_1 { ";
			for (auto const& pair : idx.data) cpp << pair.second << "u, ";
			cpp << "};" << std::endl;
			cpp << std::endl;
		}

		cpp << "static std::multimap<uint32_t, uint32_t> const wordring::whatwg::encoding::index_pointer_" << gb18030_pointer.name << " {{ ";
		for (auto const& pair : gb18030_pointer.data) cpp << "{ " << pair.first << "u, " << pair.second << "u }, ";
		cpp << " }};" << std::endl;
		cpp << std::endl;

		auto it = std::find_if(indexes_pointer.begin(), indexes_pointer.end(), [](pointer const& p) { return p.name == "jis0208"; });
		assert(it != indexes_pointer.end());
		cpp << "static std::vector<uint32_t> const wordring::whatwg::encoding::index_pointer_Shift_JIS_0 { ";
		for (auto const& pair : it->data) cpp << pair.first << "u, ";
		cpp << "};" << std::endl;
		cpp << "static std::vector<uint16_t> const wordring::whatwg::encoding::index_pointer_Shift_JIS_1 { ";
		for (auto const& pair : it->data) cpp << pair.second << "u, ";
		cpp << "};" << std::endl;
		cpp << std::endl;
	}

	return 0;
}