﻿# test/
#
# このプロジェクトは libwordring ライブラリ配下のテストをすべて作成します。
#

cmake_minimum_required (VERSION 3.12)

#[[
add_subdirectory("css")
add_subdirectory("encoding")
add_subdirectory("html")
add_subdirectory("serialize")
add_subdirectory("static_vector")
add_subdirectory("std")
add_subdirectory("string")

add_subdirectory("tag_tree")
add_subdirectory("tree")
add_subdirectory("trie")
]]
add_subdirectory("whatwg")
#add_subdirectory("wwwc")

