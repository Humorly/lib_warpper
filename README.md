// 假设动态库中提供接口：
int add(int a, int b) { return a + b; }

1：链接动态库过程()
// 指定链接库文件 test.dll / test.so
wstd::lib_warpper lib_warpper_("test");

2：获取动态库接口
// 获取其中接口
std::function<int(int, int)> tt_ = std::bind(lib_warpper_.get_function<int (int, int)>("add"), 
		std::placeholders::_1, std::placeholders::_2);

3：使用接口
auto value_ = tt_(1, 11234);
