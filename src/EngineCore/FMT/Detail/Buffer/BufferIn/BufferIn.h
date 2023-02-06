#pragma once

#include "FMT/Detail/Buffer/BasicBuffer.h"

namespace EngineCore::FMT::Detail {

    template<typename CharBuffer>
    class BasicFormatterMemoryBufferIn : public BasicFormatterMemoryBuffer<const CharBuffer> {

    protected:
        using Base = BasicFormatterMemoryBuffer<const CharBuffer>;
        using Base::m_Buffer;
        using Base::m_BufferEnd;
        using Base::m_BufferSize;
        using Base::m_CurrentPos;

    public:
        using typename Base::StringView;

    public:
        using CharBufferType = CharBuffer;

        using Base::GetBuffer;
        using Base::GetBufferCurrentPos;
        using Base::GetBufferEnd;
        using Base::GetBufferSize;
        using Base::GetBufferCurrentSize;
        using Base::SetBufferCurrentPos;
        using Base::SetParentBufferForUpdate;

    public:
        using Base::CanMoveForward;
        using Base::CanMoveBackward;
        using Base::IsNotOutOfBound;

        using Base::IsEnd;

        using Base::CanMoveForwardThrow;
        using Base::CanMoveBackwardThrow;
        using Base::IsNotOutOfBoundThrow;
        using Base::IsEndThrow;

        using Base::Forward;
        using Base::ForwardNoCheck;
        using Base::Backward;
        using Base::BackwardNoCheck;
        using Base::ForwardNoThrow;
        using Base::ForwardNoCheckNoThrow;
        using Base::BackwardNoThrow;
        using Base::BackwardNoCheckNoThrow;

        using Base::Get;
        using Base::GetAndForward;
        using Base::GetAndForwardNoCheck;
        using Base::GetAndBackward;
        using Base::GetAndBackwardNoCheck;
        using Base::GetNext;
        using Base::GetNextNoCheck;

        using Base::UpdateFromChlid;

    public:
        explicit BasicFormatterMemoryBufferIn()
            : Base()
        {}

        explicit BasicFormatterMemoryBufferIn(const std::basic_string_view<CharBuffer>& buffer)
            : Base(buffer)
        {}

        explicit BasicFormatterMemoryBufferIn(const CharBuffer* const buffer, const std::size_t bufferSize)
            : Base(buffer, bufferSize)
        {}

        template <typename ParentBuffer>
        explicit BasicFormatterMemoryBufferIn(ParentBuffer& parentBuffer)
            : Base(parentBuffer.GetBuffer(), parentBuffer.GetBufferCurrentPos(), parentBuffer.GetBufferEnd(), parentBuffer.GetBufferSize())
        {
            SetParentBufferForUpdate(&parentBuffer);
        }

        ~BasicFormatterMemoryBufferIn() {
            // Should call the destructo but doesn't compile : BasicFormatterMemoryBuffer<CharBuffer>::~BasicFormatterMemoryBuffer();
            UpdateFromChlid();
        }

    public:
        template<typename T> void FastReadInt	(T& i);
        template<typename T> void FastReadUInt	(T& i);
        template<typename T> void FastReadFloat	(T& i, FloatPrecision floatPrecision = FloatPrecision{});
        
        template<typename T> void BasicReadInt		(T& i, ShiftType st = ShiftType::Nothing, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{});
        template<typename T> void BasicReadUInt		(T& i, ShiftType st = ShiftType::Nothing, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{});
        template<typename T> void BasicReadFloat	(T& i, FloatPrecision floatPrecision = FloatPrecision{}, ShiftType st = ShiftType::Nothing, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{});
        
        template<typename T> void BasicReadIntAsBin	(T& i, DigitSize digitSize = DigitSize{}, ShiftType st = ShiftType::Nothing, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{}, bool trueValue = false);
        template<typename T> void BasicReadIntAsHex	(T& i, DigitSize digitSize = DigitSize{}, ShiftType st = ShiftType::Nothing, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{}, bool trueValue = false, Detail::PrintStyle valueDes = PrintStyle::Nothing);
        template<typename T> void BasicReadIntAsOct	(T& i, DigitSize digitSize = DigitSize{}, ShiftType st = ShiftType::Nothing, ShiftSize shift = ShiftSize{}, ShiftPrint sp = ShiftPrint{}, bool trueValue = false);


    public:
        template<typename T, typename FormatDataCharType> void ReadIntFormatData	(T& i, const FormatData<FormatDataCharType>& formatData);
        template<typename T, typename FormatDataCharType> void ReadUIntFormatData	(T& i, const FormatData<FormatDataCharType>& formatData);
        template<typename T, typename FormatDataCharType> void ReadFloatFormatData	(T& i, const FormatData<FormatDataCharType>& formatData);

    public:
        // Basic types
        template<typename T> bool BasicReadType(T& i) { return false; }

        inline void BasicReadType(std::int8_t& i)	{ return FastReadInt(i); 	}
        inline void BasicReadType(std::uint8_t& i)	{ return FastReadUInt(i); 	}
        inline void BasicReadType(std::int16_t& i)	{ return FastReadInt(i);	}
        inline void BasicReadType(std::uint16_t& i)	{ return FastReadUInt(i); 	}
        inline void BasicReadType(std::int32_t& i)	{ return FastReadInt(i);	}
        inline void BasicReadType(std::uint32_t& i)	{ return FastReadUInt(i); 	}
        inline void BasicReadType(std::int64_t& i)	{ return FastReadInt(i);	}
        inline void BasicReadType(std::uint64_t& i)	{ return FastReadUInt(i); 	}

        inline void BasicReadType(float& i)			{ return FastReadFloat(i);	}
        inline void BasicReadType(double& i)		{ return FastReadFloat(i);	}
        inline void BasicReadType(long double& i)	{ return FastReadFloat(i);	}

        inline void BasicReadType(char& i)		{ i = Base::GetAndForward(); return; }
        inline void BasicReadType(wchar_t& i)	{ i = Base::GetAndForward(); return; }
        inline void BasicReadType(char16_t& i)	{ i = Base::GetAndForward(); return; }
        inline void BasicReadType(char32_t& i)	{ i = Base::GetAndForward(); return; }

        template<std::size_t SIZE> inline void BasicReadType(char(&i)[SIZE])		{ /* TODO */ return; }
        template<std::size_t SIZE> inline void BasicReadType(wchar_t(&i)[SIZE])		{ /* TODO */ return; }
        template<std::size_t SIZE> inline void BasicReadType(char16_t(&i)[SIZE])	{ /* TODO */ return; }
        template<std::size_t SIZE> inline void BasicReadType(char32_t(&i)[SIZE])	{ /* TODO */ return; }

        template<typename CharType> inline bool BasicReadType(std::basic_string_view<CharType>& i) { /* TODO */ return true; }

    public:
        // Format check
        inline bool IsEqualTo(const CharBuffer c) const				{ return Get() == c; }
        inline bool IsNotEqualTo(const CharBuffer c) const			{ return Get() != c; }
        inline bool IsEqualToForward(const CharBuffer c)				{ if (IsEqualTo(c)) { Forward(); return true; } return false; }
        inline bool IsNotEqualForward(const CharBuffer c)			{ if (IsNotEqualTo(c)) { Forward(); return true; } return false; }
        template<typename ...CharToTest> inline bool IsEqualTo(const CharBuffer c, const CharToTest ...ele) const		{ return IsEqualTo(c) || IsEqualTo(ele...); }
        template<typename ...CharToTest> inline bool IsEqualToForward(const CharToTest ...ele)							{ if (IsEqualTo(ele...)) { Forward(); return true; } return false; }
        template<typename ...CharToTest> inline bool IsNotEqualTo(const CharBuffer c, const CharToTest ...ele) const	{ return IsNotEqualTo(c) && IsNotEqualTo(ele...); }
        template<typename ...CharToTest> inline bool IsNotEqualForward(const CharToTest ...ele)							{ if (IsNotEqualTo(ele...)) { Forward(); return true; } return false; }
        // Auto throw variant
        template<typename ...CharToTest> inline void IsEqualToThrow(const CharBuffer c, const CharToTest ...ele) const		{ if (IsEqualTo(c, ele...)) return; throw FormatParseError(); }
        template<typename ...CharToTest> inline void IsEqualToForwardThrow(const CharToTest ...ele)							{ if (IsEqualToForward(ele...)) return; throw FormatParseError(); }
        template<typename ...CharToTest> inline void IsNotEqualToThrow(const CharBuffer c, const CharToTest ...ele) const	{ if (IsNotEqualTo(c, ele...)) return; throw FormatParseError(); }
        template<typename ...CharToTest> inline void IsNotEqualForwardThrow(const CharToTest ...ele)						{ if (IsNotEqualForward(ele...)) return; throw FormatParseError(); }
        
        template<typename ...CharToTest> inline bool IsSeqOrderEqualToImpl(const CharBuffer* buffer, const CharBuffer c, const CharToTest ...ele) const	{ if (*buffer != c) return false; return IsSeqOrderEqualToImpl(++buffer, ele...); }
        template<typename ...CharToTest> inline bool IsSeqOrderEqualTo(const CharToTest ...ele) const	                                                { if (CanMoveForward(sizeof...(ele)) == false) return false; return IsSeqOrderEqualToImpl(m_Buffer, ele...); }

        // Format Next check
        inline bool NextIsEqualTo(const CharBuffer c) const			{ return GetNext() == c; }
        inline bool NextIsNotEqualTo(const CharBuffer c) const		{ return GetNext() != c; }
        inline bool NextIsEqualToForward(const CharBuffer c)			{ Forward(); if (!IsEqualTo(c)) { BackwardNoCheck(); return false; } return true; }
        inline bool NextIsNotEqualForward(const CharBuffer c)		{ Forward(); if (!IsNotEqualTo(c)) { BackwardNoCheck(); return false; } return true; }
        template<typename ...CharToTest> inline bool NextIsEqualToForward(const CharToTest ...ele)		{ Forward(); if (IsEqualTo(ele...)) { return true; } BackwardNoCheck(); return false; }
        template<typename ...CharToTest> inline bool NextIsEqualTo(const CharToTest ...ele) const		{ Forward(); if (IsEqualTo(ele...)) { BackwardNoCheck(); return true; } BackwardNoCheck(); return false; }
        template<typename ...CharToTest> inline bool NextIsNotEqualForward(const CharToTest ...ele)		{ Forward(); if (IsNotEqualTo(ele...)) { return true; } BackwardNoCheck(); return false; }
        template<typename ...CharToTest> inline bool NextIsNotEqualTo(const CharToTest ...ele) const	{ Forward(); if (IsNotEqualTo(ele...)) { BackwardNoCheck(); return true; } BackwardNoCheck(); return false; }
        // Auto throw variant
        template<typename ...CharToTest> inline void NextIsEqualToThrow(const CharBuffer c, const CharToTest ...ele) const		{ if (NextIsEqualTo(c, ele...)) return; throw FormatParseError(); }
        template<typename ...CharToTest> inline void NextIsEqualToForwardThrow(const CharToTest ...ele)							{ if (NextIsEqualToForward(ele...)) return; throw FormatParseError(); }
        template<typename ...CharToTest> inline void NextIsNotEqualToThrow(const CharBuffer c, const CharToTest ...ele) const	{ if (NextIsNotEqualTo(c, ele...)) return; throw FormatParseError(); }
        template<typename ...CharToTest> inline void NextIsNotEqualForwardThrow(const CharToTest ...ele)						{ if (NextIsNotEqualForward(ele...)) return; throw FormatParseError(); }

    public:
        inline bool IsLowerCase() const			{ return Get() >= 'a' && Get() <= 'z'; }
        inline bool IsUpperCase() const			{ return Get() >= 'A' && Get() <= 'Z'; }
        inline bool IsADigit() const			{ return Get() >= '0' && Get() <= '9'; }
        inline void IsLowerCaseThrow() const	{ if (IsLowerCase()) return; throw FormatParseError(); }
        inline void IsUpperCaseThrow() const	{ if (IsUpperCase()) return; throw FormatParseError(); }
        inline void IsADigitThrow() const		{ if (IsADigit()) return; throw FormatParseError(); }

    public:
        template<typename CharToTest> bool NextIsSame(const std::basic_string_view<CharToTest>& sv) {
            const CharToTest* str = sv.data();
            std::size_t size = sv.size();
            const CharBuffer* prevSubFormat = m_CurrentPos;		bool isSame = true;
            while (isSame && size-- != 0 && CanMoveForward())	isSame = GetAndForwardNoCheck() == *str++;
            if (isSame && size == 0)							isSame = false;
            if (!isSame)										m_CurrentPos = prevSubFormat;
            return isSame;
        }

        template<std::size_t SIZE, typename CharToTest> inline bool NextIsSame(const CharToTest(&data)[SIZE])			{ return NextIsSame(std::basic_string_view<CharToTest>(data)); }
        template<typename CharToTest> inline void NextIsSameThrow(const std::basic_string_view<CharToTest>& sv)			{ if (NextIsSame(sv)) return; throw FormatParseError(); }
        template<std::size_t SIZE, typename CharToTest> inline void NextIsSameThrow(const CharToTest(&data)[SIZE])		{ if (NextIsSame(data)) return; throw FormatParseError(); }


        template<typename CharToTest> bool NextIsANamedArgs(const std::basic_string_view<CharToTest>& sv) {
            const CharBuffer* const prevSubFormat = m_CurrentPos;
            if (NextIsSame(sv) && (IsEqualTo(':') || IsEqualTo('}'))) return true;
            m_CurrentPos = prevSubFormat;
            return false;
        }

        template<typename CharToTest> inline void NextIsANamedArgsThrow(const std::basic_string_view<CharToTest>& sv)	{ if (NextIsANamedArgs(sv)) return; throw FormatParseError(); }


        static constexpr std::size_t GET_WORD_FROM_LIST_NOT_FOUND = (std::numeric_limits<std::size_t>::max)();
        template<std::size_t SIZE>
        std::size_t GetWordFromList(const StringView (&data)[SIZE], const std::size_t defaultValue = GET_WORD_FROM_LIST_NOT_FOUND)
        {
            for (std::size_t idx = 0; idx < SIZE; ++idx)
                if (NextIsSame(data[idx]))
                    return idx;
            return defaultValue;
        }


        template<typename T>
        using TextTo = std::pair<StringView, T>;

        template<typename T, std::size_t SIZE>
        T GetWordFromList(const TextTo<T> (&data)[SIZE], T defaultValue = T{})
        {
            for (std::size_t idx = 0; idx < SIZE; ++idx)
                if (NextIsSame(data[idx].first))
                    return data[idx].second;
            return defaultValue;
        }

        // Format commands
    public:
        inline void IgnoreSpace()															{ while (IsEqualTo(' ') && CanMoveForward()) ForwardNoCheck(); }
        template<typename ...CharToTest> inline void GoTo(const CharToTest ...ele)			{ while (IsNotEqualTo(ele...) && CanMoveForward())	ForwardNoCheck(); }
        template<typename ...CharToTest> inline void GoToForward(const CharToTest ...ele)	{ GoTo(ele...); Forward(); }

    public:
        // TODO Better way
        template<typename ...CharToTest>
        StringView GoToAndGetStr(const CharToTest ...args)
        {
            const CharBuffer* begin = GetBufferCurrentPos();
            GoTo(args...);
            const CharBuffer* end = GetBufferCurrentPos();
            return StringView(begin, end); 
        }

        template<typename ...CharToTest>
        StringView GoToForwardAndGetStr(const CharToTest ...args)
        {
            const CharBuffer* begin = GetBufferCurrentPos();
            GoToForward(args...);
            const CharBuffer* end = GetBufferCurrentPos();
            return StringView(begin, end); 
        }
    
        // FIXME
        template <typename Func, typename... Args>
        StringView ExecAndGetStr(const Args& ...args)
        {
            const CharBuffer* begin = GetBufferCurrentPos();
            Func(std::forward<Args>(args)...);
            const CharBuffer* end = GetBufferCurrentPos();
            return StringView(begin, end); 
        }

    // Utils
    protected:
        template<typename T>
        void SkipShiftBeginSpace(const Detail::ShiftType st, const Detail::ShiftPrint sp, T& shift) {
            if (sp.BeforeIsADigit() == false)
                return;
            if (st == ShiftType::Right || st == ShiftType::CenterLeft || st == ShiftType::CenterRight)
                while (Base::Get() == ' ') {
                    Base::Forward();
                    --shift;
                }
        }

        template<typename T>
        void SkipShiftEnd(const Detail::ShiftType st, const Detail::ShiftPrint sp, T& shift) {
            if (st == ShiftType::Left || st == ShiftType::CenterLeft || st == ShiftType::CenterRight)
                while (Base::Get() == ' ' && shift > 0) {
                    Base::Forward();
                    --shift;
                }
        }
    };
}
