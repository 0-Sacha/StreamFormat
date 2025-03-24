#pragma once

#include "stream.hxx"
#include "manip.hxx"

#include "streamio_manager/basic_streamio_manager.hxx"

namespace stream::fmt::buf {
    template <typename CharType>
    class StreamIO : public Stream<CharType> {
    public:
        using typename Stream<CharType>::TChar;

        using Stream<CharType>::buffer;
        using Stream<CharType>::current_pos;
        using Stream<CharType>::buffer_end;

        using Stream<CharType>::get;
        using Stream<CharType>::get_buffer_total_size;
        using Stream<CharType>::get_buffer_current_size;
        using Stream<CharType>::get_buffer_remaining_size;
        using Stream<CharType>::is_out_of_bound;
        using Stream<CharType>::is_empty;
        using Stream<CharType>::is_end_of_string;

    protected:
        StreamIO(BasicStreamIOManager<CharType>& ostream_manager) noexcept : Stream<CharType>(), manager(ostream_manager) {}

    protected:
        static void init(StreamIO<CharType>& in) {
            in.manager.begin_context();
            Manip(in).reload(in.manager.get_buffer(), in.manager.get_buffer_size());
        }

    public:
        static StreamIO<CharType> create(BasicStreamIOManager<CharType>& ostream_manager) {
            StreamIO<CharType> res(ostream_manager);
            init(res);
            return res;
        }

    public:
        inline void set(const TChar c) noexcept {
            *current_pos = c;
        }

    public:
        BasicStreamIOManager<CharType>& manager;
    };

    template <typename T>
    concept convertible_to_streamio_info = requires(T&& t) { StreamIO(std::forward<T>(t)); };
}  // namespace stream::fmt::buf
