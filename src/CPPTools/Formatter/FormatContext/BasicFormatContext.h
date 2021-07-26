#pragma once

#include "CPPTools/Formatter/Core/Detail.h"

#include "BaseFormat/FormatType.h"
#include "BaseFormat/NamedArgs.h"
#include "BaseFormat/FormatArgs.h"
#include "BaseFormat/STDEnumerable.h"

#include "FormatContextArgsTuple.h"

#include "../Core/FormatterHandler.h"

namespace CPPTools::Fmt {
	template<typename CharFormat = char, typename CharBuffer = CharFormat, typename ...ContextArgs>
	class BasicFormatContext {
	public:
		BasicFormatContext(const std::basic_string_view<CharFormat> format, CharBuffer *const buffer, const std::size_t bufferSize, ContextArgs &&...args);

		template <typename OldCharFormat, typename... OldContextArgs>
		BasicFormatContext(const std::basic_string_view<CharFormat> format, BasicFormatContext<OldCharFormat, CharBuffer, OldContextArgs...> &oldContext, ContextArgs &&...args);

		template<typename OldCharFormat, typename ...OldContextArgs>
		inline void UpdateOldContext(BasicFormatContext<OldCharFormat, CharBuffer, OldContextArgs...>& oldContext) { oldContext.SetSubBuffer(m_SubBuffer); }

	private:
		// Buffer
		CharBuffer* const	m_Buffer;
		CharBuffer*			m_SubBuffer;
		CharBuffer* const	m_BufferEnd;	// Point one behind the end char
		std::size_t			m_BufferSize;	// The real allocated size

		// Format
		const CharFormat*	m_Format;				
		const CharFormat*	m_SubFormat;
		const CharFormat*	m_FormatEnd;			// Point to the end char of the format
		std::size_t			m_FormatSize;			// Do not count the end char

		// Args
		Detail::FormatContextArgsTuple<ContextArgs...> 	m_ContextArgs;
		std::size_t					 					m_ContextArgsSize;

		// Stride (mostly for container and new line format-style)
		std::size_t 			m_NoStride;

		// For handling color / format data and idx (for not specified parameter)
		FormatIdx				m_ValuesIdx;
		FormatData				m_FormatData;
		Detail::AnsiColorMem	m_ColorMem;

	public:
		inline CharBuffer*			GetBuffer()								{ return m_Buffer; }
		inline const CharBuffer*	GetBuffer() const						{ return m_Buffer; }
		inline CharBuffer*			GetSubBuffer()							{ return m_SubBuffer; }
		inline const CharBuffer*	GetSubBuffer() const					{ return m_SubBuffer; }
		inline CharBuffer*			GetBufferEnd() 							{ return m_BufferEnd; }
		inline const CharBuffer*	GetBufferEnd() const					{ return m_BufferEnd; }
		inline std::size_t			GetBufferSize() const					{ return m_BufferSize; }
		inline std::size_t			GetCurrentBufferSize() const			{ return m_SubBuffer - m_Buffer; }
		inline void					SetSubBuffer(CharBuffer* const pos)		{ m_SubBuffer = pos; }

		inline const CharFormat*	GetFormat() const						{ return m_Format; }
		inline const CharFormat*	GetSubFormat() const					{ return m_SubFormat; }
		inline const CharFormat*	GetFormatEnd() const					{ return m_FormatEnd; }
		inline std::size_t			GetFormatSize() const					{ return m_FormatSize; }
		inline std::size_t			GetCurrentFormatSize() const			{ return m_SubFormat - m_Format; }
		inline void					SetSubFormat(CharFormat* const pos)		{ m_SubFormat = pos; }

		inline Detail::AnsiColorMem& GetColorMem()				{ return m_ColorMem; }
		inline const Detail::AnsiColorMem& GetColorMem() const	{ return m_ColorMem; }
		inline FormatData& GetFormatData()						{ return m_FormatData; }
		inline const FormatData& GetFormatData() const			{ return m_FormatData; }
		inline FormatData ForwardFormatData() const				{ return m_FormatData; }

		inline void AddNoStride(const std::size_t noStride)		{ m_NoStride += noStride; }
		inline std::size_t GetNoStride() const					{ return m_NoStride; }
		inline std::size_t GetStride() const					{ return GetCurrentBufferSize() - m_NoStride; }

	public:
		inline static FormatterHandler& GetAPI()					{ return FormatterHandler::GetInstance(); }

	private:
		/////---------- Impl ----------/////
		bool GetFormatIdx(FormatIdx& idx);
		bool ParameterPrint();
		void ParameterData();

	public:
		void Format();
		void MainFormat();

		template<typename NewCharFormat, typename ...NewContextArgs>
		void LittleFormat(const std::basic_string_view<NewCharFormat> format, NewContextArgs&& ...args);
		template<typename CharType, std::size_t SIZE, typename ...NewContextArgs>
		inline void LittleFormat(const CharType (&format)[SIZE], NewContextArgs&& ...args)				{ LittleFormat(std::basic_string_view<CharType>(format), std::forward<NewContextArgs>(args)...); }

	private:
		template<typename CharList, std::size_t SIZE>
		std::size_t GetWordFromList(const std::basic_string_view<CharList> (&formatTypes)[SIZE]);

		void CheckEndStr();
		void ColorValuePrint();
		std::uint8_t GetColorCode();
		std::uint8_t GetColorFG();
		std::uint8_t GetColorBG();
		void TimerValuePrint();
		void DateValuePrint();
		void ReloadColor();

	public:
		// Integer
		template<typename T> bool FormatReadInt(T& i);
		template<typename T> bool FormatReadUInt(T& i);

		// unsigned Integer
		template<typename T> bool FormatReadParameter(T& i);

	public:
		// Integer
		template<typename T> void BufferWriteInt(T i);
		template<typename T> void BufferWriteUInt(T i);

		// Floating point
		template<typename T> void BufferWriteFloat(T i);

		// C-Style String / Char pointer
		template<typename CharStr>						inline void BufferWriteCharPt(const CharStr* str);
		template<typename CharStr>						inline void BufferWriteCharPt(const CharStr* str, std::size_t size);

		// String Literal / Char array - wrapper
		template<typename CharStr, std::size_t SIZE>	inline void BufferWriteCharArray(const CharStr(&str)[SIZE]) { BufferWriteCharPt(str, SIZE); }
		template<typename CharStr, std::size_t SIZE>	inline void Print(const CharStr(&str)[SIZE])				{ BufferWriteCharPt(str, SIZE); }

		// C++-Style String (string-view) - wrapper
		template<typename CharStr>						inline void BufferWriteStringView(const std::basic_string_view<CharStr> str)	{ BufferWriteCharPt(str.data(), str.size()); }
		template<typename CharStr>						inline void Print(const std::basic_string_view<CharStr> str)					{ BufferWriteCharPt(str.data(), str.size()); }

		// Type formating from FormatType<>
		template<typename Type>							inline void WriteType(Type&& type) { FormatType<Detail::GetBaseType<Type>, BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>>::Write(type, *this); }

	public:
		// Format
		inline bool FormatCanMoveForward() const									{ return m_SubFormat < m_FormatEnd; }
		inline bool FormatCanMoveBackward() const									{ return m_SubFormat > m_Format; }
		inline bool FormatCanMoveForward(const std::size_t count) const				{ return m_SubFormat + count <= m_FormatEnd; }
		inline bool FormatCanMoveBackward(const std::size_t count) const			{ return m_SubFormat + count >= m_Format; }
		inline bool FormatIsNotOutOfBound() const									{ return !FormatCanMoveForward() || !FormatCanMoveBackward(); }
		inline bool FormatEnd() const												{ return m_SubFormat >= m_FormatEnd; }

		// Format base commands
		inline void FormatForward()													{ if (FormatCanMoveForward()) ++m_SubFormat; }
		inline void FormatForwardNoCheck()											{ ++m_SubFormat; }
		inline void FormatBackward()												{ if (FormatCanMoveBackward()) --m_SubFormat; }
		inline void FormatBackwardNoCheck()											{ --m_SubFormat; }
		template<typename Int> inline void FormatForward(const Int size)			{ m_SubFormat += size; if (!FormatCanMoveForward()) m_SubFormat = m_FormatEnd; }
		template<typename Int> inline void FormatBackward(const Int size)			{ m_SubFormat -= size; if (!FormatCanMoveBackward()) m_SubFormat = m_Format; }
		
		inline CharFormat FormatGet() const											{ return *m_SubFormat; }
		inline CharFormat FormatGetAndForward()										{ return FormatCanMoveForward() ? *m_SubFormat++ : '\0'; }
		inline CharFormat FormatGetAndForwardNoCheck()								{ return *m_SubFormat++; }
		inline CharFormat FormatGetAndBackward()									{ return FormatCanMoveBackward() ? *m_SubFormat-- : '\0'; }
		inline CharFormat FormatGetAndBackwardNoCheck()								{ return *m_SubFormat--; }
		inline CharFormat FormatGetNext() const										{ return FormatCanMoveForward() ? *(m_SubFormat + 1) : '\0'; }
		inline CharFormat FormatGetNextNoCheck() const								{ return *(m_SubFormat + 1); }

		// Format check
		inline bool FormatIsEqualTo(const CharFormat c) const						{ return FormatGet() == c; }
		inline bool FormatIsNotEqualTo(const CharFormat c) const					{ return FormatGet() != c; }
		inline bool FormatIsEqualForward(const CharFormat c)						{ if (FormatIsEqualTo(c)) { FormatForward(); return true; } return false; }
		inline bool FormatIsNotEqualForward(const CharFormat c)						{ if (FormatIsNotEqualTo(c)) { FormatForward(); return true; } return false; }
		template<typename ...CharToTest> inline bool FormatIsEqualTo(const CharFormat c, const CharToTest ...ele) const		{ return FormatIsEqualTo(c) || FormatIsEqualTo(ele...); }
		template<typename ...CharToTest> inline bool FormatIsEqualForward(const CharToTest ...ele) const					{ if (FormatIsEqualTo(ele...)) { FormatForward(); return true; } return false; }
		template<typename ...CharToTest> inline bool FormatIsNotEqualTo(const CharFormat c, const CharToTest ...ele) const	{ return FormatIsNotEqualTo(c) && FormatIsNotEqualTo(ele...); }
		template<typename ...CharToTest> inline bool FormatIsNotEqualForward(const CharToTest ...ele) const					{ if (FormatIsNotEqualTo(ele...)) { FormatForward(); return true; } return false; }

		template<typename CharToTest> 	bool FormatNextIsANamedArgs(std::basic_string_view<CharToTest> sv);

		// Format Next check
		inline bool FormatNextIsEqualTo(const CharFormat c) const					{ return FormatGetNext() == c; }
		inline bool FormatNextIsNotEqualTo(const CharFormat c) const				{ return FormatGetNext() != c; }
		inline bool FormatNextIsEqualForward(const CharFormat c)					{ FormatForward(); if(!FormatIsEqualTo(c)) { FormatBackwardNoCheck(); return false; } return true; }
		inline bool FormatNextIsNotEqualForward(const CharFormat c)					{ FormatForward(); if (!FormatIsNotEqualTo(c)) { FormatBackwardNoCheck(); return false; } return true; }
		template<typename ...CharToTest> inline bool FormatNextIsEqualForward(const CharToTest ...ele)		{ FormatForward(); if (FormatIsEqualTo(ele...)) { return true; } FormatBackwardNoCheck(); return false; }
		template<typename ...CharToTest> inline bool FormatNextIsEqualTo(const CharToTest ...ele) const		{ FormatForward(); if (FormatIsEqualTo(ele...)) { FormatBackwardNoCheck(); return true; } FormatBackwardNoCheck(); return false; }
		template<typename ...CharToTest> inline bool FormatNextIsNotEqualForward(const CharToTest ...ele)	{ FormatForward(); if (FormatIsNotEqualTo(ele...)) { return true; } FormatBackwardNoCheck(); return false; }
		template<typename ...CharToTest> inline bool FormatNextIsNotEqualTo(const CharToTest ...ele) const	{ FormatForward(); if (FormatIsNotEqualTo(ele...)) { FormatBackwardNoCheck(); return true; } FormatBackwardNoCheck(); return false; }

		template<typename CharToTest>
		bool FormatNextIsSame(std::basic_string_view<CharToTest> sv);
		template<std::size_t SIZE, typename CharToTest>
		inline bool FormatNextIsSame(const CharToTest(&data)[SIZE])					{ return FormatNextIsSame(std::basic_string_view<CharToTest>(data)); }

		inline bool FormatIsLowerCase() const										{ return FormatGet() >= 'a' && FormatGet() <= 'z'; }
		inline bool FormatIsUpperCase() const										{ return FormatGet() >= 'A' && FormatGet() <= 'Z'; }
		inline bool FormatIsADigit() const											{ return FormatGet() >= '0' && FormatGet() <= '9'; }

		// Format commands
		inline void FormatIgnoreSpace()												{ while (FormatIsEqualTo(' ') && FormatCanMoveForward()) FormatForwardNoCheck(); }
		template<typename ...CharToTest> inline void FormatGoTo(const CharToTest ...ele)				{ while (FormatIsNotEqualTo(ele...) && FormatCanMoveForward())	FormatForwardNoCheck(); }
		template<typename ...CharToTest> inline void FormatGoToForward(const CharToTest ...ele)			{ while (FormatIsNotEqualTo(ele...) && FormatCanMoveForward())	FormatForwardNoCheck();	FormatForward(); }
	
		// Format commands in parameter (add check to '}' to avoid skip the end of the format specifier)
		template<typename ...CharToTest> inline void FormatParamGoTo(const CharToTest ...ele)			{ while (FormatIsNotEqualTo(ele..., '}') && FormatCanMoveForward())	FormatForwardNoCheck(); }
		template<typename ...CharToTest> inline void FormatParamGoToForward(const CharToTest ...ele)	{ while (FormatIsNotEqualTo(ele..., '}') && FormatCanMoveForward())	FormatForwardNoCheck();	FormatForward(); }

	public:
		// Buffer
		inline bool BufferCanMoveForward() const									{ return m_SubBuffer < m_BufferEnd; }
		inline bool BufferCanMoveBackward() const									{ return m_SubBuffer > m_Buffer; }
		inline bool BufferCanMoveForward(const std::size_t count) const				{ return m_SubBuffer + count <= m_BufferEnd; }
		inline bool BufferCanMoveBackward(const std::size_t count) const			{ return m_SubBuffer + count >= m_Buffer; }
		inline bool BufferIsNotOutOfBound() const									{ return !BufferCanMoveForward() || !BufferCanMoveBackward(); }

		// Buffer base commands
		inline void BufferForward()													{ if (BufferCanMoveForward()) ++m_SubBuffer; }
		inline void BufferForwardNoCheck()											{ ++m_SubBuffer; }
		inline void BufferBackward()												{ if (BufferCanMoveBackward()) --m_SubBuffer; }
		template<typename Int> inline void BufferForward(const Int size)			{ m_SubBuffer += size; if (!BufferCanMoveForward()) m_SubBuffer = m_BufferEnd; }
		template<typename Int> inline void BufferBackward(const Int size)			{ m_SubBuffer -= size; if (!BufferCanMoveBackward()) m_SubBuffer = m_Buffer; }

		inline CharBuffer BufferGet() const											{ return *m_SubBuffer; }
		inline CharBuffer BufferGetAndForward()										{ return BufferCanMoveForward() ? *m_SubBuffer++ : '\0'; }
		inline CharBuffer BufferGetAndForwardNoCheck()								{ return *m_SubBuffer++; }
		inline CharBuffer BufferGetAndBackward()									{ return BufferCanMoveBackward() ? *m_SubBuffer-- : '\0'; }
		inline CharBuffer BufferGetNext() const										{ return BufferCanMoveForward() ? *(m_SubBuffer + 1) : '\0'; }

		inline void BufferSet(const CharBuffer c)									{ *m_SubBuffer = c; }
		inline void BufferPushBack(const CharBuffer c)								{ if (BufferCanMoveForward()) *m_SubBuffer++ = c; }
		inline void BufferPushReverse(const CharBuffer c)							{ if (BufferCanMoveBackward()) *m_SubBuffer-- = c; }
		inline void BufferPushBackNoCheck(const CharBuffer c)						{ *m_SubBuffer++ = c; }
		inline void BufferPushReverseNoCheck(const CharBuffer c)					{ *m_SubBuffer-- = c; }

		// Buffer commands
		inline void BufferPushEndChar()												{ BufferPushBack('\0'); }
		inline void BufferAddSpaces(const std::size_t count)						{ for (std::size_t i = count; i > 0 && BufferCanMoveForward(); --i) BufferPushBackNoCheck(' '); }

	public:
		// Format check for param
		inline bool FormatIsEndOfParameter()										{ return FormatIsEqualTo('}'); }
		inline void FormatGoToEndOfParameter()										{ while (FormatIsNotEqualTo('}') && FormatCanMoveForward()) FormatForwardNoCheck(); }
		inline void FormatGoOutOfParameter()										{ while (FormatIsNotEqualTo('}') && FormatCanMoveForward()) FormatForwardNoCheck(); FormatForward(); }

		inline void CopyFormatToBuffer()											{ BufferPushBack(FormatGetAndForward()); }

		template<typename ...CharToTest> inline void WriteUntilNextParameter(const CharToTest ...ele) 	{ while (FormatIsNotEqualTo('{', ele...) && FormatCanMoveForward())	CopyFormatToBuffer(); }
		template<typename ...CharToTest> inline void WriteUntilEndOfParameter(const CharToTest ...ele)	{ while (FormatIsNotEqualTo('}', ele...) && FormatCanMoveForward())	CopyFormatToBuffer(); }
	};
}