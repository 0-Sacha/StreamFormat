
#include "JsonFactory.h"

#include <fstream>
#include <utility>

namespace EngineCore::JSON
{
    JsonContext JsonFactory::FromPath(const std::filesystem::path& path)
    {
        JsonContext json;

        std::ifstream file(path.string(), std::ios::in);
        
        if (file.is_open() == false)
            throw std::runtime_error("unable to open file");


        file.seekg(0, std::ios::end);
        std::size_t size = file.tellg();
        file.seekg(0, std::ios::beg);
        json.GetBuffer().Reserve(size);
        file.read(json.GetBuffer().GetBuffer(), size);
        file.close();

        json.ReloadParser();
        json.LoadObjects();
        return json;                  
    }
    
    void JsonFactory::SaveToPath(JsonContext& json, const std::filesystem::path& path)
    {
		std::ofstream file(path.string(), std::ios::out);
        file.close();                   
    }
}
