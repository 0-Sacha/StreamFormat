#pragma once

#include "JsonParser.h"
#include "JsonFormatter.h"

#include "EngineCore/FMT/Detail/Buffer/BasicBufferIn/Utils/BufferInUtils.h"
#include "EngineCore/FMT/Detail/Buffer/BasicBufferOut/Utils/BufferOutUtils.h"

#include <string>

namespace EngineCore::JSON::Detail
{
    template <typename T> class ForwardAsJsonString {};
    template <typename T> class ForwardAsJsonNumber {};
    template <typename T> class ForwardAsJsonBoolean {};
    template <typename T> class ForwardAsJsonStruct {};
    template <typename T> class ForwardAsJsonArray {};
    template <typename T> class ForwardAsJsonNull {};
}

namespace EngineCore::JSON
{
    template<typename T>
	struct JsonSerializer
    {
		static inline void Load(T& t, Detail::JsonParser& parser)
        {
#ifndef ENGINECORE_COMPILER_VS
            throw JsonTypeSerializerNotImpl{};
#else
            __debugbreak();
#endif
        }

		static inline void Dump(const T& t, Detail::JsonFormatter& formatter)
        {
            formatter.BufferOut().WriteCharArray("Unkown JsonFormatter for type : ");
            formatter.BufferOut().WriteCharPtr(typeid(T).name());

#ifndef ENGINECORE_COMPILER_VS
            throw JsonTypeSerializerNotImpl{};
#endif
        }
	};

    template <typename T>
	struct JsonSerializer<Detail::ForwardAsJsonString<T>>
    {
        static inline void LoadSTDString(std::string& t, Detail::JsonParser& parser)
        {
            std::string string = EngineCore::FMT::BufferInUtils<char>::ParseEscapedQuotedString(parser.BufferIn());
            t = std::move(string);
        }

		static inline void DumpSTDString(const std::string& t, Detail::JsonFormatter& formatter)
        {
            EngineCore::FMT::BufferOutUtils<char>::WriteEscapedQuotedString(formatter.BufferOut(), t);
        }
    };

    template <typename T>
	struct JsonSerializer<Detail::ForwardAsJsonNumber<T>>
    {
        template <typename FloatType>
        static inline void LoadFloat(FloatType& t, Detail::JsonParser& parser)
        {
            parser.BufferIn().FastReadFloat<FloatType>(t);
        }

        template <typename IntType>
        static inline void LoadInt(IntType& t, Detail::JsonParser& parser)
        {
            const char* begin = parser.BufferIn().GetBufferCurrentPos();
            float tmp = 0;
            parser.BufferIn().FastReadFloat<float>(tmp);
            const char* end = parser.BufferIn().GetBufferCurrentPos();
            
            parser.BufferIn().SetBufferCurrentPos(begin);
            parser.BufferIn().FastReadInt(t);

            parser.BufferIn().SetBufferCurrentPos(end);
        }

        template <typename UIntType>
        static inline void LoadUInt(UIntType& t, Detail::JsonParser& parser)
        {
            const char* begin = parser.BufferIn().GetBufferCurrentPos();
            float tmp = 0;
            parser.BufferIn().FastReadFloat<float>(tmp);
            const char* end = parser.BufferIn().GetBufferCurrentPos();
            
            parser.BufferIn().SetBufferCurrentPos(begin);
            parser.BufferIn().FastReadUInt(t);

            parser.BufferIn().SetBufferCurrentPos(end);
        }

        template <typename FloatType>
		static inline void DumpFloat(const FloatType& t, Detail::JsonFormatter& formatter)
        {
            formatter.BufferOut().FastWriteFloat(t);
        }

        template <typename IntType>
		static inline void DumpInt(const IntType& t, Detail::JsonFormatter& formatter)
        {
            formatter.BufferOut().FastWriteInt(t);
        }

        template <typename UIntType>
		static inline void DumpUInt(const UIntType& t, Detail::JsonFormatter& formatter)
        {
            formatter.BufferOut().FastWriteUInt(t);
        }
    };

    template <typename T>
	struct JsonSerializer<Detail::ForwardAsJsonBoolean<T>>
    {
        static inline void LoadBool(bool& t, Detail::JsonParser& parser)
        {
            if (parser.BufferIn().IsSameSeqForward('t', 'r', 'u', 'e'))
                t = true;
            else if (parser.BufferIn().IsSameSeqForward('f', 'a', 'l', 's', 'e'))
                t  = false;
        }

		static inline void DumpBool(const bool& t, Detail::JsonFormatter& formatter)
        {
            if (t)
                formatter.BufferOut().PushBackSeq('t', 'r', 'u', 'e');
            else
                formatter.BufferOut().PushBackSeq('f', 'a', 'l', 's', 'e');
        }
    };

    template <typename T>
	struct JsonSerializer<Detail::ForwardAsJsonStruct<T>>
    {
        static inline void LoadSubObjects(T& t, Detail::JsonParser& parser)
        {
           parser.BufferIn().Skip('{');

            while (parser.BufferIn().IsEnd() == false)
            {
                parser.BufferIn().GoTo('"', '}');
                if (parser.BufferIn().IsEqualTo('}')) break;

                std::string name = EngineCore::FMT::BufferInUtils<char>::ParseEscapedQuotedString(parser.BufferIn());

                parser.BufferIn().IgnoreAllBlanks();
                parser.BufferIn().Skip(':');
                parser.BufferIn().IgnoreAllBlanks();

                typename JsonSerializer<T>::SubObjectType subObject;
                JsonSerializer<typename JsonSerializer<T>::SubObjectType>::Load(subObject, parser);
                JsonSerializer<T>::AddSubObject(t, std::move(name), std::move(subObject));

                parser.BufferIn().GoTo(',', '}');
                parser.BufferIn().Ignore(',');
            }

            parser.BufferIn().Skip('}');
        }

		static inline void DumpBegin(Detail::JsonFormatter& formatter)
        {
            formatter.BufferOut().PushBack('{');
        }

        static inline void DumpEnd(Detail::JsonFormatter& formatter)
        {
            formatter.NewLine();
            formatter.BufferOut().PushBack('}');
        }

        static inline void DumpObject(const std::string& name, const typename JsonSerializer<T>::SubObjectType& subObject, const std::size_t idx, Detail::JsonFormatter& formatter)
        {
            if (idx != 0) formatter.BufferOut().PushBack(',');

            formatter.BeginNewObject();
            formatter.NewLine();
            EngineCore::FMT::BufferOutUtils<char>::WriteEscapedQuotedString(formatter.BufferOut(), name);
            formatter.BufferOut().PushBack(':');
            formatter.BufferOut().PushBack(' ');
            JsonSerializer<typename JsonSerializer<T>::SubObjectType>::Dump(subObject, formatter);
            formatter.EndNewObject();
        }
    };

     template <typename T>
	struct JsonSerializer<Detail::ForwardAsJsonArray<T>>
    {
        static inline void LoadSubObjects(T& t, Detail::JsonParser& parser)
        {
           parser.BufferIn().Skip('[');

            while (parser.BufferIn().IsEnd() == false)
            {
                parser.BufferIn().IgnoreAllBlanks();

                if (parser.BufferIn().IsEqualTo(']')) break;

				typename JsonSerializer<T>::SubObjectType subObject;
				JsonSerializer<typename JsonSerializer<T>::SubObjectType>::Load(subObject, parser);
                JsonSerializer<T>::AddSubObject(t, std::move(subObject));

                parser.BufferIn().GoTo(',', ']');
                parser.BufferIn().Ignore(',');
            }

            parser.BufferIn().Skip(']');
        }

		static inline void DumpBegin(Detail::JsonFormatter& formatter)
        {
            formatter.BufferOut().PushBack('[');
        }

        static inline void DumpEnd(Detail::JsonFormatter& formatter)
        {
            formatter.NewLine();
		    formatter.BufferOut().PushBack(']');
        }

        static inline void DumpObject(const typename JsonSerializer<T>::SubObjectType& subObject, const std::size_t idx, Detail::JsonFormatter& formatter)
        {
            if (idx != 0) formatter.BufferOut().PushBack(',');

            formatter.BeginNewObject();
            formatter.NewLine();
            JsonSerializer<typename JsonSerializer<T>::SubObjectType>::Dump(subObject, formatter);
            formatter.EndNewObject();
        }
    };

    template <typename T>
	struct JsonSerializer<Detail::ForwardAsJsonNull<T>>
    {
        static inline void LoadNull(Detail::JsonParser& parser)
        {
            parser.BufferIn().IsSameSeqForwardThrow('n', 'u', 'l', 'l');
        }

		static inline void DumpNull(Detail::JsonFormatter& formatter)
        {
            formatter.BufferOut().PushBackSeq('n', 'u', 'l', 'l');
        }
    };
}
