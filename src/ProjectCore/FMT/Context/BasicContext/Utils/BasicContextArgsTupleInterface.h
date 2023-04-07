
#pragma once

#include "ProjectCore/FMT/Detail/Detail.h"
#include "FMTContextTemplate.h"

#include <any>
#include <functional>

namespace ProjectCore::FMT::Detail {

    template<typename CharFormat>
    class BasicArgsTupleInterface
    {
        public:
            BasicArgsTupleInterface() {}
            virtual ~BasicArgsTupleInterface() = default;

        public:
            virtual size_t Size() = 0;
            virtual void SetContext(std::any context) = 0;

        public:
            virtual void RunTypeAtIndex(Detail::FormatIndex idx) = 0;
            virtual Detail::FormatIndex GetIndexOfCurrentNameArg() = 0;

            virtual std::any GetTypeAtIndexImpl(Detail::FormatIndex idx) = 0;

            virtual Detail::FormatIndex GetFormatIndexAt(Detail::FormatIndex idx) = 0;
            virtual typename std::basic_string_view<CharFormat> GetStringAt(Detail::FormatIndex idx) = 0;
            virtual int64_t GetIntAt(Detail::FormatIndex idx) = 0;

            virtual void RunFuncAtImpl(Detail::FormatIndex idx, std::function<void(std::any)> func) = 0;

        public:
            template <typename T>
            const T* GetTypeAtIndex(Detail::FormatIndex idx)
            {
                try
                {
                    return std::any_cast<const T*>(GetTypeAtIndexImpl(idx));
                }
                catch(...)
                {
                    return nullptr;
                }
            }

            template <typename T>
            const T& GetTypeAtIndexThrow(Detail::FormatIndex idx)
            {
                const T* value = GetTypeAtIndex<T>(idx);
                if (value != nullptr)
                    return *value;
                throw FMTGivenTypeError{};
            }


            template <typename T>
            void RunFuncFromTypeAtIndex(Detail::FormatIndex idx, std::function<void(const T&)> func)
            {
                const T* value = GetTypeAtIndex<T>(idx);
                if (value != nullptr)
                    func(*value);
            }
    };

    template<typename Context>
    class BasicContextArgsTupleInterface : public BasicArgsTupleInterface<typename Context::CharFormatType>
    {
        public:
            BasicContextArgsTupleInterface()
                : m_Context(nullptr)
            {}
            ~BasicContextArgsTupleInterface() override = default;

        public:
            void SetContext(std::any context) override { m_Context = std::any_cast<Context*>(context); }
            
        protected:
            Context* m_Context;
    };

    template<typename Context>
    class EmptyContextArgsTupleInterface : public BasicContextArgsTupleInterface<Context>
    {
        public:
            EmptyContextArgsTupleInterface() {}
            ~EmptyContextArgsTupleInterface() override = default;

        public:
            size_t Size() override { return 0; }

            void RunTypeAtIndex(Detail::FormatIndex) override { }

            Detail::FormatIndex GetIndexOfCurrentNameArg() override { return Detail::FormatIndex{}; }

            std::any GetTypeAtIndexImpl(Detail::FormatIndex) override { return {}; }

            void RunFuncAtImpl(Detail::FormatIndex, std::function<void(std::any)>) override { }

            Detail::FormatIndex GetFormatIndexAt(Detail::FormatIndex) override { return Detail::FormatIndex{}; }
            typename Context::StringViewFormat GetStringAt(Detail::FormatIndex) override { return ""; }
            std::int64_t GetIntAt(Detail::FormatIndex) override { return 0; }
    };
}
