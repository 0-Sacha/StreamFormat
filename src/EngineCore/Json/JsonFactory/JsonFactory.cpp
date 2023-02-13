
#include "JsonFactory.h"

#include "EngineCore//FMT/Detail/Buffer/BasicBufferOut/BufferManager/DynamicBufferManager.h"

#include <fstream>
#include <utility>

namespace EngineCore::JSON
{
    JsonContext JsonFactory::FromPath(const std::filesystem::path& path)
    {
        std::ifstream file(path.string(), std::ios::in);
        
        if (file.is_open() == false)
            throw std::runtime_error("unable to open file");
        
        JsonContext json;

        file.seekg(0, std::ios::end);
        std::size_t size = file.tellg();
        file.seekg(0, std::ios::beg);
        json.GetBuffer().Reserve(size);
        file.read(json.GetBuffer().GetBuffer(), size);
        file.close();

        json.ReloadFromBuffer();
        return json;                  
    }
    
    void JsonFactory::SaveToPath(JsonContext& json, const std::filesystem::path& path)
    {
		std::ofstream file(path.string(), std::ios::out);

		if (file.is_open() == false)
			throw std::runtime_error("unable to open file");

        FMT::Detail::DynamicBufferManager<char> bufferManager(256);
        Detail::JsonFormatter formatter(bufferManager);
        formatter.DumpJsonObject(json.GetObjects());
        
		file.write(bufferManager.GetBuffer(), bufferManager.GetLastGeneratedDataSize());
		file.flush();
        file.close();
    }
}
