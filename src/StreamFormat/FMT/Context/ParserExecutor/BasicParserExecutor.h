#pragma once

#include "StreamFormat/FMT/Buffer/BufferInfo.h"
#include "StreamFormat/FMT/Buffer/BufferManip.h"
#include "StreamFormat/FMT/Buffer/BufferTestManip.h"

#include "StreamFormat/FMT/Context/BasicContext/BasicContext.h"

#include "ParserType.h"

#include "ParserArgs.h"

#include "ParserTextPropertiesExecutor/ParserTextPropertiesExecutor.h"

namespace StreamFormat::FMT::Context
{
    template <typename CharType>
    class BasicParserExecutor : public ContextExecutor<CharType>
    {
    public:
        using TChar = CharType;
    private:
        using M_Type = BasicParserExecutor<TChar>;

    public:
        BasicParserExecutor(Detail::BufferInfoView<TChar>& bufferIn, Detail::ITextPropertiesExecutor& textPropertiesExecutor);
        ~BasicParserExecutor() override = default;

        [[nodiscard]] std::expected<void, FMTResult> Terminate();

    public:
        Detail::BufferInfoView<TChar>& BufferIn;

        using ContextExecutor<CharType>::Data;
        using ContextExecutor<CharType>::TextManager;

    protected:
        [[nodiscard]] std::expected<void, FMTResult> ExecRawString(std::basic_string_view<TChar> sv) override
        {
            SF_TRY(Detail::BufferTestManip(BufferIn).IsSameForward(sv.data(), sv.size()));
            return {};
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecSettings() override {};

    public:
        template <typename... Args>
        [[nodiscard]] std::expected<void, FMTResult> Run_(Detail::BufferInfoView<TChar> format, Args&&... args);
        template <typename Format, typename... Args>
        [[nodiscard]] std::expected<void, FMTResult> Run(Format&& format, Args&&... args);

    public:
        template <typename Type, typename... Rest>
        [[nodiscard]] inline std::expected<void, FMTResult> ReadType(Type& type, Rest&... rest)
        {
            ParserType<typename Detail::FormatTypeForwardAs<Detail::GetBaseType<Type>>::Type, M_Type>::Parse(type, *this);
            if constexpr (sizeof...(rest) > 0)
                ReadType(std::forward<Rest>(rest)...);
        }
    };
}

namespace StreamFormat::FMT::Context
{
    template <typename TChar>
    BasicParserExecutor<TChar>::BasicParserExecutor(Detail::BufferInfoView<TChar>& bufferIn, Detail::ITextPropertiesExecutor& textPropertiesExecutor)
        : ContextExecutor<TChar>(textPropertiesExecutor)
        , BufferIn{bufferIn}
    {
        textPropertiesExecutor.LinkToExecutor(this);
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicParserExecutor<TChar>::Terminate()
    {
    }

    template <typename TChar>
    template <typename... Args>
    [[nodiscard]] std::expected<void, FMTResult> BasicParserExecutor<TChar>::Run_(Detail::BufferInfoView<TChar> format, Args&&... args)
    {
        auto argsInterface = Detail::ParserArgsInterface<TChar, BasicParserExecutor<TChar>, Args...>(*this, std::forward<Args>(args)...);

        Detail::TextProperties::Properties saveTextProperties = TextManager.Save();
        Context::BasicContext<TChar> context(*this, format, argsInterface);
        context.Run();
        TextManager.Reload(saveTextProperties);
    }

    template <typename TChar>
    template <typename Format, typename... Args>
    [[nodiscard]] std::expected<void, FMTResult> BasicParserExecutor<TChar>::Run(Format&& formatInput, Args&&... args)
    {
        Run_(Detail::BufferInfoView{formatInput}, std::forward<Args>(args)...);
    }
}

#include "ParseBasics-impl.h"
#include "ParseTextProperties-impl.h"
