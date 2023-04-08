#pragma once

#include "ProjectCore/FMT/Detail/Detail.h"

namespace ProjectCore::FMT::Detail
{
    template <typename BufferContext>
    struct NoStrideFunction {
        inline explicit NoStrideFunction(BufferContext& buffer)
            : Buffer(buffer)
            , SizeBuffer(Buffer.GetBufferCurrentSize()) {}

        ~NoStrideFunction() {
            Buffer.AddNoStride(Buffer.GetBufferCurrentSize() - SizeBuffer);
        }

        BufferContext&  Buffer;
        std::size_t 	SizeBuffer;
    };

    template <typename Char>
    struct IndentInfo
    {
        inline IndentInfo()
            : Restore(true)
            , AddIndent(0)
        {}

        inline explicit IndentInfo(const std::basic_string_view<Char>& txt)
            : Restore(false)
            , AddIndent(txt.size())
        {
            for (std::size_t k = 0; k < txt.size(); ++k)
            {
                if (txt[k] == '\n')
                {
                    Restore = true;
                    AddIndent = txt.size() - k - 1;
                }
            }
        }

        bool 		Restore;
        std::size_t AddIndent;
    };

    template <typename FormatterContext>
    class RestoreIndentFunction
    {
        inline explicit RestoreIndentFunction(FormatterContext& context)
            : m_Context(context)
            , m_OldIndent(context.GetIndent())
            , m_IndentInfo()
            , m_AddIndentEnd(false)
        {}

        template <typename Char>
        inline RestoreIndentFunction(FormatterContext& context, const std::basic_string_view<Char>& txt, bool addIndentEnd = true)
            : m_Context(context)
            , m_OldIndent(context.BufferOut().GetIndent())
            , m_IndentInfo(txt)
            , m_AddIndentEnd(addIndentEnd)
        {}

        ~RestoreIndentFunction() {
            if (m_IndentInfo.Restore)
                m_Context.BufferOut().SetIndent(m_OldIndent);
            if (m_AddIndentEnd)
                m_Context.BufferOut().AddIndent(m_IndentInfo.AddIndent);
        }

    private:
        FormatterContext&                                       m_Context;
        std::size_t                                             m_OldIndent;
        IndentInfo<typename FormatterContext::CharFormatType> 	m_IndentInfo;
        bool                                                    m_AddIndentEnd;
    };

    template <typename FormatterContext>
    struct IndentFunctionData
    {
        inline explicit IndentFunctionData(FormatterContext& context)
            : Context(context)
            , OldNoStride(context.BufferOut().GetNoStride())
            , OldBufferSize(context.BufferOut().GetBufferCurrentSize())
        {}

        inline std::size_t GetIndent()
        {
            return (Context.BufferOut().GetBufferCurrentSize() - OldBufferSize) - (Context.BufferOut().GetNoStride() - OldNoStride);
        }

        FormatterContext&   Context;
        std::size_t 		OldNoStride;
        std::size_t         OldBufferSize;
    };
    
    template <typename FormatterContext>
    class IndentFunction
    {
        explicit inline IndentFunction(FormatterContext& context)
            : m_IndentFunctionData(context)
        {}

        ~IndentFunction() {
            m_IndentFunctionData.Context.AddIndent(m_IndentFunctionData.GetIndent());
        }

    private:
        IndentFunctionData<FormatterContext>     m_IndentFunctionData;
    };
}
