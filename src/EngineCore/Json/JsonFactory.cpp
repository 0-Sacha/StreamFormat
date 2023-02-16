
#include "JsonFactory.h"

#include "EngineCore//FMT/Detail/Buffer/BasicBufferOut/BufferManager/DynamicBufferManager.h"

#include <fstream>
#include <utility>

#include "JsonObjectsSerializer.h"

namespace EngineCore::JSON
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

        Detail::JsonParser parser(buffer.data(), buffer.size());
        std::unique_ptr<JsonObject> res;
        JsonSerializer<std::unique_ptr<JsonObject>>::Load(res, parser);
        return res;
    }
    
    void JsonFactory::SaveToPath(JsonObject& json, const std::filesystem::path& path)
    {
		std::ofstream file(path.string(), std::ios::out);

		if (file.is_open() == false)
			throw std::runtime_error("unable to open file");

        FMT::Detail::DynamicBufferManager<char> bufferManager(256);
        Detail::JsonFormatter formatter(bufferManager);
        JsonSerializer<JsonObject>::Dump(json, formatter);
        
		file.write(bufferManager.GetBuffer(), bufferManager.GetLastGeneratedDataSize());
		file.flush();
        file.close();
    }
}
