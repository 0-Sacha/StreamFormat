#pragma once

#include "json_formatter.hxx"
#include "json_parser.hxx"

#include "stream/fmt.hxx"
#include "stream/fmt/buf/read_manip.hxx"
#include "stream/fmt/buf/write_manip.hxx"
#include "stream/fmt/buf/utils/buffer_utils.hxx"

#include <functional>
#include <string>

namespace stream::json {
    template <typename T>
    struct JsonSerializer {
        static inline void parse(T&, detail::JsonParser&) {
#ifdef UNKOWN_TYPE_MESSAGE
            fmt::file_print(std::cerr, "{C:red}JsonSerializer::Parse<{}> not impl", typeid(T).name()).value();
#endif
#ifdef UNKOWN_TYPE_THROW
            throw detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_FAIL
            // FIXME
            throw detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_DEBUG
            STREAMFORMAT_DEBUGBREAK();
#endif
        }

        static inline void format(const T&, detail::JsonFormatter& formatter) {
            fmt::buf::WriteManip(formatter.ostream).fast_write_string(std::string_view("Unknown JsonFormatter for type : ")).value();
            fmt::buf::WriteManip(formatter.ostream).fast_write_string(std::string_view(typeid(T).name())).value();

#ifdef UNKOWN_TYPE_MESSAGE
            fmt::file_print(std::cerr, "{C:red}JsonSerializer::Format<{}> not impl", typeid(T).name()).value();
#endif
#ifdef UNKOWN_TYPE_THROW
            throw detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_FAIL
            // FIXME
            throw detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_DEBUG
            STREAMFORMAT_DEBUGBREAK();
#endif
        }
    };

    template <typename T>
    struct JsonObjectSerializer {
        static inline void ReadObject(T&, const JsonObject&) {
#ifdef UNKOWN_TYPE_MESSAGE
            fmt::file_print(std::cerr, "{C:red}JsonObjectSerializer::ReadObject<{}> not impl", typeid(T).name()).value();
#endif
#ifdef UNKOWN_TYPE_THROW
            throw detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_FAIL
            // FIXME
            throw detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_DEBUG
            STREAMFORMAT_DEBUGBREAK();
#endif
        }

        static inline void WriteObject(const T&, JsonObject&) {
#ifdef UNKOWN_TYPE_MESSAGE
            fmt::file_print(std::cerr, "{C:red}JsonObjectSerializer::WriteObject<{}> not impl", typeid(T).name()).value();
#endif
#ifdef UNKOWN_TYPE_THROW
            throw detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_FAIL
            // FIXME
            throw detail::JsonTypeSerializerNotImpl{};
#endif
#ifdef UNKOWN_TYPE_DEBUG
            STREAMFORMAT_DEBUGBREAK();
#endif
        }
    };

    struct JsonStringSerializer {
        static inline void ParseSTDString(std::string& t, detail::JsonParser& parser) {
            fmt::buf::DynamicStreamIOManager<char> bufferData;
            fmt::buf::StreamIO<char>               buffer = fmt::buf::StreamIO<char>::create(bufferData).value();
            fmt::buf::utils::parse_escaped_quoted_string(parser.istream, buffer).value();
            fmt::buf::ManipIO(buffer).compute_generated_size();
            t = bufferData.get_last_generated_string_view();
        }

        static inline void FormatSTDString(const std::string_view t, detail::JsonFormatter& formatter) {
            fmt::buf::Stream<const char> buffer(t.data(), t.size());
            fmt::buf::utils::format_escaped_quoted_string(formatter.ostream, buffer).value();
        }
    };

    struct JsonNumberSerializer {
        template <typename FloatType>
        static inline void ParseFloat(FloatType& t, detail::JsonParser& parser) {
            fmt::buf::ReadManip(parser.istream).fast_read_float(t).value();
        }

        template <typename IntType>
        static inline void ParseInteger(IntType& t, detail::JsonParser& parser) {
            const char* begin = parser.istream.current_pos;
            float       tmp   = 0;
            fmt::buf::ReadManip(parser.istream).fast_read_float(tmp).value();
            const char* end = parser.istream.current_pos;

            parser.istream.current_pos = begin;
            fmt::buf::ReadManip(parser.istream).fast_read_integer(t).value();
            parser.istream.current_pos = end;
        }

        template <typename FloatType>
        static inline void FormatFloat(const FloatType& t, detail::JsonFormatter& formatter) {
            fmt::buf::WriteManip(formatter.ostream).fast_write_float(t, formatter.settings.float_precision).value();
        }

        template <typename IntType>
        static inline void FormatInteger(const IntType& t, detail::JsonFormatter& formatter) {
            fmt::buf::WriteManip(formatter.ostream).fast_write_integer(t).value();
        }
    };

    struct JsonBooleanSerializer {
        static inline void ParseBool(bool& t, detail::JsonParser& parser) {
            if (fmt::buf::TestManip<const char>(parser.istream).is_same_forward("true", 5).value())
                t = true;
            else if (fmt::buf::TestManip<const char>(parser.istream).is_same_forward("false", 5).value())
                t = false;
        }

        static inline void FormatBool(const bool& t, detail::JsonFormatter& formatter) {
            if (t)
                fmt::buf::WriteManip(formatter.ostream).fast_write_char_array("true", 5).value();
            else
                fmt::buf::WriteManip(formatter.ostream).fast_write_char_array("false", 5).value();
        }
    };

    struct JsonStructSerializer {
        template <typename T>
        static inline void LoadAllSubObjects(T& t, detail::JsonParser& parser, std::function<void(T&, std::size_t, std::string&&, detail::JsonParser&)> subObjectParsingFunction) {
            fmt::buf::TestAccess access(parser.istream);
            fmt::buf::TestManip  manip(parser.istream);

            manip.skip_one_of('{').value();
            std::size_t idx = 0;

            while (fmt::buf::Access(parser.istream).is_end_of_string() == false) {
                manip.GoTo('"', '}');
                if (access.is_equal_to('}')) break;

                std::string name;
                JsonStringSerializer::ParseSTDString(name, parser);

                manip.IgnoreEveryBlanks();
                manip.skip_one_of(':').value();
                manip.IgnoreEveryBlanks();

                subObjectParsingFunction(t, idx++, std::move(name), parser);

                manip.GoTo(',', '}');
                manip.skip_one_of(',').value();
            }

            manip.skip_one_of('}').value();
        }

        template <typename T>
        static inline void LoadAllSubObjects(T& t, detail::JsonParser& parserObject) {
            LoadAllSubObjects<T>(t, parserObject, [](T& mainObject, std::size_t idx, std::string&& name, detail::JsonParser& parser) {
                typename JsonSerializer<T>::StructSubObjectType subObject;
                parser.parse(subObject);
                JsonSerializer<T>::add_struct_sub_object(mainObject, idx, std::move(name), std::move(subObject));
            });
        }

        static inline void FormatBegin(detail::JsonFormatter& formatter) {
            fmt::buf::ManipIO(formatter.ostream).pushback('{').value();
        }

        static inline void FormatEnd(detail::JsonFormatter& formatter) {
            formatter.NewLine();
            fmt::buf::ManipIO(formatter.ostream).pushback('}').value();
        }

        template <typename SubObject>
        static inline void FormatObject(const std::string_view name, const SubObject& subObject, const std::size_t idx, detail::JsonFormatter& formatter) {
            if (idx != 0) fmt::buf::ManipIO(formatter.ostream).pushback(',').value();

            formatter.begin_new_object();
            formatter.NewLine();
            JsonStringSerializer::FormatSTDString(name, formatter);
            fmt::buf::ManipIO(formatter.ostream).pushback(':').value();
            fmt::buf::ManipIO(formatter.ostream).pushback(' ').value();
            formatter.format(subObject);
            formatter.end_new_object();
        }
    };

    struct JsonArraySerializer {
        template <typename T>
        static inline void LoadAllSubObjects(T& t, detail::JsonParser& parser, std::function<void(T&, std::size_t, detail::JsonParser&)> subObjectParsingFunction) {
            fmt::buf::TestAccess access(parser.istream);
            fmt::buf::TestManip  manip(parser.istream);

            manip.skip_one_of('[').value();
            std::size_t idx = 0;

            while (fmt::buf::Access(parser.istream).is_end_of_string() == false) {
                manip.IgnoreEveryBlanks();

                if (access.is_equal_to(']')) break;

                subObjectParsingFunction(t, idx++, parser);

                manip.GoTo(',', ']');
                manip.skip_one_of(',').value();
            }

            manip.skip_one_of(']').value();
        }

        template <typename T>
        static inline void LoadAllSubObjects(T& t, detail::JsonParser& parser) {
            LoadAllSubObjects<T>(t, parser, [](T& mainObject, std::size_t idx, detail::JsonParser& json_parser) {
                typename JsonSerializer<T>::ArraySubObjectType subObject;
                json_parser.parse(subObject);
                JsonSerializer<T>::AddArraySubObject(mainObject, idx, std::move(subObject));
            });
        }

        static inline void FormatBegin(detail::JsonFormatter& formatter) {
            fmt::buf::ManipIO(formatter.ostream).pushback('[').value();
        }

        static inline void FormatEnd(detail::JsonFormatter& formatter) {
            formatter.NewLine();
            fmt::buf::ManipIO(formatter.ostream).pushback(']').value();
        }

        template <typename SubObject>
        static inline void FormatObject(const SubObject& subObject, const std::size_t idx, detail::JsonFormatter& formatter) {
            if (idx != 0) fmt::buf::ManipIO(formatter.ostream).pushback(',').value();

            formatter.begin_new_object();
            formatter.NewLine();
            formatter.format(subObject);
            formatter.end_new_object();
        }
    };

    struct JsonNullSerializer {
        static inline void ParseNull(detail::JsonParser& parser) {
            fmt::buf::TestManip(parser.istream).is_same_forward("null", 4).value();
        }

        static inline void FormatNull(detail::JsonFormatter& formatter) {
            fmt::buf::WriteManip(formatter.ostream).fast_write_char_array("null", 4).value();
        }
    };
}  // namespace stream::json

namespace stream::json::detail {
    template <typename T>
    void JsonFormatter::format(const T& t) {
        JsonSerializer<T>::format(t, *this);
    }

    template <typename T>
    void JsonParser::parse(T& t) {
        JsonSerializer<T>::parse(t, *this);
    }
}  // namespace stream::json::detail

namespace stream::json {
    template <typename T>
    struct FormatAsJson {
    public:
        FormatAsJson(const T& value) : value(value) {}

    public:
        const T& value;
    };
}  // namespace stream::json

#include "stream/fmt.hxx"
namespace stream::fmt {
#ifdef STREAMFORMAT_FORMATTER_DECLARED
    template <typename T, typename FormatterExecutor>
    struct FormatterType<json::FormatAsJson<T>, FormatterExecutor> {
        [[nodiscard]] static std::expected<void, FMTResult> format(const json::FormatAsJson<T>& json, FormatterExecutor& executor) {
            bool                                        ordered_struct = executor.data.specifiers.has("ordered_struct");
            json::detail::JsonFormatter::FormatSettings settings{.ordered_struct = ordered_struct, .float_precision = executor.data.float_precision};
            json::detail::JsonFormatter                 jsonFormatter(executor.ostream, settings);
            json::JsonSerializer<T>::format(json.value, jsonFormatter);
            return {};
        }
    };
#endif

#ifdef STREAMFORMAT_PARSER_DECLARED
    template <typename T, typename ParserExecutor>
    struct ParserType<json::FormatAsJson<T>, ParserExecutor> {
        [[nodiscard]] static std::expected<void, FMTResult> parse(T& json, ParserExecutor& executor) {
            json::detail::JsonParser json_parser(*executor.istream.Manager);
            json_parser.istream.current_pos = executor.istream.current_pos;
            // TODO:
            // json::JsonSerializer<T>::parse(json.value, json_parser);
            executor.istream.current_pos = json_parser.istream.current_pos;
            return {};
        }
    };
#endif
}  // namespace stream::fmt
