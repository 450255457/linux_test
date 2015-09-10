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
		cout << "upload_id = " << upload_id
			<< " code = " << code << endl;
	}
	return 0;
}

void readJson() {
	using namespace std;
	std::string strValue = "{\"name\":\"json\",\"array\":[{\"cpp\":\"jsoncpp\"},{\"java\":\"jsoninjava\"},{\"php\":\"support\"}]}";

	Json::Reader reader;
	Json::Value value;

	if (reader.parse(strValue, value))
	{
		std::string out = value["name"].asString();
		std::cout << out << std::endl;
		const Json::Value arrayObj = value["array"];
		for (unsigned int i = 0; i < arrayObj.size(); i++)
		{
			if (!arrayObj[i].isMember("cpp"))
				continue;
			out = arrayObj[i]["cpp"].asString();
			std::cout << out;
			if (i != (arrayObj.size() - 1))
				std::cout << std::endl;
		}
	}
}

void writeJson() {
	using namespace std;

	Json::Value root;
	Json::Value arrayObj;
	Json::Value item;

	item["cpp"] = "jsoncpp";
	item["java"] = "jsoninjava";
	item["php"] = "support";
	arrayObj.append(item);

	root["name"] = "json";
	root["array"] = arrayObj;

	// 转换为字符串（带格式）
	//root.toStyledString();
	//std::string out = root.toStyledString();
	// 输出无格式json字符串
	Json::FastWriter writer;
	std::string out = writer.write(root);
	std::cout << out << std::endl;
}

int main()
{
	writeJson();
	//readJson();
	//ParseJsonFromString();
//	string test = "{\"id\":1,\"name\":\"kurama\"}";
//	Json::Reader reader;
//	Json::Value value;
//	if (reader.parse(test, value))
//	{
//		if (!value["id"].isNull())
//		{
//			cout << value["id"].asInt() << endl;
//			cout << value["name"].asString() << endl;
//		}
//	}
	return 0;
}