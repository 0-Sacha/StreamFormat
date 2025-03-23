#pragma once

#include "json_objects.hxx"
#include "stream/fmt/buf/streamio.hxx"
#include "stream/fmt/buf/manip_io.hxx"

namespace stream::json::detail {
    class JsonFormatter {
    public:
        struct FormatSettings {
            std::size_t  indent_size        = 4;
            bool         indent_with_spaces = true;
            bool         one_line           = false;
            bool         ordered_struct     = false;
            std::int32_t float_precision    = 7;
        };

    public:
        JsonFormatter(stream::fmt::buf::StreamIO<char>& ostream_) : ostream(ostream_), settings(), indent_(0) {}
        JsonFormatter(stream::fmt::buf::StreamIO<char>& ostream_, FormatSettings settings_) : ostream(ostream_), settings(settings_), indent_(0) {}

    public:
        template <typename T>
        void format(const T& t);

        struct StructIntermediate;
        struct ArrayIntermediate;
        StructIntermediate get_struct_intermediate();
        ArrayIntermediate  get_array_intermediate();

    public:
        void indent() {
            if (settings.one_line) return;

            if (settings.indent_with_spaces)
                fmt::buf::ManipIO(ostream).pushback(' ', indent_ * settings.indent_size).value();
            else
                fmt::buf::ManipIO(ostream).pushback('\t', indent_ * settings.indent_size).value();
        }

        void NewLine() {
            if (settings.one_line) return;
            fmt::buf::ManipIO(ostream).pushback('\n').value();
            indent();
        }
        void begin_new_object() {
            ++indent_;
        }
        void end_new_object() {
            --indent_;
        }

    public:
        fmt::buf::StreamIO<char>& ostream;
        FormatSettings            settings;

    protected:
        std::size_t indent_;
    };
}  // namespace stream::json::detail

namespace stream::json::detail {
    struct JsonFormatter::StructIntermediate {
    public:
        StructIntermediate(JsonFormatter& formatter);
        ~StructIntermediate();

    public:
        template <typename T>
        void format(const std::string_view name, const T& t);

    public:
        JsonFormatter& Formatter;
        std::uint32_t  Idx;
    };

    struct JsonFormatter::ArrayIntermediate {
    public:
        ArrayIntermediate(JsonFormatter& formatter);
        ~ArrayIntermediate();

    public:
        template <typename T>
        void format(const T& t);

    public:
        JsonFormatter& Formatter;
        std::uint32_t  Idx;
    };

    inline JsonFormatter::StructIntermediate JsonFormatter::get_struct_intermediate() {
        return JsonFormatter::StructIntermediate(*this);
    }

    inline JsonFormatter::ArrayIntermediate JsonFormatter::get_array_intermediate() {
        return JsonFormatter::ArrayIntermediate(*this);
    }
}  // namespace stream::json::detail
