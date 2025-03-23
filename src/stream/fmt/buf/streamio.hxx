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

    protected:
        StreamIO(BasicStreamIOManager<CharType>& ostream_manager) noexcept : Stream<CharType>(), Manager(ostream_manager) {}

    protected:
        [[nodiscard]] static std::expected<void, FMTResult> init(StreamIO<CharType>& in) {
            SF_TRY(in.Manager.BeginContext());
            Manip(in).reload(in.Manager.get_buffer(), in.Manager.get_buffer_size());
            return {};
        }

    public:
        [[nodiscard]] static std::expected<StreamIO<CharType>, FMTResult> create(BasicStreamIOManager<CharType>& ostream_manager) {
            StreamIO<CharType> res(ostream_manager);
            SF_TRY(init(res));
            return res;
        }

    public:
        inline void set(const TChar c) noexcept {
            *current_pos = c;
        }

    public:
        BasicStreamIOManager<CharType>& Manager;
    };

    template <typename T>
    concept convertible_to_streamio_info = requires(T&& t) { StreamIO(std::forward<T>(t)); };
}  // namespace stream::fmt::buf
