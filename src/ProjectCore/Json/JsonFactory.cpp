
#include "JsonFactory.h"

#include "ProjectCore//FMT/Detail/Buffer/BufferOutManager/DynamicBufferOutManager.h"

#include <fstream>
#include <utility>

#include "Serializers/JsonObjectsSerializer.h"

namespace ProjectCore::JSON
{
    std::unique_ptr<JsonObject> JsonFactory::FromPath(const std::filesystem::path& path)
    {
        std::ifstream file(path.string(), std::ios::in);
        
        if (file.is_open() == false)
            throw std::runtime_error("unable to open file");
        
        std::string buffer;

        file.seekg(0, std::ios::end);
        std::size_t size = file.tellg();
        file.seekg(0, std::ios::beg);
        buffer.resize(size);
        file.read(buffer.data(), size);
        file.close();

        FMT::Detail::BufferInProperties<char> parserProperties(buffer.data(), buffer.size());
        Detail::JsonParser parser(parserProperties);
        std::unique_ptr<JsonObject> res;
        JsonSerializer<std::unique_ptr<JsonObject>>::Parse(res, parser);
        return res;
    }
    
    void JsonFactory::SaveToPath(JsonObject& json, const std::filesystem::path& path)
    {
		std::ofstream file(path.string(), std::ios::out);

		if (file.is_open() == false)
			throw std::runtime_error("unable to open file");

        FMT::Detail::DynamicBufferOutManager<char> BufferOutManager(256);
        Detail::JsonFormatter formatter(BufferOutManager);
        JsonSerializer<JsonObject>::Format(json, formatter);
        
		file.write(BufferOutManager.GetBuffer(), BufferOutManager.GetLastGeneratedDataSize());
		file.flush();
        file.close();
    }
}
