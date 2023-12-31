topic "U++ Code vs standard C++ library";
[b42;a42;ph2 $$1,1#45413000475342174754091244180557:text]
[ $$0,0#00000000000000000000000000000000:Default]
[{_}%EN-US 
[s0; [*R6 U`+`+ Core vs standard C`+`+ library]&]
[s1; U`+`+ can be easily accused of reinventing the wheel. While 
the main reason of not using standard C`+`+ library is not quite 
performance related, the interface definition of U`+`+ containers 
allows very effective implementation. Matched with U`+`+ heap 
allocator which overloads global new and delete operators, U`+`+ 
is able to boost the speed of applications a bit.&]
[s1; In the benchmark example, we are comparing `"out`-of`-box`" 
performance of standard library implementations coming with widely 
used compilers with performance of U`+`+ Core with the same compilers 
in simple example. The purpose of code is to scan through file, 
find all identifiers (by C lexical definition) and print them 
sorted by the name, with list of lines where they occur.&]
[s0;2 &]
[s0; [2 Implementation use std`::map, std`::tr1`::unordered`_map (or equivalent 
stdext`::hash`_map with microsoft compiler) with std`::string and 
standard library streams and U`+`+ container VectorMap with UPP`::String 
and U`+`+ streams, tested with both U`+`+ and standard library 
heap allocator.]&]
[s0;*/2 &]
[s0; [*/2 ratio U`+`+/std][2  column shows how many times is U`+`+ Core 
VectorMap container based solution faster then the standard solution 
with the library that comes with the compiler (best of map/hash`_map 
times is considered).]&]
[s0;2 &]
[s0; [*/@(128.0.255)2 ratio U`+`+/STL][2  column shows how many times 
is U`+`+ Core based solution faster then the STL solution when 
using U`+`+ allocator, because STL containers also benefit from 
it (best of map/hash`_map times is considered).]&]
[s0;2 &]
[s0; [2 Perhaps if the reinvented wheel spins about 4 times faster, 
reinventing is not that bad idea...]&]
[s0;2 &]
[s0;2 &]
[s0; [* Results]&]
[s0;2 &]
[s0; [2 Test with 3.93 KB .cpp file:]&]
[s0;2 &]
[ {{1203:1269:1626:948:1572:1152:1066:1164h2;@(216) [s0; [*+75 allocator]]
::-1 [s0;= [+75 standard]]
::@2 [s0;%- ]
::@(216)-2 [s0;= [+75 U`+`+]]
::@2-1 [s0;%- ]
:: [s0;%- ]
::@(216)|1 [s0;%- [*/+75 ratio]&]
[s0;%- [*/+75 U`+`+/std]]
::|1 [s0;%- [*/@(128.0.255)+75 ratio]&]
[s0;%- [*/@(128.0.255)+75 U`+`+/STL]]
:: [s0; [*+75 code]]
:: [s0;= [+75 map]]
:: [s0;= [+75 unordered`_map]]
:: [s0;= [+75 map]]
:: [s0;= [+75 unordered`_map]]
:: [s0;= [+75 U`+`+]]
::@2 [s0;%- ]
:: [s0;%- ]
:: [s0; [+75 GCC32]]
:: [s0;= [+75 5.3 s]]
:: [s0;= [*_+75 4.9 s]]
:: [s0;= [+75 4.4 s]]
:: [s0;= [*_@(128.0.255)+75 3.9 s]]
:: [s0;= [*_+75 1.1 s]]
:: [s0;= [*_+75 4.5]]
:: [s0;= [*_@(128.0.255)+75 3.5]]
:: [s0; [+75 GCC64]]
:: [s0;= [+75 4.2 s]]
:: [s0;= [*_+75 3.7 s]]
:: [s0;= [+75 3.2 s]]
:: [s0;= [*_@(128.0.255)+75 3.0 s]]
:: [s0;= [*_+75 0.8 s]]
:: [s0;= [*_+75 4.6]]
:: [s0;= [*_@(128.0.255)+75 3.8]]}}&]
[s0;2 &]
[s0;2 &]
[s0; [2 Test with 58 KB .cpp file:]&]
[s0;2 &]
[ {{1261:1256:1695:831:1626:1088:1067:1176h2;@(216) [s0; [*+75 allocator]]
::-1 [s0;= [+75 standard]]
::@2 [s0;%- ]
::@(216)-2 [s0;= [+75 U`+`+]]
::@2-1 [s0;%- ]
:: [s0;%- ]
::@(216)|1 [s0;%- [*/+75 ratio]&]
[s0;%- [*/+75 U`+`+/std]]
::|1 [s0;%- [*/@(128.0.255)+75 ratio]&]
[s0;%- [*/@(128.0.255)+75 U`+`+/STL]]
:: [s0; [*+75 code]]
:: [s0;= [+75 map]]
:: [s0;= [+75 unordered`_map]]
:: [s0;= [+75 map]]
:: [s0;= [+75 unordered`_map]]
:: [s0;= [+75 U`+`+]]
::@2 [s0;%- ]
:: [s0;%- ]
:: [s0; [+75 GCC32]]
:: [s0;= [+75 70 s]]
:: [s0;= [*_+75 56 s]]
:: [s0;= [+75 58 s]]
:: [s0;= [*_@(128.0.255)+75 45 s]]
:: [s0;= [*_+75 11 s]]
:: [s0;= [*_+75 5.1]]
:: [s0;= [*_@(128.0.255)+75 4.1]]
:: [s0; [+75 GCC64]]
:: [s0;= [+75 55 s]]
:: [s0;= [*_+75 43 s]]
:: [s0;= [+75 45 s]]
:: [s0;= [*_@(128.0.255)+75 34 s]]
:: [s0;= [*_+75 8.8 s]]
:: [s0;= [*_+75 4.9]]
:: [s0;= [*_@(128.0.255)+75 3.9]]}}&]
[s0;2 &]
[s0;2 &]
[s0; [*_2 Platforms]&]
[s0;*_2 &]
[ {{972:9028^ [s0; [+75 GCC64]]
::= [s0; [+75 Ubuntu 7.10 AMD64]&]
[s0; [+75 (GCC) 4.1.3 20070929 (prerelease) (Ubuntu 4.1.2`-16ubuntu2)]&]
[s0; [/+75 compiler options:][+75  `-O3]]
::^ [s0; [+75 GCC32]]
::= [s0; [+75 Ubuntu 7.10 i386]&]
[s0; [+75 (GCC) 4.1.3 20070929 (prerelease) (Ubuntu 4.1.2`-16ubuntu2)]&]
[s0; [/+75 compiler options:][+75  `-O3]]}}&]
[s0;2 &]
[s0; [*/2 Hardware:][2  Core 2 Duo, 2.7 Ghz, 2GB RAM]&]
[s0;2 &]
[s0;2 &]
[s0; [*_2 Benchmark code]&]
[s0;*/2 &]
[ {{10000@(254.254.208) [s0; [*C@5;2 #define  NDEBUG]&]
[s0; [*C@5;2 #define  `_SECURE`_SCL 0]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 #include <Core/Core.h>]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 #include <stdio.h>]&]
[s0; [*C@5;2 #include <iostream>]&]
[s0; [*C@5;2 #include <fstream>]&]
[s0; [*C@5;2 #include <time.h>]&]
[s0; [*C@5;2 #include <vector>]&]
[s0; [*C@5;2 #include <algorithm>]&]
[s0; [*C@5;2 #include <map>]&]
[s0; [*C@5;2 #include <deque>]&]
[s0; [*C@5;2 #include <string>]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 #define TEST`_HASHMAP]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 #ifdef TEST`_HASHMAP]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 #ifdef COMPILER`_GCC]&]
[s0; [*C@5;2 #include <tr1/unordered`_map>]&]
[s0; [*C@5;2 #else]&]
[s0; [*C@5;2 #include <hash`_map>]&]
[s0; [*C@5;2 #endif]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 #endif]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 using namespace std;]&]
[s0; [*C@5;2 using namespace Upp;]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 #define NO`_OUTPUT // for benchmark purposes, output is 
omitted]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 void BenchNTL(const char `*file) `{]&]
[s0; [*C@5;2 -|FileIn in(file);]&]
[s0; [*C@5;2 -|if (!in) `{]&]
[s0; [*C@5;2 -|-|std`::cout << `"Cannot open input file.`\n`";]&]
[s0; [*C@5;2 -|-|return;]&]
[s0; [*C@5;2 -|`}]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 -|VectorMap<String, Vector<int> > map;]&]
[s0; [*C@5;2 -|int line `= 1;]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 -|for(;;) `{]&]
[s0; [*C@5;2 -|-|int c `= in.Get();]&]
[s0; [*C@5;2 -|-|if(c < 0) break;]&]
[s0; [*C@5;2 -|-|if(isalpha(c) `|`| c `=`= `'`_`') `{]&]
[s0; [*C@5;2 -|-|-|String id;]&]
[s0; [*C@5;2 -|-|-|id.Cat(c);]&]
[s0; [*C@5;2 -|-|-|c `= in.Get();]&]
[s0; [*C@5;2 -|-|-|while(c >`= 0 `&`& (isalnum(c) `|`| c `=`= `'`_`')) 
`{]&]
[s0; [*C@5;2 -|-|-|-|id.Cat(c);]&]
[s0; [*C@5;2 -|-|-|-|c `= in.Get();]&]
[s0; [*C@5;2 -|-|-|`}]&]
[s0; [*C@5;2 -|-|-|map.GetAdd(id).Add(line);]&]
[s0; [*C@5;2 -|-|`}]&]
[s0; [*C@5;2 -|-|else]&]
[s0; [*C@5;2 -|-|if(isdigit(c))]&]
[s0; [*C@5;2 -|-|-|do c `= in.Get();]&]
[s0; [*C@5;2 -|-|-|while(c >`= 0 `&`& (isalnum(c) `|`| c `=`= `'.`'));]&]
[s0; [*C@5;2 -|-|if(c `=`= `'`\n`')]&]
[s0; [*C@5;2 -|-|-|`+`+line;]&]
[s0; [*C@5;2 -|`}]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 -|Vector<int> order `= GetSortOrder(map.GetKeys());]&]
[s0; [*C@5;2 #ifndef NO`_OUTPUT]&]
[s0; [*C@5;2 -|for(int i `= 0; i < order.GetCount(); i`+`+) `{]&]
[s0; [*C@5;2 -|-|std`::cout << `~map.GetKey(order`[i`]) << `": `";]&]
[s0; [*C@5;2 -|-|const Vector<int>`& l `= map`[order`[i`]`];]&]
[s0; [*C@5;2 -|-|for(int i `= 0; i < l.GetCount(); i`+`+) `{]&]
[s0; [*C@5;2 -|-|-|if(i) std`::cout << `", `";]&]
[s0; [*C@5;2 -|-|-|std`::cout << l`[i`];]&]
[s0; [*C@5;2 -|-|`}]&]
[s0; [*C@5;2 -|-|std`::cout << `'`\n`';]&]
[s0; [*C@5;2 -|`}]&]
[s0; [*C@5;2 #endif]&]
[s0; [*C@5;2 `}]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 template <class Container>]&]
[s0; [*C@5;2 void BenchSTL(Container`& imap, const char `*file) `{]&]
[s0; [*C@5;2 -|std`::ifstream in(file);]&]
[s0; [*C@5;2 -|if (!in) `{]&]
[s0; [*C@5;2 -|-|std`::cout << `"Cannot open input file.`\n`";]&]
[s0; [*C@5;2 -|-|return;]&]
[s0; [*C@5;2 -|`}]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 -|int line `= 1;]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 -|for(;;) `{]&]
[s0; [*C@5;2 -|-|int c `= in.get();]&]
[s0; [*C@5;2 -|-|if(c `=`= EOF) break;]&]
[s0; [*C@5;2 -|-|if(isalpha(c) `|`| c `=`= `'`_`') `{]&]
[s0; [*C@5;2 -|-|-|string id;]&]
[s0; [*C@5;2 -|-|-|id `+`= c;]&]
[s0; [*C@5;2 -|-|-|c `= in.get();]&]
[s0; [*C@5;2 -|-|-|while(c !`= EOF `&`& (isalnum(c) `|`| c `=`= `'`_`')) 
`{]&]
[s0; [*C@5;2 -|-|-|-|id `+`= c;]&]
[s0; [*C@5;2 -|-|-|-|c `= in.get();]&]
[s0; [*C@5;2 -|-|-|`}]&]
[s0; [*C@5;2 -|-|-|imap`[id`].push`_back(line);]&]
[s0; [*C@5;2 -|-|`}]&]
[s0; [*C@5;2 -|-|else]&]
[s0; [*C@5;2 -|-|if(isdigit(c))]&]
[s0; [*C@5;2 -|-|-|do c `= in.get();]&]
[s0; [*C@5;2 -|-|-|while(c !`= EOF `&`& (isalnum(c) `|`| c `=`= `'.`'));]&]
[s0; [*C@5;2 -|-|if(c `=`= `'`\n`')]&]
[s0; [*C@5;2 -|-|-|`+`+line;]&]
[s0; [*C@5;2 -|`}]&]
[s0; [*C@5;2 `}]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 void BenchMap(const char `*file)]&]
[s0; [*C@5;2 `{]&]
[s0; [*C@5;2 -|map< string, vector<int> > imap;]&]
[s0; [*C@5;2 -|BenchSTL(imap, file);]&]
[s0; [*C@5;2 #ifndef NO`_OUTPUT]&]
[s0; [*C@5;2 -|map< std`::string, vector<int> >`::const`_iterator e `= 
imap.end();]&]
[s0; [*C@5;2 -|for(map< std`::string, vector<int> >`::const`_iterator 
i `= imap.begin(); i !`= e; i`+`+) `{]&]
[s0; [*C@5;2 -|-|std`::cout << i`->first << `": `";]&]
[s0; [*C@5;2 -|-|vector<int>`::const`_iterator e `= i`->second.end();]&]
[s0; [*C@5;2 -|-|vector<int>`::const`_iterator b `= i`->second.begin();]&]
[s0; [*C@5;2 -|-|for(vector<int>`::const`_iterator j `= b; j !`= e; j`+`+) 
`{]&]
[s0; [*C@5;2 -|-|-|if(j !`= b) std`::cout << `", `";]&]
[s0; [*C@5;2 -|-|-|std`::cout << `*j;]&]
[s0; [*C@5;2 -|-|`}]&]
[s0; [*C@5;2 -|-|std`::cout << `'`\n`';]&]
[s0; [*C@5;2 -|`}]&]
[s0; [*C@5;2 #endif]&]
[s0; [*C@5;2 `}]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 #ifdef TEST`_HASHMAP]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 #ifdef COMPILER`_GCC]&]
[s0; [*C@5;2 typedef std`::tr1`::unordered`_map< string, vector<int> 
> HashMap;]&]
[s0; [*C@5;2 #else]&]
[s0; [*C@5;2 typedef stdext`::hash`_map< string, vector<int> > HashMap;]&]
[s0; [*C@5;2 #endif]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 inline bool h`_less(const HashMap`::value`_type `*a, const 
HashMap`::value`_type `*b)]&]
[s0; [*C@5;2 `{]&]
[s0; [*C@5;2 -|return a`->first < b`->first;]&]
[s0; [*C@5;2 `}]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 void BenchHashMap(const char `*file)]&]
[s0; [*C@5;2 `{]&]
[s0; [*C@5;2 -|HashMap imap;]&]
[s0; [*C@5;2 -|BenchSTL(imap, file);]&]
[s0; [*C@5;2 -|vector< const HashMap`::value`_type `* > order;]&]
[s0; [*C@5;2 -|for(HashMap`::const`_iterator i `= imap.begin(); i !`= 
imap.end(); i`+`+)]&]
[s0; [*C@5;2 -|-|order.push`_back(`&`*i);]&]
[s0; [*C@5;2 -|sort(order.begin(), order.end(), h`_less);]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 #ifndef NO`_OUTPUT]&]
[s0; [*C@5;2 -|vector< const HashMap`::value`_type `* >`::const`_iterator 
e `= order.end();]&]
[s0; [*C@5;2 -|for(vector< const HashMap`::value`_type `* >`::const`_iterator 
i `= order.begin(); i !`= e; i`+`+) `{]&]
[s0; [*C@5;2 -|-|std`::cout << (`*i)`->first << `": `";]&]
[s0; [*C@5;2 -|-|vector<int>`::const`_iterator e `= (`*i)`->second.end();]&]
[s0; [*C@5;2 -|-|vector<int>`::const`_iterator b `= (`*i)`->second.begin();]&]
[s0; [*C@5;2 -|-|for(vector<int>`::const`_iterator j `= b; j !`= e; j`+`+) 
`{]&]
[s0; [*C@5;2 -|-|-|if(j !`= b) std`::cout << `", `";]&]
[s0; [*C@5;2 -|-|-|std`::cout << `*j;]&]
[s0; [*C@5;2 -|-|`}]&]
[s0; [*C@5;2 -|-|std`::cout << `'`\n`';]&]
[s0; [*C@5;2 -|`}]&]
[s0; [*C@5;2 #endif]&]
[s0; [*C@5;2 `}]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 #endif]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 #define N 10000]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 CONSOLE`_APP`_MAIN]&]
[s0; [*C@5;2 `{]&]
[s0; [*C@5;2 -|String fn;]&]
[s0; [*C@5;2 -|int argc `= CommandLine().GetCount();]&]
[s0; [*C@5;2 -|const Vector<String>`& argv `= CommandLine();]&]
[s0; [*C@5;2 -|if(argc < 1)]&]
[s0; [*C@5;2 -|-|fn `= GetDataFile(`"main.cpp`");]&]
[s0; [*C@5;2 -|else]&]
[s0; [*C@5;2 -|-|fn `= argv`[0`];]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 -|BenchNTL(fn); // first run to cache the file]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 #ifdef TEST`_HASHMAP]&]
[s0; [*C@5;2 -|`{]&]
[s0; [*C@5;2 -|-|BenchHashMap(fn);]&]
[s0; [*C@5;2 -|-|TimeStop tm;]&]
[s0; [*C@5;2 -|-|for(int n `= 0; n < N; n`+`+)]&]
[s0; [*C@5;2 -|-|-|BenchHashMap(fn);]&]
[s0; [*C@5;2 -|-|cout << `"STL hash`_map time: `" << tm.Elapsed() << `" 
ms `\n`";]&]
[s0; [*C@5;2 -|`}]&]
[s0; [*C@5;2 #endif]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 -|`{]&]
[s0; [*C@5;2 -|-|BenchMap(fn);]&]
[s0; [*C@5;2 -|-|TimeStop tm;]&]
[s0; [*C@5;2 -|-|for(int n `= 0; n < N; n`+`+)]&]
[s0; [*C@5;2 -|-|-|BenchMap(fn);]&]
[s0; [*C@5;2 -|-|cout << `"STL map time: `" << tm.Elapsed() << `" ms `\n`";]&]
[s0; [*C@5;2 -|`}]&]
[s0;*C@5;2 &]
[s0; [*C@5;2 -|`{]&]
[s0; [*C@5;2 -|-|BenchNTL(fn);]&]
[s0; [*C@5;2 -|-|TimeStop tm;]&]
[s0; [*C@5;2 -|-|for(int n `= 0; n < N; n`+`+)]&]
[s0; [*C@5;2 -|-|-|BenchNTL(fn);]&]
[s0; [*C@5;2 -|-|cout << `"NTL time: `" << tm.Elapsed() << `" ms`\n`";]&]
[s0; [*C@5;2 -|`}]&]
[s0; [*C@5;2 `}]&]
[s0; ]}}&]
[s0; ]]