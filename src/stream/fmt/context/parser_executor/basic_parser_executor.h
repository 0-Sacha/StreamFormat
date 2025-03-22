#pragma once

#include "stream/fmt/buffer/buffer_info.h"
#include "stream/fmt/buffer/buffer_manip.h"
#include "stream/fmt/buffer/buffer_test_manip.h"

#include "stream/fmt/context/basic_context/basic_context.h"

#include "ParserType.h"

#include "ParserArgs.h"

#include "ParserTextPropertiesExecutor/ParserTextPropertiesExecutor.h"

namespace stream::fmt::context
{
    template <typename CharType>
    class BasicParserExecutor : public ContextExecutor<CharType>
    {
    public:
        using TChar = CharType;
    private:
        using M_Type = BasicParserExecutor<TChar>;

    public:
        BasicParserExecutor(detail::BufferInfoView<TChar>& bufferIn, detail::ITextPropertiesExecutor& textPropertiesExecutor);
        ~BasicParserExecutor() override = default;

        [[nodiscard]] std::expected<void, FMTResult> Terminate();

    public:
        detail::BufferInfoView<TChar>& BufferIn;

        using ContextExecutor<CharType>::Data;
        using ContextExecutor<CharType>::TextManager;

    protected:
        [[nodiscard]] std::expected<void, FMTResult> ExecRawString(std::basic_string_view<TChar> sv) override
        {
            SF_TRY(detail::BufferTestManip(BufferIn).is_same_forward(sv.data(), sv.size()));
            return {};
        }
        [[nodiscard]] std::expected<void, FMTResult> ExecSettings() override { return {}; };

    public:
        template <typename... Args>
        [[nodiscard]] std::expected<void, FMTResult> Run_(detail::BufferInfoView<TChar> format, Args&&... args);
        template <typename Format, typename... Args>
        [[nodiscard]] std::expected<void, FMTResult> Run(Format&& format, Args&&... args);

    public:
        template <typename Type, typename... Rest>
        [[nodiscard]] inline std::expected<void, FMTResult> ReadType(Type& type, Rest&... rest)
        {
            auto&& parseErr = ParserType<typename detail::FormatTypeForwardAs<detail::GetBaseType<Type>>::Type, M_Type>::parse(type, *this);
            SF_TRY(parseErr);
            if constexpr (sizeof...(rest) > 0)
                SF_TRY(ReadType(std::forward<Rest>(rest)...));
            return {};
        }
    };
}

namespace stream::fmt::context
{
    template <typename TChar>
    BasicParserExecutor<TChar>::BasicParserExecutor(detail::BufferInfoView<TChar>& bufferIn, detail::ITextPropertiesExecutor& textPropertiesExecutor)
        : ContextExecutor<TChar>(textPropertiesExecutor)
        , BufferIn{bufferIn}
    {
        textPropertiesExecutor.link_to_executor(this);
    }

    template <typename TChar>
    [[nodiscard]] std::expected<void, FMTResult> BasicParserExecutor<TChar>::Terminate()
    {
        return {};
    }

    template <typename TChar>
    template <typename... Args>
    [[nodiscard]] std::expected<void, FMTResult> BasicParserExecutor<TChar>::Run_(detail::BufferInfoView<TChar> format, Args&&... args)
    {
        auto argsInterface = detail::ParserArgsInterface<TChar, BasicParserExecutor<TChar>, Args...>(*this, std::forward<Args>(args)...);

        detail::TextProperties::Properties saveTextProperties = TextManager.Save();
        Context::BasicContext<TChar> context(*this, format, argsInterface);
        SF_TRY(context.Run());
        return TextManager.Reload(saveTextProperties);
    }

    template <typename TChar>
    template <typename Format, typename... Args>
    [[nodiscard]] std::expected<void, FMTResult> BasicParserExecutor<TChar>::Run(Format&& formatInput, Args&&... args)
    {
        return Run_(detail::BufferInfoView{formatInput}, std::forward<Args>(args)...);
    }
}

#include "ParseBasics-impl.h"
#include "ParseTextProperties-impl.h"
