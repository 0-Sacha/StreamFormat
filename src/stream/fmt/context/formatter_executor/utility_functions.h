#pragma once

#include "basic_formatter_executor.h"

#include "stream/fmt/buffer/buffer_out_manager/dynamic_buffer_out_manager.h"
#include "stream/fmt/buffer/buffer_out_manager/given_buffer_out_manager.h"
#include "stream/fmt/buffer/buffer_out_manager/static_buffer_out_manager.h"

#include "FormatterTextPropertiesExecutor/FormatterANSITextPropertiesExecutor.h"

#include <memory>

namespace stream::fmt
{
    /////---------- Impl with as Format ----------//////
    namespace Detail
    {
        template <typename TChar, typename... Args>
        requires(IsCharType<TChar>::Value)
        [[nodiscard]] std::expected<void, FMTResult> FormatInManager(
            detail::BasicBufferOutManager<TChar>& bufferOutManager,
            bool newline,
            BufferInfoView<TChar> format,
            Args&&... args
        )
        {
            using TCharResolved = std::remove_const_t<TChar>;

            detail::FormatterANSITextPropertiesExecutor<TCharResolved> textPropertiesExecutor;
            detail::FMTBufferOutInfo<TCharResolved> bufferOut = SF_TRY(detail::FMTBufferOutInfo<TCharResolved>::Create(bufferOutManager));
            Context::BasicFormatterExecutor<TCharResolved> executor(bufferOut, textPropertiesExecutor);
            SF_TRY(executor.Run(format, std::forward<Args>(args)...));
            if (newline) SF_TRY(BufferOutManip(bufferOut).Pushback('\n'));
            return executor.Terminate();
        }

        template <typename TChar, typename T>
        requires(IsCharType<TChar>::Value)
        [[nodiscard]] std::expected<void, FMTResult> FormatInManager(detail::BasicBufferOutManager<TChar>& bufferOutManager, bool newline, T&& t)
        {
            using TCharResolved = std::remove_const_t<TChar>;

            detail::FormatterANSITextPropertiesExecutor<TCharResolved> textPropertiesExecutor;
            detail::FMTBufferOutInfo<TCharResolved> bufferOut = SF_TRY(detail::FMTBufferOutInfo<TCharResolved>::Create(bufferOutManager));
            Context::BasicFormatterExecutor<TCharResolved> executor(bufferOut, textPropertiesExecutor);
            SF_TRY(executor.WriteType(std::forward<T>(t)));
            if (newline) SF_TRY(BufferOutManip(bufferOut).Pushback('\n'));
            return executor.Terminate();
        }
    }

    template <typename TChar, typename Format, std::size_t BUFFER_SIZE, typename... Args>
    requires(detail::IsCharType<TChar>::Value && detail::ConvertibleToBufferInfoView<Format>)
    [[nodiscard]] std::expected<void, FMTResult> FormatInChar(TChar (&buffer)[BUFFER_SIZE], Format&& formatInput, Args&&... args)
    {
        detail::GivenBufferOutManager<TChar> bufferOutManager(buffer);
        return detail::FormatInManager(bufferOutManager, false, detail::BufferInfoView{formatInput}, std::forward<Args>(args)...);
    }

    template <typename TChar, typename Format, typename... Args>
    requires(detail::IsCharType<TChar>::Value && detail::ConvertibleToBufferInfoView<Format>)
    [[nodiscard]] std::expected<void, FMTResult> FormatInChar(TChar* const buffer, const std::size_t bufferSize, Format&& formatInput, Args&&... args)
    {
        detail::GivenBufferOutManager<TChar> bufferOutManager(buffer, bufferSize);
        return detail::FormatInManager(bufferOutManager, false, detail::BufferInfoView{formatInput}, std::forward<Args>(args)...);
    }

    template <typename TChar, typename Format, typename... Args>
    requires(detail::IsCharType<TChar>::Value && detail::ConvertibleToBufferInfoView<Format>)
    [[nodiscard]] std::expected<void, FMTResult> CFilePrint(FILE* stream, Format&& formatInput, Args&&... args)
    {
        detail::DynamicBufferOutManager<TChar> bufferOutManager(256);
        SF_TRY(detail::FormatInManager(bufferOutManager, false, detail::BufferInfoView{formatInput}, std::forward<Args>(args)...));

        std::fwrite(bufferOutManager.GetBuffer(), bufferOutManager.GetLastGeneratedDataSize(), 1, stream);
        std::fflush(stream);
        return {};
    }

    template <typename TChar, typename Format, typename... Args>
    requires(detail::IsCharType<TChar>::Value && detail::ConvertibleToBufferInfoView<Format>)
    [[nodiscard]] std::expected<void, FMTResult> CFilePrintLn(FILE* stream, Format&& formatInput, Args&&... args)
    {
        detail::DynamicBufferOutManager<TChar> bufferOutManager(256);
        SF_TRY(detail::FormatInManager(bufferOutManager, true, detail::BufferInfoView{formatInput}, std::forward<Args>(args)...));

        std::fwrite(bufferOutManager.GetBuffer(), bufferOutManager.GetLastGeneratedDataSize(), 1, stream);
        std::fflush(stream);
        return {};
    }

    template <typename TChar, typename Format, typename... Args>
    requires(detail::IsCharType<TChar>::Value && detail::ConvertibleToBufferInfoView<Format>)
    [[nodiscard]] std::expected<void, FMTResult> FilePrint(std::basic_ostream<TChar>& stream, Format&& formatInput, Args&&... args)
    {
        detail::DynamicBufferOutManager<TChar> bufferOutManager(256);
        SF_TRY(detail::FormatInManager(bufferOutManager, false, detail::BufferInfoView{formatInput}, std::forward<Args>(args)...));

        stream.write(bufferOutManager.GetBuffer(), bufferOutManager.GetLastGeneratedDataSize());
        stream.flush();
        return {};
    }

    template <typename TChar, typename Format, typename... Args>
    requires(detail::IsCharType<TChar>::Value && detail::ConvertibleToBufferInfoView<Format>)
    [[nodiscard]] std::expected<void, FMTResult> FilePrintLn(std::basic_ostream<TChar>& stream, Format&& formatInput, Args&&... args)
    {
        detail::DynamicBufferOutManager<TChar> bufferOutManager(256);
        SF_TRY(detail::FormatInManager(bufferOutManager, true, detail::BufferInfoView{formatInput}, std::forward<Args>(args)...));

        stream.write(bufferOutManager.GetBuffer(), bufferOutManager.GetLastGeneratedDataSize());
        stream.flush();
        return {};
    }

    template <typename TChar, typename Format, typename... Args>
    requires(detail::IsCharType<TChar>::Value && detail::ConvertibleToBufferInfoView<Format>)
    [[nodiscard]] std::expected<void, FMTResult> FormatInString(std::basic_string<TChar>& str, Format&& formatInput, Args&&... args)
    {
        detail::DynamicBufferOutManager<TChar> bufferOutManager(256);
        SF_TRY(detail::FormatInManager(bufferOutManager, false, detail::BufferInfoView{formatInput}, std::forward<Args>(args)...));
        str = bufferOutManager.GetLastGeneratedString();
        return {};
    }

    template <typename TChar = char, typename Format, typename... Args>
    requires(detail::IsCharType<TChar>::Value && detail::ConvertibleToBufferInfoView<Format>)
    [[nodiscard]] inline std::expected<std::basic_string<TChar>, FMTResult> FormatString(Format&& formatInput, Args&&... args)
    {
        detail::DynamicBufferOutManager<TChar> bufferOutManager(256);
        SF_TRY(detail::FormatInManager(bufferOutManager, false, detail::BufferInfoView{formatInput}, std::forward<Args>(args)...));
        return bufferOutManager.GetLastGeneratedString();
    }

    /////---------- NO-FORMAT Impl except for string which are formatted to avoid {} ----------//////

    template <typename TChar, size_t BUFFER_SIZE, typename T>
    requires(detail::IsCharType<TChar>::Value)
    [[nodiscard]] std::expected<void, FMTResult> FormatInChar(TChar (&buffer)[BUFFER_SIZE], T&& t)
    {
        detail::GivenBufferOutManager<TChar> bufferOutManager(buffer, BUFFER_SIZE);
        return detail::FormatInManager(bufferOutManager, false, std::forward<T>(t));
    }

    template <typename TChar, typename T>
    requires(detail::IsCharType<TChar>::Value)
    [[nodiscard]] std::expected<void, FMTResult> FormatInChar(TChar* const buffer, const std::size_t bufferSize, T&& t)
    {
        detail::GivenBufferOutManager<TChar> bufferOutManager(buffer, bufferSize);
        return detail::FormatInManager(bufferOutManager, false, std::forward<T>(t));
    }

    template <typename TChar = char, typename T>
    requires(detail::IsCharType<TChar>::Value)
    [[nodiscard]] std::expected<void, FMTResult> CFilePrint(FILE* stream, T&& t)
    {
        detail::DynamicBufferOutManager<TChar> bufferOutManager(32);
        SF_TRY(detail::FormatInManager(bufferOutManager, false, std::forward<T>(t)));

        std::fwrite(bufferOutManager.GetBuffer(), static_cast<std::streamsize>(bufferOutManager.GetLastGeneratedDataSize()), 1, stream);
        std::fflush(stream);
        return {};
    }

    template <typename TChar = char, typename T>
    requires(detail::IsCharType<TChar>::Value)
    [[nodiscard]] std::expected<void, FMTResult> CFilePrintLn(FILE* stream, T&& t)
    {
        detail::DynamicBufferOutManager<TChar> bufferOutManager(32);
        SF_TRY(detail::FormatInManager(bufferOutManager, true, std::forward<T>(t)));

        std::fwrite(bufferOutManager.GetBuffer(), static_cast<std::streamsize>(bufferOutManager.GetLastGeneratedDataSize()), 1, stream);
        std::fflush(stream);
        return {};
    }

    template <typename TChar = char, typename T>
    requires(detail::IsCharType<TChar>::Value)
    [[nodiscard]] std::expected<void, FMTResult> FilePrint(std::basic_ostream<TChar>& stream, T&& t)
    {
        detail::DynamicBufferOutManager<TChar> bufferOutManager(32);
        SF_TRY(detail::FormatInManager(bufferOutManager, false, std::forward<T>(t)));

        stream.write(bufferOutManager.GetBuffer(), static_cast<std::streamsize>(bufferOutManager.GetLastGeneratedDataSize()));
        stream.flush();
        return {};
    }

    template <typename TChar = char, typename T>
    requires(detail::IsCharType<TChar>::Value)
    [[nodiscard]] std::expected<void, FMTResult> FilePrintLn(std::basic_ostream<TChar>& stream, T&& t)
    {
        detail::DynamicBufferOutManager<TChar> bufferOutManager(32);
        SF_TRY(detail::FormatInManager(bufferOutManager, true, std::forward<T>(t)));

        stream.write(bufferOutManager.GetBuffer(), static_cast<std::streamsize>(bufferOutManager.GetLastGeneratedDataSize()));
        stream.flush();
        return {};
    }

    template <typename TChar = char, typename T>
    requires(detail::IsCharType<TChar>::Value)
    [[nodiscard]] std::expected<void, FMTResult> FormatInString(std::basic_string<TChar>& str, T&& t)
    {
        detail::DynamicBufferOutManager<TChar> bufferOutManager(32);
        SF_TRY(detail::FormatInManager(bufferOutManager, false, std::forward<T>(t)));
        str = bufferOutManager.GetLastGeneratedString();
        return {};
    }

    template <typename TChar = char, typename T>
    requires(detail::IsCharType<TChar>::Value)
    [[nodiscard]] inline std::expected<std::basic_string<TChar>, FMTResult> FormatString(T&& t)
    {
        detail::DynamicBufferOutManager<TChar> bufferOutManager(32);
        SF_TRY(detail::FormatInManager(bufferOutManager, false, std::forward<T>(t)));
        return bufferOutManager.GetLastGeneratedString();
    }
}

namespace stream::fmt
{
    template <typename FormatterExecutor>
    struct FormatterType<FMTResult, FormatterExecutor>
    {
        [[nodiscard]] static std::expected<void, FMTResult> format(FMTResult result, FormatterExecutor& executor)
        {
            switch(result)
            {
                case FMTResult::FunctionNotImpl:
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("FunctionNotImpl");
                case FMTResult::Buffer_NonValid:
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("Buffer_NonValid");
                case FMTResult::Buffer_OutOfBoundAccess:
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("Buffer_OutOfBoundAccess");
                case FMTResult::Buffer_UnableToReserveMemory:
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("Buffer_UnableToReserveMemory");
                case FMTResult::Parse_NonValidDigit:
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("Parse_NonValidDigit");
                case FMTResult::Parse_TokenNotExpected:
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("Parse_TokenNotExpected");
                case FMTResult::ArgsInterface_Unavaible:
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("ArgsInterface_Unavaible");
                case FMTResult::ArgsInterface_InvalidTypeID:
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("ArgsInterface_InvalidTypeID");
                case FMTResult::ArgsInterface_InvalidConversion:
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("ArgsInterface_InvalidConversion");
                case FMTResult::ArgsInterface_CantMatchNamedArgs:
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("ArgsInterface_CantMatchNamedArgs");
                case FMTResult::ArgsInterface_IndexOutOfBounds:
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("ArgsInterface_IndexOutOfBounds");
                case FMTResult::Specifers_Full:
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("Specifers_Full");
                case FMTResult::Specifers_Invalid:
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("Specifers_Invalid");
                case FMTResult::Specifers_DoesNotExist:
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("Specifers_DoesNotExist");
                case FMTResult::Context_ParsingFormat:
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("Context_ParsingFormat");
                case FMTResult::Context_ArgumentIndexResolution:
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("Context_ArgumentIndexResolution");
                case FMTResult::Context_ArgumentIndexExpected:
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("Context_ArgumentIndexExpected");
                case FMTResult::Context_CannotApplyType:
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("Context_CannotApplyType");
                case FMTResult::GivenArgs_UnableToDeduceSize:
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("GivenArgs_UnableToDeduceSize");
                case FMTResult::Manager_StaticMemory:
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("Manager_StaticMemory");
                case FMTResult::Manager_AllocationFailed:
                    return detail::BufferWriteManip(executor.buffer_out).FastWriteStringLitteral("Manager_AllocationFailed");
            }
        }
    };
}
