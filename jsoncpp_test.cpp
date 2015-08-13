//g++ -g -o jsoncpp_test jsoncpp_test.cpp /usr/lib/libjson_linux-gcc-4.8_libmt.a

#include <json/json.h>
#include <string>
#include <iostream>

using namespace std;

int ParseJsonFromString()
{
	const char* str = "{\"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}";

	Json::Reader reader;
	Json::Value root;
	if (reader.parse(str, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素  
	{
		std::string upload_id = root["uploadid"].asString();  // 访问节点，upload_id = "UP000000"  
		int code = root["code"].asInt();    // 访问节点，code = 100  
	}
	return 0;
}

int main()
{
	ParseJsonFromString();
	string test = "{\"id\":1,\"name\":\"kurama\"}";
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(test, value))
	{
		if (!value["id"].isNull())
		{
			cout << value["id"].asInt() << endl;
			cout << value["name"].asString() << endl;
		}
	}
	return 0;
}