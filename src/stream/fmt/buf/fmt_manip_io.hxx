#pragma once

#include "stream.hxx"
#include "manip_io.hxx"
#include "test_manip.hxx"

namespace stream::fmt::buf {
    template <typename CharType>
    class FMTStreamIO : public StreamIO<CharType> {
    public:
        using typename StreamIO<CharType>::TChar;

        using StreamIO<CharType>::buffer;
        using StreamIO<CharType>::current_pos;
        using StreamIO<CharType>::buffer_end;

        using StreamIO<CharType>::get;

        using StreamIO<CharType>::Manager;

    protected:
        FMTStreamIO(BasicStreamIOManager<CharType>& ostream_manager) noexcept : StreamIO<CharType>(ostream_manager) {}

    public:
        [[nodiscard]] static std::expected<FMTStreamIO<CharType>, FMTResult> create(BasicStreamIOManager<CharType>& ostream_manager) {
            FMTStreamIO<CharType> res(ostream_manager);
            SF_VERIFY(StreamIO<CharType>::init(res));
            return res;
        }

    public:
        std::size_t NoStride = 0;
        std::size_t indent   = 0;
    };

    template <typename TChar>
    class FMTManipIO {
    public:
        FMTManipIO(FMTStreamIO<TChar>& buffer) : buffer(buffer) {}

    public:
        FMTStreamIO<TChar>& buffer;

    public:
        constexpr inline void add_no_stride(const std::size_t no_stride) noexcept {
            buffer.NoStride += no_stride;
        }

        constexpr inline void add_indent(const std::size_t indent) noexcept {
            buffer.indent += indent;
        }
        constexpr inline void remove_indent(const std::size_t indent) noexcept {
            buffer.indent -= indent;
        }
        constexpr inline void set_indent() noexcept {
            buffer.indent = Manip(buffer).get_buffer_current_size() - buffer.NoStride;
        }

    public:
        [[nodiscard]] constexpr inline std::expected<void, FMTResult> new_line_indent() {
            SF_VERIFY(ManipIO(buffer).pushback('\n'));
            return ManipIO(buffer).pushback(' ', buffer.indent);
        }

        [[nodiscard]] constexpr inline std::expected<void, FMTResult> pushback_check_indent(const TChar c) {
            SF_VERIFY(ManipIO(buffer).pushback(c));
            if (c == '\n') {
                return ManipIO(buffer).pushback(' ', buffer.indent);
            }
            return {};
        }
    };

    template <typename TChar>
    class FMTParamsManip {
    public:
        FMTParamsManip(Stream<TChar>& buffer) : buffer(buffer) {}

    public:
        Stream<TChar>& buffer;

    public:
        template <typename... CharToTest>
        inline void param_go_to(const CharToTest... ele) {
            TestManip(buffer).GoTo(ele..., '}');
        }
        template <typename... CharToTest>
        [[nodiscard]] inline std::expected<void, FMTResult> param_go_to_forward(const CharToTest... ele) {
            return TestManip(buffer).go_to_forward(ele..., '}');
        }

        inline bool is_begin_of_parameter() {
            return TestAccess(buffer).is_equal_to('{');
        }
        inline bool is_end_of_parameter() {
            return TestAccess(buffer).is_equal_to('}');
        }

    public:
        template <typename CharToTest>
        [[nodiscard]] std::expected<bool, FMTResult> next_is_named_args(const std::basic_string_view<CharToTest>& sv) {
            TestAccess access(buffer);
            TestManip  manip(buffer);

            TChar* const oldpos = buffer.current_pos;

            auto is_same = manip.is_same_forward(sv);
            if (is_same.has_value() == false) return std::unexpected(is_same.error());
            if (is_same.value() && (access.is_equal_to(':') || access.is_equal_to('}'))) {
                return true;
            }
            buffer.current_pos = oldpos;
            return false;
        }
    };
}  // namespace stream::fmt::buf
