topic "StringBuffer and WStringBuffer";
[2 $$0,0#00000000000000000000000000000000:Default]
[i448;a25;kKO9;2 $$1,0#37138531426314131252341829483380:class]
[l288;2 $$2,0#27521748481378242620020725143825:desc]
[0 $$3,0#96390100711032703541132217272105:end]
[H6;0 $$4,0#05600065144404261032431302351956:begin]
[i448;a25;kKO9;2 $$5,0#37138531426314131252341829483370:item]
[l288;a4;*@5;1 $$6,6#70004532496200323422659154056402:requirement]
[l288;i1121;b17;O9;~~~.1408;2 $$7,0#10431211400427159095818037425705:param]
[i448;b42;O9;2 $$8,8#61672508125594000341940100500538:tparam]
[b42;2 $$9,9#13035079074754324216151401829390:normal]
[{_} 
[ {{10000@(113.42.0) [s0;%% [*@7;4 StringBuffer]]}}&]
[s3;%% &]
[s1;:StringBuffer`:`:class: [@(0.0.255)3 class][3 _][*3 StringBuffer][3 _:_][@(0.0.255)3 private
][3 _][*@3;3 NoCopy]&]
[s9;%% A class useful when working with code that expects a character 
buffer, like C code. It supports constant time pick assignment 
to and from [* String].&]
[s3; &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Constructor Detail]]}}&]
[s3; &]
[s5;:StringBuffer`:`:StringBuffer`(`): [* StringBuffer]()&]
[s2;%% Constructs empty buffer.&]
[s3; &]
[s4; &]
[s5;:StringBuffer`:`:StringBuffer`(int`): [* StringBuffer]([@(0.0.255) int]_[*@3 len])&]
[s2;%% Constructs buffer of [%-*@3 len] characters.&]
[s3;%% &]
[s4; &]
[s5;:StringBuffer`:`:StringBuffer`(String`&`): [* StringBuffer]([_^String^ String][@(0.0.255) `&
]_[*@3 s])&]
[s2;%% Assigns content of [%-*@3 s] to [* StringBuffer]. Clears [%-*@3 s].&]
[s3;%% &]
[s4; &]
[s5;:StringBuffer`:`:`~StringBuffer`(`): [@(0.0.255) `~][* StringBuffer]()&]
[s2;%% Default destructor.&]
[s3; &]
[s0;i448;a25;kKO9;:noref:@(0.0.255) &]
[ {{10000F(128)G(128)@1 [s0;%% [* Public Method List]]}}&]
[s3; &]
[s5;:StringBuffer`:`:Begin`(`): [@(0.0.255) char]_`*[* Begin]()&]
[s2;%% Returns a pointer to the buffer of characters. Mutating operations 
invalidate this pointer.&]
[s3; &]
[s4; &]
[s5;:StringBuffer`:`:End`(`): [@(0.0.255) char]_`*[* End]()&]
[s2;%% Returns Begin() `+ GetCount(). Mutating operations invalidate 
this pointer.&]
[s3; &]
[s4; &]
[s5;:StringBuffer`:`:Cat`(int`): [@(0.0.255) void]_[* Cat]([@(0.0.255) int]_[*@3 c])&]
[s2;%% Appends single character [%-*@3 c].&]
[s3;%% &]
[s4; &]
[s5;:StringBuffer`:`:Cat`(int`,int`): [@(0.0.255) void]_[* Cat]([@(0.0.255) int]_[*@3 c], 
[@(0.0.255) int]_[*@3 count])&]
[s2;%% Appends [%-*@3 count] characters [%-*@3 c].&]
[s3;%% &]
[s4; &]
[s5;:StringBuffer`:`:Cat`(const char`*`): [@(0.0.255) void]_[* Cat]([@(0.0.255) const]_[@(0.0.255) c
har]_`*[*@3 s])&]
[s5;:StringBuffer`:`:Cat`(const String`&`): [@(0.0.255) void]_[* Cat]([@(0.0.255) const]_[_^String^ S
tring][@(0.0.255) `&]_[*@3 s])&]
[s2;%% Appends the string [%-*@3 s].&]
[s3;%% &]
[s4; &]
[s5;:StringBuffer`:`:Cat`(const char`*`,int`): [@(0.0.255) void]_[* Cat]([@(0.0.255) const]_
[@(0.0.255) char]_`*[*@3 s], [@(0.0.255) int]_[*@3 l])&]
[s2;%% Appends the first [%-*@3 l] characters of [%-*@3 s].&]
[s3;%% &]
[s4; &]
[s5;:StringBuffer`:`:Cat`(const char`*`,const char`*`): [@(0.0.255) void]_[* Cat]([@(0.0.255) c
onst]_[@(0.0.255) char]_`*[*@3 s], [@(0.0.255) const]_[@(0.0.255) char]_`*[*@3 e])&]
[s2;%% Same as Cat(s, e `- s).&]
[s3;%% &]
[s4; &]
[s5;:StringBuffer`:`:GetLength`(`)const: [@(0.0.255) int]_[* GetLength]()_[@(0.0.255) const
]&]
[s5;:StringBuffer`:`:GetCount`(`)const: [@(0.0.255) int]_[* GetCount]()_[@(0.0.255) const]&]
[s2;%% Returns the number of characters in the buffer.&]
[s3; &]
[s4; &]
[s5;:StringBuffer`:`:SetLength`(int`): [@(0.0.255) void]_[* SetLength]([@(0.0.255) int]_[*@3 l
])&]
[s5;:StringBuffer`:`:SetCount`(int`): [@(0.0.255) void]_[* SetCount]([@(0.0.255) int]_[*@3 l])
&]
[s2;%% Sets the length of the character buffer to [%-*@3 l].&]
[s3;%% &]
[s4; &]
[s5;:StringBuffer`:`:Strlen`(`): [@(0.0.255) void]_[* Strlen]()&]
[s2;%% Sets the length of the character buffer to the length of the 
zero terminated string stored in the buffer (up to the first 
zero character). Useful for converting C strings returned from 
system to String.&]
[s3; &]
[s4; &]
[s5;:StringBuffer`:`:Clear`(`): [@(0.0.255) void]_[* Clear]()&]
[s2;%% Clears the contents of the string buffer.&]
[s3; &]
[s4; &]
[s5;:StringBuffer`:`:Reserve`(int`): [@(0.0.255) void]_[* Reserve]([@(0.0.255) int]_[*@3 r])&]
[s2;%% Hint to preallocate internal buffer for concatenation of next 
r characters.&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:StringBuffer`:`:Shrink`(`): [@(0.0.255) void]_[* Shrink]()&]
[s2;%% Shrinks the internal buffer to minimize memory consumption.&]
[s3; &]
[s4; &]
[s5;:StringBuffer`:`:GetAlloc`(`)const: [@(0.0.255) int]_[* GetAlloc]()_[@(0.0.255) const]&]
[s2;%% Returns the maximum number of characters in the internal buffer.&]
[s3; &]
[s4; &]
[s5;:StringBuffer`:`:operator char`*`(`): [* operator_char`*]()&]
[s5;:StringBuffer`:`:operator`~`(`): [@(0.0.255) char]_`*[* operator`~]()&]
[s2;%% Returns [* Begin]().&]
[s3; &]
[s4; &]
[s5;:StringBuffer`:`:operator`=`(String`&`): [@(0.0.255) void]_[* operator`=]([_^String^ St
ring][@(0.0.255) `&]_[*@3 s])&]
[s2;%% Clears the string buffer and assigns the content of [%-*@3 s]. 
Clears [%-*@3 s].&]
[s3; &]
[s0; &]
[s0; &]
[s0; &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 WStringBuffer]]}}&]
[s3; &]
[s1;:WStringBuffer`:`:class: [@(0.0.255)3 class][3 _][*3 WStringBuffer][3 _:_][@(0.0.255)3 priva
te][3 _][*@3;3 NoCopy]&]
[s9;%% A class useful when working with code that expects a wide 
character buffer, like C code. It supports constant time pick 
assignment to and from [* WString].&]
[s3; &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Constructor Detail]]}}&]
[s3; &]
[s5;:WStringBuffer`:`:WStringBuffer`(`): [* WStringBuffer]()&]
[s2;%% Constructs empty buffer.&]
[s3; &]
[s4; &]
[s5;:WStringBuffer`:`:WStringBuffer`(int`): [* WStringBuffer]([@(0.0.255) int]_[*@3 len])&]
[s2;%% Constructs buffer of [%-*@3 len] characters.&]
[s3;%% &]
[s4; &]
[s5;:WStringBuffer`:`:WStringBuffer`(WString`&`): [* WStringBuffer]([_^WString^ WString][@(0.0.255) `&
]_[*@3 s])&]
[s2;%% Assigns content of [%-*@3 s] to [* StringBuffer]. Clears [%-*@3 s].&]
[s3;%% &]
[s4; &]
[s5;:WStringBuffer`:`:`~WStringBuffer`(`): [@(0.0.255) `~][* WStringBuffer]()&]
[s2;%% Default destructor.&]
[s3; &]
[s0;i448;a25;kKO9;:noref:@(0.0.255) &]
[ {{10000F(128)G(128)@1 [s0;%% [* Public Method List]]}}&]
[s3; &]
[s5;:WStringBuffer`:`:Begin`(`): [_^wchar^ wchar]_`*[* Begin]()&]
[s2;%% Returns a pointer to the buffer of characters. Mutating operations 
invalidate this pointer.&]
[s3; &]
[s4; &]
[s5;:WStringBuffer`:`:End`(`): [_^wchar^ wchar]_`*[* End]()&]
[s2;%% Returns Begin() `+ GetCount(). Mutating operations invalidate 
this pointer.&]
[s3; &]
[s4; &]
[s5;:WStringBuffer`:`:Cat`(int`): [@(0.0.255) void]_[* Cat]([@(0.0.255) int]_[*@3 c])&]
[s2;%% Appends single character [%-*@3 c].&]
[s3;%% &]
[s4; &]
[s5;:WStringBuffer`:`:Cat`(int`,int`): [@(0.0.255) void]_[* Cat]([@(0.0.255) int]_[*@3 c], 
[@(0.0.255) int]_[*@3 count])&]
[s2;%% Appends [%-*@3 count] characters [%-*@3 c].&]
[s3;%% &]
[s4; &]
[s5;:WStringBuffer`:`:Cat`(const wchar`*`): [@(0.0.255) void]_[* Cat]([@(0.0.255) const]_[_^wchar^ w
char]_`*[*@3 s])&]
[s5;:WStringBuffer`:`:Cat`(const WString`&`): [@(0.0.255) void]_[* Cat]([@(0.0.255) const]_
[_^WString^ WString][@(0.0.255) `&]_[*@3 s])&]
[s5;:WStringBuffer`:`:Cat`(const char`*`): [@(0.0.255) void]_[* Cat]([@(0.0.255) const]_[@(0.0.255) c
har]_`*[*@3 s])&]
[s2;%% Appends the string [%-*@3 s].&]
[s3;%% &]
[s4; &]
[s5;:WStringBuffer`:`:Cat`(const wchar`*`,int`): [@(0.0.255) void]_[* Cat]([@(0.0.255) cons
t]_[_^wchar^ wchar]_`*[*@3 s], [@(0.0.255) int]_[*@3 l])&]
[s2;%% Appends the first [%-*@3 l] characters of [%-*@3 s].&]
[s3;%% &]
[s4; &]
[s5;:WStringBuffer`:`:Cat`(const wchar`*`,const wchar`*`): [@(0.0.255) void]_[* Cat]([@(0.0.255) c
onst]_[_^wchar^ wchar]_`*[*@3 s], [@(0.0.255) const]_[_^wchar^ wchar]_`*[*@3 e])&]
[s2;%% Same as Cat([%-*@3 s], [%-*@3 e] `- [%-*@3 s]).&]
[s3;%% &]
[s4; &]
[s5;:WStringBuffer`:`:GetLength`(`)const: [@(0.0.255) int]_[* GetLength]()_[@(0.0.255) cons
t]&]
[s5;:WStringBuffer`:`:GetCount`(`)const: [@(0.0.255) int]_[* GetCount]()_[@(0.0.255) const]&]
[s2;%% Returns the number of characters in the buffer.&]
[s3; &]
[s4; &]
[s5;:WStringBuffer`:`:SetLength`(int`): [@(0.0.255) void]_[* SetLength]([@(0.0.255) int]_[*@3 l
])&]
[s5;:WStringBuffer`:`:SetCount`(int`): [@(0.0.255) void]_[* SetCount]([@(0.0.255) int]_[*@3 l
])&]
[s2;%% Sets the length of the character buffer to [%-*@3 l].&]
[s3;%% &]
[s4; &]
[s5;:WStringBuffer`:`:Strlen`(`): [@(0.0.255) void]_[* Strlen]()&]
[s2;%% Sets the length of the character buffer to the length of the 
zero terminated string stored in the buffer (up to the first 
zero character). Useful for converting C strings returned from 
system to String.&]
[s3; &]
[s4; &]
[s5;:WStringBuffer`:`:Clear`(`): [@(0.0.255) void]_[* Clear]()&]
[s2;%% Clears the contents of the string buffer.&]
[s3; &]
[s4; &]
[s5;:WStringBuffer`:`:Reserve`(int`): [@(0.0.255) void]_[* Reserve]([@(0.0.255) int]_[*@3 r])
&]
[s2;%% Preallocates internal buffer (avoids resizing of internal 
buffer up to [%-*@3 r] characters).&]
[s3;%% &]
[s4; &]
[s5;:WStringBuffer`:`:GetAlloc`(`)const: [@(0.0.255) int]_[* GetAlloc]()_[@(0.0.255) const]&]
[s2;%% Returns the maximum number of characters in the internal buffer.&]
[s3; &]
[s4; &]
[s5;:WStringBuffer`:`:operator wchar`*`(`): [* operator_wchar`*]()&]
[s5;:WStringBuffer`:`:operator`~`(`): [_^wchar^ wchar]_`*[* operator`~]()&]
[s2;%% Returns [* Begin]().&]
[s3; &]
[s4; &]
[s5;:WStringBuffer`:`:operator`=`(WString`&`): [@(0.0.255) void]_[* operator`=]([_^WString^ W
String][@(0.0.255) `&]_[*@3 s])&]
[s2;%% Clears the string buffer and assigns the content of [%-*@3 s]. 
Clears [%-*@3 s].&]
[s3; &]
[s0; ]]