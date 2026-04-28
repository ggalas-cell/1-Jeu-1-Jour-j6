#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

class Json {

	json data;
	
public:
	void LoadFile(const char* path);

	template <typename T>
	T GetData(std::string key) {
		return data.at(key).get<T>();
	}
};