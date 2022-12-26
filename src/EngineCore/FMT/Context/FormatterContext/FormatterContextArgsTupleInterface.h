#pragma once

#include "FormatterContextArgsTuple.h"

namespace EngineCore::FMT::Detail {

    template<typename Context>
    class BasicFormatterContextArgsTupleInterface
    {
        public:
            BasicFormatterContextArgsTupleInterface()
                : m_Context(nullptr)
            {}

            void SetContext(Context* context) { m_Context = context; }
            
        public:
            virtual void RunTypeAtIndex(const Detail::FormatIndex& idx) = 0;
            virtual Detail::FormatIndex GetIndexOfCurrentNameArg() = 0;
            virtual void* GetTypeAtIndex(const Detail::FormatIndex& idx) = 0;
            virtual int RuntimeTypeUID(const Detail::FormatIndex& idx) = 0;

        protected:
            Context* m_Context;

        public:
         template <typename CastTo>
            CastTo* Cast(void* type, int uid)

            template <typename ConvertTo>
            void Convert(void* from, void* to, int uid)

            template <typename CastTo>
            CastTo* GetTypeAtIndexCast(const Detail::FormatIndex& idx)
            {
                return reinterpret_cast<CastTo*>(Handler.Cast(GetTypeAtIndex(idx), RuntimeTypeUID(idx)));
            }

            template <typename CastTo>
            CastTo& GetTypeAtIndexCastThrow(const Detail::FormatIndex& idx)
            {
                CastTo* get = GetTypeAtIndexCast(idx);
                if (get == nullptr)
                {
                    throw FormatGivenTypeError{};
                    return nullptr;
                }
                return *get
            }

            template <typename ConvertTo>
            ConvertTo GetTypeAtIndexConvertThrow(const Detail::FormatIndex& idx)
            {
                void* get = GetTypeAtIndex(idx);
                if (get == nullptr)
                {
                    throw FormatGivenTypeError{};
                    return ConvertTo{};
                }
                return Handler.Convert(get, RuntimeTypeUID(idx))
            }
    };

    template<typename Context, typename... Args>
    class FormatterContextArgsTupleInterface : public BasicFormatterContextArgsTupleInterface<Context>
    {
        public:
            using Base 	            = BasicFormatterContextArgsTupleInterface<Context>;
            using ContextArgsType 	= Detail::FormatterContextArgsTuple<Args...>;
            
        public:
            FormatterContextArgsTupleInterface(Args&&... args)
                : Base()
                , m_contextArgs(std::forward<Args>(args)...)
            {}
            
        public:
            virtual void RunTypeAtIndex(const Detail::FormatIndex& idx)
                    { return m_contextArgs.RunTypeAtIndex(m_Context, idx); }

            virtual Detail::FormatIndex GetIndexOfCurrentNameArg()
                    { return m_contextArgs.GetIndexOfCurrentNameArg(m_Context, 0); }

            virtual void* GetTypeAtIndex(const Detail::FormatIndex& idx)
                    { return m_contextArgs.GetTypeAtIndex(idx); }

            virtual int RuntimeTypeUID(const Detail::FormatIndex& idx)
                    { return m_contextArgs.RuntimeTypeUID(idx); }

        protected:
            ContextArgsType m_contextArgs;
    };
}
