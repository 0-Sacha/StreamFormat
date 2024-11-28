#pragma once

#include "BasicFormatterExecutor.h"

#include "StreamFormat/FMT/Buffer/BufferOutManager/DynamicBufferOutManager.h"
#include "StreamFormat/FMT/Buffer/BufferOutManager/GivenBufferOutManager.h"
#include "StreamFormat/FMT/Buffer/BufferOutManager/StaticBufferOutManager.h"

#include "FormatterTextPropertiesExecutor/FormatterANSITextPropertiesExecutor.h"

#include <memory>

namespace StreamFormat::FMT
{
    /////---------- Impl with as Format ----------//////
    namespace Detail
    {
        template <typename TChar, typename... Args>
        requires(IsCharType<TChar>::Value)
        [[nodiscard]] std::expected<void, FMTResult> FormatInManager(
            Detail::BasicBufferOutManager<TChar>& bufferOutManager,
            bool newline,
            BufferInfoView<TChar> format,
            Args&&... args
        )
        {
            using TCharResolved = std::remove_const_t<TChar>;

            Detail::FormatterANSITextPropertiesExecutor<TCharResolved> textPropertiesExecutor;
            Detail::FMTBufferOutInfo<TCharResolved> bufferOut = SF_TRY(Detail::FMTBufferOutInfo<TCharResolved>::Create(bufferOutManager));
            Context::BasicFormatterExecutor<TCharResolved> executor(bufferOut, textPropertiesExecutor);
            SF_TRY(executor.Run(format, std::forward<Args>(args)...));
            if (newline) SF_TRY(BufferOutManip(bufferOut).Pushback('\n'));
            return executor.Terminate();
        }

        template <typename TChar, typename T>
        requires(IsCharType<TChar>::Value)
        [[nodiscard]] std::expected<void, FMTResult> FormatInManager(Detail::BasicBufferOutManager<TChar>& bufferOutManager, bool newline, T&& t)
        {
            using TCharResolved = std::remove_const_t<TChar>;

            Detail::FormatterANSITextPropertiesExecutor<TCharResolved> textPropertiesExecutor;
            Detail::FMTBufferOutInfo<TCharResolved> bufferOut = SF_TRY(Detail::FMTBufferOutInfo<TCharResolved>::Create(bufferOutManager));
            Context::BasicFormatterExecutor<TCharResolved> executor(bufferOut, textPropertiesExecutor);
            SF_TRY(executor.WriteType(std::forward<T>(t)));
            if (newline) SF_TRY(BufferOutManip(bufferOut).Pushback('\n'));
            return executor.Terminate();
        }
    }

    template <typename TChar, typename Format, std::size_t BUFFER_SIZE, typename... Args>
    requires(Detail::IsCharType<TChar>::Value && Detail::ConvertibleToBufferInfoView<Format>)
    [[nodiscard]] std::expected<void, FMTResult> FormatInChar(TChar (&buffer)[BUFFER_SIZE], Format&& formatInput, Args&&... args)
    {
        Detail::GivenBufferOutManager<TChar> bufferOutManager(buffer);
        return Detail::FormatInManager(bufferOutManager, false, Detail::BufferInfoView{formatInput}, std::forward<Args>(args)...);
    }

    template <typename TChar, typename Format, typename... Args>
    requires(Detail::IsCharType<TChar>::Value && Detail::ConvertibleToBufferInfoView<Format>)
    [[nodiscard]] std::expected<void, FMTResult> FormatInChar(TChar* const buffer, const std::size_t bufferSize, Format&& formatInput, Args&&... args)
    {
        Detail::GivenBufferOutManager<TChar> bufferOutManager(buffer, bufferSize);
        return Detail::FormatInManager(bufferOutManager, false, Detail::BufferInfoView{formatInput}, std::forward<Args>(args)...);
    }

    template <typename TChar, typename Format, typename... Args>
    requires(Detail::IsCharType<TChar>::Value && Detail::ConvertibleToBufferInfoView<Format>)
    [[nodiscard]] std::expected<void, FMTResult> CFilePrint(FILE* stream, Format&& formatInput, Args&&... args)
    {
        Detail::DynamicBufferOutManager<TChar> bufferOutManager(256);
        SF_TRY(Detail::FormatInManager(bufferOutManager, false, Detail::BufferInfoView{formatInput}, std::forward<Args>(args)...));

        std::fwrite(bufferOutManager.GetBuffer(), bufferOutManager.GetLastGeneratedDataSize(), 1, stream);
        std::fflush(stream);
        return {};
    }

    template <typename TChar, typename Format, typename... Args>
    requires(Detail::IsCharType<TChar>::Value && Detail::ConvertibleToBufferInfoView<Format>)
    [[nodiscard]] std::expected<void, FMTResult> CFilePrintLn(FILE* stream, Format&& formatInput, Args&&... args)
    {
        Detail::DynamicBufferOutManager<TChar> bufferOutManager(256);
        SF_TRY(Detail::FormatInManager(bufferOutManager, true, Detail::BufferInfoView{formatInput}, std::forward<Args>(args)...));

        std::fwrite(bufferOutManager.GetBuffer(), bufferOutManager.GetLastGeneratedDataSize(), 1, stream);
        std::fflush(stream);
        return {};
    }

    template <typename TChar, typename Format, typename... Args>
    requires(Detail::IsCharType<TChar>::Value && Detail::ConvertibleToBufferInfoView<Format>)
    [[nodiscard]] std::expected<void, FMTResult> FilePrint(std::basic_ostream<TChar>& stream, Format&& formatInput, Args&&... args)
    {
        Detail::DynamicBufferOutManager<TChar> bufferOutManager(256);
        SF_TRY(Detail::FormatInManager(bufferOutManager, false, Detail::BufferInfoView{formatInput}, std::forward<Args>(args)...));

        stream.write(bufferOutManager.GetBuffer(), bufferOutManager.GetLastGeneratedDataSize());
        stream.flush();
        return {};
    }

    template <typename TChar, typename Format, typename... Args>
    requires(Detail::IsCharType<TChar>::Value && Detail::ConvertibleToBufferInfoView<Format>)
    [[nodiscard]] std::expected<void, FMTResult> FilePrintLn(std::basic_ostream<TChar>& stream, Format&& formatInput, Args&&... args)
    {
        Detail::DynamicBufferOutManager<TChar> bufferOutManager(256);
        SF_TRY(Detail::FormatInManager(bufferOutManager, true, Detail::BufferInfoView{formatInput}, std::forward<Args>(args)...));

        stream.write(bufferOutManager.GetBuffer(), bufferOutManager.GetLastGeneratedDataSize());
        stream.flush();
        return {};
    }

    template <typename TChar, typename Format, typename... Args>
    requires(Detail::IsCharType<TChar>::Value && Detail::ConvertibleToBufferInfoView<Format>)
    [[nodiscard]] std::expected<void, FMTResult> FormatInString(std::basic_string<TChar>& str, Format&& formatInput, Args&&... args)
    {
        Detail::DynamicBufferOutManager<TChar> bufferOutManager(256);
        SF_TRY(Detail::FormatInManager(bufferOutManager, false, Detail::BufferInfoView{formatInput}, std::forward<Args>(args)...));
        str = bufferOutManager.GetLastGeneratedString();
        return {};
    }

    template <typename TChar = char, typename Format, typename... Args>
    requires(Detail::IsCharType<TChar>::Value && Detail::ConvertibleToBufferInfoView<Format>)
    [[nodiscard]] inline std::expected<std::basic_string<TChar>, FMTResult> FormatString(Format&& formatInput, Args&&... args)
    {
        Detail::DynamicBufferOutManager<TChar> bufferOutManager(256);
        SF_TRY(Detail::FormatInManager(bufferOutManager, false, Detail::BufferInfoView{formatInput}, std::forward<Args>(args)...));
        return bufferOutManager.GetLastGeneratedString();
    }

    /////---------- NO-FORMAT Impl except for string which are formatted to avoid {} ----------//////

    template <typename TChar, size_t BUFFER_SIZE, typename T>
    requires(Detail::IsCharType<TChar>::Value)
    [[nodiscard]] std::expected<void, FMTResult> FormatInChar(TChar (&buffer)[BUFFER_SIZE], T&& t)
    {
        Detail::GivenBufferOutManager<TChar> bufferOutManager(buffer, BUFFER_SIZE);
        return Detail::FormatInManager(bufferOutManager, false, std::forward<T>(t));
    }

    template <typename TChar, typename T>
    requires(Detail::IsCharType<TChar>::Value)
    [[nodiscard]] std::expected<void, FMTResult> FormatInChar(TChar* const buffer, const std::size_t bufferSize, T&& t)
    {
        Detail::GivenBufferOutManager<TChar> bufferOutManager(buffer, bufferSize);
        return Detail::FormatInManager(bufferOutManager, false, std::forward<T>(t));
    }

    template <typename TChar = char, typename T>
    requires(Detail::IsCharType<TChar>::Value)
    [[nodiscard]] std::expected<void, FMTResult> CFilePrint(FILE* stream, T&& t)
    {
        Detail::DynamicBufferOutManager<TChar> bufferOutManager(32);
        SF_TRY(Detail::FormatInManager(bufferOutManager, false, std::forward<T>(t)));

        std::fwrite(bufferOutManager.GetBuffer(), static_cast<std::streamsize>(bufferOutManager.GetLastGeneratedDataSize()), 1, stream);
        std::fflush(stream);
        return {};
    }

    template <typename TChar = char, typename T>
    requires(Detail::IsCharType<TChar>::Value)
    [[nodiscard]] std::expected<void, FMTResult> CFilePrintLn(FILE* stream, T&& t)
    {
        Detail::DynamicBufferOutManager<TChar> bufferOutManager(32);
        SF_TRY(Detail::FormatInManager(bufferOutManager, true, std::forward<T>(t)));

        std::fwrite(bufferOutManager.GetBuffer(), static_cast<std::streamsize>(bufferOutManager.GetLastGeneratedDataSize()), 1, stream);
        std::fflush(stream);
        return {};
    }

    template <typename TChar = char, typename T>
    requires(Detail::IsCharType<TChar>::Value)
    [[nodiscard]] std::expected<void, FMTResult> FilePrint(std::basic_ostream<TChar>& stream, T&& t)
    {
        Detail::DynamicBufferOutManager<TChar> bufferOutManager(32);
        SF_TRY(Detail::FormatInManager(bufferOutManager, false, std::forward<T>(t)));

        stream.write(bufferOutManager.GetBuffer(), static_cast<std::streamsize>(bufferOutManager.GetLastGeneratedDataSize()));
        stream.flush();
        return {};
    }

    template <typename TChar = char, typename T>
    requires(Detail::IsCharType<TChar>::Value)
    [[nodiscard]] std::expected<void, FMTResult> FilePrintLn(std::basic_ostream<TChar>& stream, T&& t)
    {
        Detail::DynamicBufferOutManager<TChar> bufferOutManager(32);
        SF_TRY(Detail::FormatInManager(bufferOutManager, true, std::forward<T>(t)));

        stream.write(bufferOutManager.GetBuffer(), static_cast<std::streamsize>(bufferOutManager.GetLastGeneratedDataSize()));
        stream.flush();
        return {};
    }

    template <typename TChar = char, typename T>
    requires(Detail::IsCharType<TChar>::Value)
    [[nodiscard]] std::expected<void, FMTResult> FormatInString(std::basic_string<TChar>& str, T&& t)
    {
        Detail::DynamicBufferOutManager<TChar> bufferOutManager(32);
        SF_TRY(Detail::FormatInManager(bufferOutManager, false, std::forward<T>(t)));
        str = bufferOutManager.GetLastGeneratedString();
        return {};
    }

    template <typename TChar = char, typename T>
    requires(Detail::IsCharType<TChar>::Value)
    [[nodiscard]] inline std::expected<std::basic_string<TChar>, FMTResult> FormatString(T&& t)
    {
        Detail::DynamicBufferOutManager<TChar> bufferOutManager(32);
        SF_TRY(Detail::FormatInManager(bufferOutManager, false, std::forward<T>(t)));
        return bufferOutManager.GetLastGeneratedString();
    }
}
