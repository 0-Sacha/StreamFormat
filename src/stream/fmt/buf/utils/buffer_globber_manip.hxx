#pragma once

#include "stream/fmt/buf/stream.hxx"
#include "stream/fmt/buf/manip.hxx"

namespace stream::fmt::buf {
    template <typename TChar>
    class Globber {
    public:
        enum class PatternMatchType {
            MatchBiggest,
            MatchSmallest
        };

    private:
        [[nodiscard]] static std::expected<const TChar*, FMTResult> buffer_exec_glob_(Stream<TChar>& istream, Stream<TChar>& glob) {
            if (Access(glob).is_end_of_string()) {
                return istream.current_pos;
            }

            if (Access(istream).is_end_of_string()) {
                return nullptr;
            }

            if (TestAccess(glob).is_equal_to('?')) {
                SF_VERIFY(Manip(glob).forward());
                SF_VERIFY(Manip(istream).forward());
                return buffer_exec_glob_(istream, glob);
            } else if (TestAccess(glob).is_equal_to('*')) {
                SF_VERIFY(Manip(glob).forward());
                const TChar* further = SF_TRY(buffer_exec_glob_(istream, glob));
                while (Access(istream).can_move_forward()) {
                    SF_VERIFY(Manip(istream).forward());
                    const TChar* last = SF_TRY(buffer_exec_glob_(istream, glob));
                    if (last > further || further == nullptr) further = last;
                }
                return further;
            } else if (TestAccess(glob).is_equal_to('[')) {
                SF_VERIFY(Manip(istream).forward());
                const TChar* begin = glob.current_pos;
                SF_VERIFY(TestManip(glob).go_to_forward(']'));
                const TChar* end = glob.current_pos;

                StreamView<TChar> charSet(begin, end - begin);

                bool  is_inverted = TestAccess(glob).is_equal_to('!');
                TChar toMatch     = istream.get();
                SF_VERIFY(Manip(glob).forward());
                SF_VERIFY(Manip(istream).forward());
                bool found = false;

                while (found == false && Access(charSet).can_move_forward()) {
                    if (TestAccess(charSet).is_equal_to(toMatch)) {
                        found = true;
                        break;
                    }

                    if (TestAccess(charSet).is_equal_to('-')) {
                        TChar beginSubSet = Access(charSet).get_prev_force();
                        TChar endSubSet   = Access(charSet).get_next_force();
                        if (toMatch >= beginSubSet && toMatch <= endSubSet) {
                            found = true;
                            break;
                        }
                    }

                    Manip(charSet).forward();
                }

                if (found && is_inverted == false)
                    return buffer_exec_glob_(istream, glob);
                else if (found == false && is_inverted == true)
                    return buffer_exec_glob_(istream, glob);
                return nullptr;
            }

            if (istream.get() == glob.get()) {
                SF_VERIFY(Manip(glob).forward());
                SF_VERIFY(Manip(istream).forward());
                return buffer_exec_glob_(istream, glob);
            }
            return nullptr;
        }

    public:
        [[nodiscard]] static std::expected<void, FMTResult> buffer_exec_glob(Stream<TChar>& istream, Stream<TChar>& glob,
                                                                             [[maybe_unused]] PatternMatchType patternMatchtype = PatternMatchType::MatchBiggest) {
            const TChar* furtherPointMatched = SF_TRY(buffer_exec_glob_(istream, glob));
            if (furtherPointMatched != nullptr) istream.current_pos = furtherPointMatched;
            return {};
        }
    };

    template <typename TChar>
    class BufferGlobberManip {
    public:
        constexpr inline BufferGlobberManip(Stream<TChar>& buffer) noexcept : buffer(buffer) {}

    public:
        Stream<TChar>& buffer;

    public:
        [[nodiscard]] std::expected<void, FMTResult> fast_read_char_ptrGlobber(std::basic_string_view<TChar> globPattern, TChar* str, std::size_t size_to_copy) {
            Stream<TChar> globber(globPattern);
            const TChar*  begin = buffer.current_pos;
            Globber<TChar>::buffer_exec_glob(*this, globber);
            const TChar* end = buffer.current_pos;

            Stream<TChar> subContext(begin, end);
            return ReadManip(subContext).fast_read_char_ptr(str, size_to_copy);
        }

        [[nodiscard]] std::expected<void, FMTResult> fast_read_char_ptrRegex(std::basic_string_view<TChar> regexPattern, TChar* str, std::size_t size_to_copy) {
            return std::unexpected(FMTResult::FunctionNotImpl);
        }
    };
}  // namespace stream::fmt::buf
