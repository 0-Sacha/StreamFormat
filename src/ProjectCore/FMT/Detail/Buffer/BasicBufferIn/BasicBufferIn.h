#pragma once

#include "ProjectCore/FMT/Detail/Buffer/BasicBuffer.h"
#include "ProjectCore/FMT/Detail/Buffer/BufferInProperties/BufferInProperties.h"

namespace ProjectCore::FMT::Detail {

    template<typename CharBuffer>
    class BasicBufferIn : public BasicBuffer<const CharBuffer>
    {
        
    protected:
        using Base = BasicBuffer<const CharBuffer>;
        using Base::m_Buffer;
        using Base::m_BufferEnd;
        using Base::m_CurrentPos;

    public:
        using typename Base::StringView;

    public:
        using Base::GetBuffer;
        using Base::GetBufferCurrentPos;
        using Base::GetBufferEnd;
		using Base::GetBufferSize;
		using Base::GetBufferSizeLeft;
        using Base::GetBufferCurrentSize;
		using Base::GetBufferRemainingSize;
		using Base::SetBufferCurrentPos;

        using Base::ReloadBuffer;
		using Base::SetBuffer;

    public:
        using Base::CanMoveForward;
        using Base::CanMoveForwardThrow;
        using Base::CanMoveBackward;
        using Base::CanMoveBackwardThrow;
        using Base::IsNotOutOfBound;
        using Base::IsNotOutOfBoundThrow;
        using Base::IsEnd;
        using Base::IsEndThrow;

        using Base::Forward;
        using Base::ForwardNoCheck;
        using Base::ForwardNoThrow;
        using Base::Backward;
        using Base::BackwardNoCheck;
        using Base::BackwardNoThrow;
		using Base::Reserve;

        using Base::Get;
        using Base::GetAndForward;
        using Base::GetAndForwardNoCheck;
        using Base::GetAndBackward;
        using Base::GetAndBackwardNoCheck;
        using Base::GetNext;
        using Base::GetNextNoCheck;
		using Base::GetPrev;
		using Base::GetPrevNoCheck;

    public:
        BasicBufferIn()
            : Base()
        {}

		BasicBufferIn(const BufferInProperties<CharBuffer>& properties)
            : Base(properties.GetBuffer(), properties.GetBufferSize())
        {}

 		BasicBufferIn(const CharBuffer* const buffer, const std::size_t bufferSize)
            : Base(buffer, bufferSize)
        {}

        BasicBufferIn(const CharBuffer* const begin, const CharBuffer* const end)
            : Base(begin, static_cast<std::size_t>(end - begin))
        {}

        ~BasicBufferIn() override = default;

    public:
        template<typename T> bool FastReadInt	(T& i);
        template<typename T> bool FastReadUInt	(T& i);
        template<typename T> bool FastReadFloat	(T& i, FloatPrecision floatPrecision = FloatPrecision{});

        template<typename CharPtr> bool FastReadCharPtr(CharPtr* str, std::size_t sizeToCopy, bool addZero = true);
		template<typename CharStr, std::size_t SIZE>	inline bool FastReadCharArray(CharStr(&str)[SIZE], bool addZero = true)				{ return FastReadCharPtr(str, SIZE - (addZero ? 1 : 0), addZero); }
    	template<typename CharStr> 						inline bool FastReadCharBound(CharStr* begin, CharStr* end, bool addZero = true)    { return FastReadCharPtr(begin, end - begin - (addZero ? 1 : 0), addZero); }

        template<typename CharPtr, typename CharPattern>
        bool FastReadCharPtrGlobber(std::basic_string_view<CharPattern> globPattern, CharPtr* str, std::size_t sizeToCopy, bool addZero = true);
        template<typename CharPtr, typename CharPattern>
        bool FastReadCharPtrRegex(std::basic_string_view<CharPattern> regexPattern, CharPtr* str, std::size_t sizeToCopy, bool addZero = true);
        template<typename CharStr, std::size_t SIZE, typename CharPattern>	inline bool FastReadCharArrayGlobber(std::basic_string_view<CharPattern> globPattern, CharStr(&str)[SIZE], bool addZero = true)					    { return FastReadCharPtrGlobber(globPattern, str, SIZE - (addZero ? 1 : 0), addZero); }
    	template<typename CharStr, typename CharPattern> 					inline bool FastReadCharBoundGlobber(std::basic_string_view<CharPattern> globPattern, CharStr* begin, CharStr* end, bool addZero = true) 	        { return FastReadCharPtrGlobber(globPattern, begin, end - begin - (addZero ? 1 : 0), addZero); }
        template<typename CharStr, std::size_t SIZE, typename CharPattern>	inline bool FastReadCharArrayRegex(std::basic_string_view<CharPattern> regexPattern, CharStr(&str)[SIZE], bool addZero = true)					    { return FastReadCharPtrRegex(regexPattern, str, SIZE - (addZero ? 1 : 0), addZero); }
    	template<typename CharStr, typename CharPattern> 					inline bool FastReadCharBoundRegex(std::basic_string_view<CharPattern> regexPattern, CharStr* begin, CharStr* end, bool addZero = true) 	        { return FastReadCharPtrRegex(regexPattern, begin, end - begin - (addZero ? 1 : 0), addZero); }


    public:
        template<typename T> void FastReadIntThrow      (T& i)                                                      { if (FastReadInt(i) == false) throw FMTParseError{}; }
        template<typename T> void FastReadUIntThrow     (T& i)                                                      { if (FastReadUInt(i) == false) throw FMTParseError{}; }
        template<typename T> void FastReadFloatThrow    (T& i, FloatPrecision floatPrecision = FloatPrecision{})    { if (FastReadFloat(i, floatPrecision) == false) throw FMTParseError{}; }
        template<typename CharPtr> void FastReadCharPtrThrow(CharPtr* str, std::size_t sizeContainer, std::size_t sizeToWrite = 0)  { if (FastReadCharPtr(str, sizeContainer, sizeToWrite) == false) throw FMTParseError{}; }
		template<typename CharStr, std::size_t SIZE>	inline void FastReadCharArrayThrow(CharStr(&str)[SIZE])					    { if (FastReadCharArray(str) == false) throw FMTParseError{}; }
    	template<typename CharStr> 						inline void FastReadCharBoundThrow(CharStr* begin, CharStr* end) 	        { if (FastReadCharBound(begin, end) == false) throw FMTParseError{}; }

        template<typename CharPtr, typename CharPattern>
        void FastReadCharPtrGlobberThrow(CharPtr* str, std::size_t sizeContainer, std::basic_string_view<CharPattern> globPattern)   { if (FastReadCharPtrGlobberThrow(str, sizeContainer, globPattern) == false) throw FMTParseError{}; }
        template<typename CharPtr, typename CharPattern>
        void FastReadCharPtrRegexThrow(CharPtr* str, std::size_t sizeContainer, std::basic_string_view<CharPattern> regexPattern)    { if (FastReadCharPtrRegex(str, sizeContainer, regexPattern) == false) throw FMTParseError{}; }
        template<typename CharStr, std::size_t SIZE, typename CharPattern>	inline void FastReadCharArrayGlobberThrow(CharStr(&str)[SIZE], std::basic_string_view<CharPattern> globPattern)					    { if (FastReadCharArrayGlobber(str, globPattern) == false) throw FMTParseError{}; }
    	template<typename CharStr, typename CharPattern> 					inline void FastReadCharBoundGlobberThrow(CharStr* begin, CharStr* end, std::basic_string_view<CharPattern> globPattern) 	        { if (FastReadCharBoundGlobber(begin, end, globPattern) == false) throw FMTParseError{}; }
		template<typename CharStr, typename CharPattern>					inline void FastReadStringViewGlobberThrow(std::basic_string_view<CharStr>& str, std::basic_string_view<CharPattern> globPattern)	{ if (FastReadStringViewGlobber(str, globPattern) == false) throw FMTParseError{}; }
        template<typename CharStr, std::size_t SIZE, typename CharPattern>	inline void FastReadCharArrayRegexThrow(CharStr(&str)[SIZE], std::basic_string_view<CharPattern> regexPattern)					    { if (FastReadCharArrayRegex(str, regexPattern) == false) throw FMTParseError{}; }
    	template<typename CharStr, typename CharPattern> 					inline void FastReadCharBoundRegexThrow(CharStr* begin, CharStr* end, std::basic_string_view<CharPattern> regexPattern) 	        { if (FastReadCharBoundRegex(begin, end, regexPattern) == false) throw FMTParseError{}; }
		template<typename CharStr, typename CharPattern>					inline void FastReadStringViewRegexThrow(std::basic_string_view<CharStr>& str, std::basic_string_view<CharPattern> regexPattern)	{ if (FastReadStringViewRegex(str, regexPattern) == false) throw FMTParseError{}; }

    public:
        // Format check
        inline bool IsEqualTo(const CharBuffer c) const				{ return Get() == c; }
        inline bool IsNotEqualTo(const CharBuffer c) const			{ return Get() != c; }
        inline bool IsEqualToForward(const CharBuffer c)			{ if (IsEqualTo(c)) { Forward(); return true; } return false; }
        inline bool IsNotEqualForward(const CharBuffer c)			{ if (IsNotEqualTo(c)) { Forward(); return true; } return false; }
        template<typename ...CharToTest> inline bool IsEqualTo(const CharBuffer c, const CharToTest ...ele) const		{ return IsEqualTo(c) || IsEqualTo(ele...); }
        template<typename ...CharToTest> inline bool IsEqualToForward(const CharToTest ...ele)							{ if (IsEqualTo(ele...)) { Forward(); return true; } return false; }
        template<typename ...CharToTest> inline bool IsNotEqualTo(const CharBuffer c, const CharToTest ...ele) const	{ return IsNotEqualTo(c) && IsNotEqualTo(ele...); }
        template<typename ...CharToTest> inline bool IsNotEqualForward(const CharToTest ...ele)							{ if (IsNotEqualTo(ele...)) { Forward(); return true; } return false; }
        // Auto throw variant
        inline bool IsEqualToThrow(const CharBuffer c) const		{ if (IsEqualTo(c)) return true; throw FMTParseError(); }
        inline bool IsNotEqualToThrow(const CharBuffer c) const	    { if (IsNotEqualTo(c)) return true; throw FMTParseError(); }
        inline bool IsEqualToForwardThrow(const CharBuffer c)		{ if (IsEqualToForward(c)) return true; throw FMTParseError(); }
        inline bool Skip(const CharBuffer c)		                { return IsEqualToForwardThrow(c); }
        inline bool IsNotEqualForwardThrow(const CharBuffer c)		{ if (IsNotEqualForward(c)) return true; throw FMTParseError(); }
        template<typename ...CharToTest> inline void IsEqualToThrow(const CharBuffer c, const CharToTest ...ele) const		{ if (IsEqualTo(c, ele...)) return; throw FMTParseError(); }
        template<typename ...CharToTest> inline void IsEqualToForwardThrow(const CharToTest ...ele)							{ if (IsEqualToForward(ele...)) return; throw FMTParseError(); }
        template<typename ...CharToTest> inline void IsNotEqualToThrow(const CharBuffer c, const CharToTest ...ele) const	{ if (IsNotEqualTo(c, ele...)) return; throw FMTParseError(); }
        template<typename ...CharToTest> inline void IsNotEqualForwardThrow(const CharToTest ...ele)						{ if (IsNotEqualForward(ele...)) return; throw FMTParseError(); }

        // Format Next check
        inline bool NextIsEqualTo(const CharBuffer c) const			{ return GetNext() == c; }
        inline bool NextIsNotEqualTo(const CharBuffer c) const		{ return GetNext() != c; }
        inline bool NextIsEqualToForward(const CharBuffer c)		{ Forward(); if (IsEqualTo(c)) { return true; } BackwardNoCheck(); return false; }
        inline bool NextIsNotEqualForward(const CharBuffer c)		{ Forward(); if (IsNotEqualTo(c)) { return true; } BackwardNoCheck(); return false; }
        template<typename ...CharToTest> inline bool NextIsEqualToForward(const CharToTest ...ele)		{ Forward(); if (IsEqualTo(ele...)) { return true; } BackwardNoCheck(); return false; }
        template<typename ...CharToTest> inline bool NextIsEqualTo(const CharToTest ...ele) const		{ Forward(); bool res = IsEqualTo(ele...); BackwardNoCheck(); return res; }
        template<typename ...CharToTest> inline bool NextIsNotEqualForward(const CharToTest ...ele)		{ Forward(); if (IsNotEqualTo(ele...)) { return true; } BackwardNoCheck(); return false; }
        template<typename ...CharToTest> inline bool NextIsNotEqualTo(const CharToTest ...ele) const	{ Forward(); bool res = IsNotEqualTo(ele...); BackwardNoCheck(); return res; }
        // Auto throw variant
        inline bool NextIsEqualToThrow(const CharBuffer c) const	    { if (NextIsEqualTo(c)) return true; throw FMTParseError(); }
        inline bool NextIsNotEqualToThrow(const CharBuffer c) const		{ if (NextIsNotEqualTo(c)) return true; throw FMTParseError(); }
        inline bool NextIsEqualToForwardThrow(const CharBuffer c)		{ if (NextIsEqualToForward(c)) return true; throw FMTParseError(); }
        inline bool NextIsNotEqualForwardThrow(const CharBuffer c)		{ if (NextIsNotEqualForward(c)) return true; throw FMTParseError(); }
        template<typename ...CharToTest> inline void NextIsEqualToThrow(const CharBuffer c, const CharToTest ...ele) const		{ if (NextIsEqualTo(c, ele...)) return; throw FMTParseError(); }
        template<typename ...CharToTest> inline void NextIsEqualToForwardThrow(const CharToTest ...ele)							{ if (NextIsEqualToForward(ele...)) return; throw FMTParseError(); }
        template<typename ...CharToTest> inline void NextIsNotEqualToThrow(const CharBuffer c, const CharToTest ...ele) const	{ if (NextIsNotEqualTo(c, ele...)) return; throw FMTParseError(); }
        template<typename ...CharToTest> inline void NextIsNotEqualForwardThrow(const CharToTest ...ele)						{ if (NextIsNotEqualForward(ele...)) return; throw FMTParseError(); }

        // Format Next check
        inline bool PrevIsEqualTo(const CharBuffer c) const			{ return GetPrev() == c; }
        inline bool PrevIsNotEqualTo(const CharBuffer c) const		{ return GetPrev() != c; }
        template<typename ...CharToTest> inline bool PrevIsEqualTo(const CharToTest ...ele) const		{ Backward(); bool res = IsEqualTo(ele...); Forward(); return res; }
        template<typename ...CharToTest> inline bool PrevIsNotEqualTo(const CharToTest ...ele) const	{ Backward(); bool res = IsNotEqualTo(ele...); Forward(); return res; }
        // Auto throw variant
        inline bool PrevIsEqualToThrow(const CharBuffer c) const	    { if (PrevIsEqualTo(c)) return true; throw FMTParseError(); }
        inline bool PrevIsNotEqualToThrow(const CharBuffer c) const		{ if (PrevIsNotEqualTo(c)) return true; throw FMTParseError(); }
        template<typename ...CharToTest> inline void PrevIsEqualToThrow(const CharBuffer c, const CharToTest ...ele) const		{ if (PrevIsEqualTo(c, ele...)) return; throw FMTParseError(); }
        template<typename ...CharToTest> inline void PrevIsNotEqualToThrow(const CharBuffer c, const CharToTest ...ele) const	{ if (PrevIsNotEqualTo(c, ele...)) return; throw FMTParseError(); }

    public:
        inline bool IsLowerCase() const			{ return Get() >= 'a' && Get() <= 'z'; }
        inline bool IsUpperCase() const			{ return Get() >= 'A' && Get() <= 'Z'; }
        inline bool IsADigit() const			{ return Get() >= '0' && Get() <= '9'; }
        inline bool IsLowerCaseForward() const  { if (IsLowerCase()) { Forward(); return true; } return false; }
        inline bool IsUpperCaseForward() const	{ if (IsUpperCase()) { Forward(); return true; } return false; }
        inline bool IsADigitForward() const		{ if (IsADigit())    { Forward(); return true; } return false; }

        inline void IsLowerCaseThrow() const	{ if (IsLowerCase()) return; throw FMTParseError(); }
        inline void IsUpperCaseThrow() const	{ if (IsUpperCase()) return; throw FMTParseError(); }
        inline void IsADigitThrow() const		{ if (IsADigit()) return; throw FMTParseError(); }
        inline void IsLowerCaseForwardThrow() const	{ if (IsLowerCaseForward()) return; throw FMTParseError(); }
        inline void IsUpperCaseForwardThrow() const	{ if (IsUpperCaseForward()) return; throw FMTParseError(); }
        inline void IsADigitForwardThrow() const	{ if (IsADigitForward()) return; throw FMTParseError(); }

    protected:
        template<typename CharToTest, typename ...Rest> inline bool IsSameSeq(const CharBuffer* buffer, const CharToTest c, const Rest ...ele) const    { if (*buffer != static_cast<const CharBuffer>(c)) return false; if constexpr (sizeof... (ele) == 0) return true; return IsSameImpl(++buffer, ele...); }
    public:
		template<typename ...CharToTest> inline bool IsSameSeq(const CharToTest ...ele) const                                                           { if (CanMoveForward(sizeof... (ele)) == false) return false; return IsSameSeqfImpl(m_Buffer, ele...); }

        template<typename CharToTest, typename ...Rest> bool IsSameSeqForward(const CharToTest c, const Rest ...ele)
        {
            if (IsEqualToForward(c))
            {
                if constexpr (sizeof...(ele) > 0)
                {
                    bool res = IsSameSeqForward(ele...);
                    if (res == false) Backward();
                    return res;
                }
                else
                    return true;
            }
            return false;
        }

		template<typename ...CharToTest> inline void IsSameSeqThrow(const CharToTest ...ele) const          { if (IsSameSeq(ele...)) return; throw FMTParseError(); }
		template<typename ...CharToTest> inline void IsSameSeqForwardThrow(const CharToTest ...ele)         { if (IsSameSeqForward(ele...)) return; throw FMTParseError(); }
        
	public:
		template<typename CharToTest> bool IsSame(const CharToTest* str, std::size_t size) const
        {
            if (str[size - 1] == 0)
                --size;
            if (size > GetBufferSizeLeft())
                return false;

            const CharBuffer* bufferStr = m_CurrentPos;
            bool isSame = true;
            while (isSame && size != 0 && *str != 0)            { isSame = *bufferStr++ == *str++; --size; }
            if (size != 0 && *str != 0)							isSame = false;
            return isSame;
        }

        template<std::size_t SIZE, typename CharToTest> inline bool IsSame(const CharToTest(&data)[SIZE]) const		    { return IsSame(data, SIZE); }
        template<typename CharToTest> inline bool IsSame(std::basic_string_view<CharToTest> sv)	const		            { return IsSame(sv.data(), sv.size()); }
        template<typename CharToTest> inline void IsSameThrow(const CharToTest* data, std::size_t size)	const	        { if (IsSame(data, size)) return; throw FMTParseError(); }
        template<std::size_t SIZE, typename CharToTest> inline void IsSameThrow(const CharToTest(&data)[SIZE]) const	{ if (IsSame(data)) return; throw FMTParseError(); }
        template<typename CharToTest> inline void IsSameThrow(const std::basic_string_view<CharToTest>& sv)	const	    { if (IsSame(sv)) return; throw FMTParseError(); }

        template<typename CharToTest> inline bool IsSameForward(const CharToTest* data, std::size_t size)		        { bool res = IsSame(data, size); if (res) ForwardNoCheck(data[size - 1] == 0 ? size - 1 : size); return res; }
        template<std::size_t SIZE, typename CharToTest> inline bool IsSameForward(const CharToTest(&data)[SIZE])		{ bool res = IsSame(data, SIZE); if (res) ForwardNoCheck(data[SIZE - 1] == 0 ? SIZE - 1 : SIZE); return res; }
        template<typename CharToTest> inline bool IsSameForward(std::basic_string_view<CharToTest> sv)			        { bool res = IsSame(sv); if (res) ForwardNoCheck(sv.size()); return res; }
        template<typename CharToTest> inline void IsSameForwardThrow(const CharToTest* data, std::size_t size)		    { if (IsSameForward(data, size)) return; throw FMTParseError(); }
        template<std::size_t SIZE, typename CharToTest> inline void IsSameForwardThrow(const CharToTest(&data)[SIZE])	{ if (IsSameForward(data)) return; throw FMTParseError(); }
        template<typename CharToTest> inline void IsSameForwardThrow(const std::basic_string_view<CharToTest>& sv)      { if (IsSameForward(sv)) return; throw FMTParseError(); }

        static constexpr std::size_t GET_WORD_FROM_LIST_NOT_FOUND = (std::numeric_limits<std::size_t>::max)();
        template<std::size_t SIZE>
        std::size_t GetWordFromList(const StringView (&data)[SIZE], const std::size_t defaultValue = GET_WORD_FROM_LIST_NOT_FOUND)
        {
            for (std::size_t idx = 0; idx < SIZE; ++idx)
                if (IsSameForward(data[idx]))
                    return idx;
            return defaultValue;
        }


        template<typename T>
        using TextTo = std::pair<StringView, T>;

        template<typename T, std::size_t SIZE>
        T GetWordFromList(const TextTo<T> (&data)[SIZE], T defaultValue = T{})
        {
            for (std::size_t idx = 0; idx < SIZE; ++idx)
                if (IsSameForward(data[idx].first))
                    return data[idx].second;
            return defaultValue;
        }

    public:
        inline void Ignore(const CharBuffer c) { IsEqualToForward(c); }
        template<typename ...CharToTest> inline void IgnoreAll(const CharToTest ...ele) { while (IsEqualTo(ele...) && CanMoveForward()) ForwardNoCheck(); }

		template<typename ...CharToTest> inline void GoTo(const CharToTest ...ele) { while (IsNotEqualTo(ele...) && CanMoveForward())	ForwardNoCheck(); }
		template<typename ...CharToTest> inline void GoToForward(const CharToTest ...ele) { GoTo(ele...); Forward(); }

    public:
		inline bool IsBlank() const             { return IsEqualTo(' ', '\t', '\r'); }
        inline bool IsBlankForward() const      { if (IsBlank()) { Forward(); return true; } return false; }
        inline void IsBlankThrow() const	        { if (IsBlank()) return; throw FMTParseError(); }
        inline void IsBlankForwardThrow() const     { if (IsBlankForward()) return; throw FMTParseError(); }
        
		inline void IgnoreSpace()       { Ignore(' ', '\t'); }
		inline void IgnoreBlank()       { Ignore(' ', '\t', '\n'); }

        inline void IgnoreAllSpaces()	{ IgnoreAll(' ', '\t'); }
        inline void IgnoreAllBlanks()	{ IgnoreAll(' ', '\t', '\n'); }

    public:
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

    public:
        // Basic types
        template<typename T> bool BasicReadType(T&) { return false; }

        inline void BasicReadType(std::int8_t& i)	{ return FastReadIntThrow(i); 	}
        inline void BasicReadType(std::uint8_t& i)	{ return FastReadUIntThrow(i); 	}
        inline void BasicReadType(std::int16_t& i)	{ return FastReadIntThrow(i);	}
        inline void BasicReadType(std::uint16_t& i)	{ return FastReadUIntThrow(i); 	}
        inline void BasicReadType(std::int32_t& i)	{ return FastReadIntThrow(i);	}
        inline void BasicReadType(std::uint32_t& i)	{ return FastReadUIntThrow(i); 	}
        inline void BasicReadType(std::int64_t& i)	{ return FastReadIntThrow(i);	}
        inline void BasicReadType(std::uint64_t& i)	{ return FastReadUIntThrow(i); 	}

        inline void BasicReadType(float& i)			{ return FastReadFloatThrow(i);	}
        inline void BasicReadType(double& i)		{ return FastReadFloatThrow(i);	}
        inline void BasicReadType(long double& i)	{ return FastReadFloatThrow(i);	}

        inline void BasicReadType(char& i)		{ i = Base::GetAndForward(); return; }
        inline void BasicReadType(wchar_t& i)	{ i = Base::GetAndForward(); return; }
        inline void BasicReadType(char16_t& i)	{ i = Base::GetAndForward(); return; }
        inline void BasicReadType(char32_t& i)	{ i = Base::GetAndForward(); return; }

        template<std::size_t SIZE> inline void BasicReadType([[maybe_unused]] char(&i)[SIZE])		{ /* TODO */ return; }
        template<std::size_t SIZE> inline void BasicReadType([[maybe_unused]] wchar_t(&i)[SIZE])	{ /* TODO */ return; }
        template<std::size_t SIZE> inline void BasicReadType([[maybe_unused]] char16_t(&i)[SIZE])	{ /* TODO */ return; }
        template<std::size_t SIZE> inline void BasicReadType([[maybe_unused]] char32_t(&i)[SIZE])	{ /* TODO */ return; }

        template<typename CharType> inline bool BasicReadType([[maybe_unused]] std::basic_string_view<CharType>& i) { /* TODO */ return true; }
    };
}

#include "Integer.h"
#include "String.h"
