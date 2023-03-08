#pragma once

#include "ProjectCore/FMT/Detail/Buffer/BasicBuffer.h"
#include "ProjectCore/FMT/Detail/Buffer/BufferOutManager/BasicBufferOutManager.h"

namespace ProjectCore::FMT::Detail {

	template <typename CharBuffer>
	class BasicBufferOut : public BasicBuffer<CharBuffer> {
	protected:
		using Base = BasicBuffer<CharBuffer>;
		using Base::m_Buffer;
		using Base::m_BufferEnd;
		using Base::m_BufferSize;
		using Base::m_CurrentPos;

	public:
		using typename Base::StringView;

	public:
		using Base::GetBuffer;
		using Base::GetBufferCurrentPos;
		using Base::GetBufferEnd;
		using Base::GetBufferSize;
		using Base::GetBufferCurrentSize;
		using Base::GetBufferRemainingSize;
		using Base::SetBufferCurrentPos;

		using Base::ReloadBuffer;
		using Base::SetBuffer;

	public:
		// using Base::CanMoveForward;
		// using Base::CanMoveForwardThrow;
		using Base::CanMoveBackward;
		using Base::CanMoveBackwardThrow;

		using Base::IsNotOutOfBound;
		using Base::IsNotOutOfBoundThrow;
		using Base::IsEnd;
		using Base::IsEndThrow;

		// using Base::Forward;
		using Base::ForwardNoCheck;
		// using Base::ForwardNoThrow;
		using Base::Backward;
		using Base::BackwardNoCheck;
		using Base::BackwardNoThrow;
		// using Base::Reserve;

		using Base::Get;
		// using Base::GetAndForward;
		using Base::GetAndForwardNoCheck;
		using Base::GetAndBackward;
		using Base::GetAndBackwardNoCheck;
		// using Base::GetNext;
		using Base::GetNextNoCheck;
		using Base::GetPrev;
		using Base::GetPrevNoCheck;

	public:
		static constexpr char			UPPER_HEX[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
		static constexpr char			LOWER_HEX[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	
	protected:
		BasicBufferOutManager<CharBuffer>* m_BufferOutManager;

	public:
		inline BasicBufferOutManager<CharBuffer>* GetBufferOutManagerPtr() 				{ return m_BufferOutManager; }
		inline const BasicBufferOutManager<CharBuffer>* GetBufferOutManagerPtr() const 	{ return m_BufferOutManager; }

		inline BasicBufferOutManager<CharBuffer>& GetBufferOutManager() 				{ return *m_BufferOutManager; }
		inline const BasicBufferOutManager<CharBuffer>& GetBufferOutManager() const 	{ return *m_BufferOutManager; }

	public:
		BasicBufferOut()
			: Base()
			, m_BufferOutManager(nullptr)
		{}

		BasicBufferOut(BasicBufferOutManager<CharBuffer>& bufferOutManager)
			: Base()
			, m_BufferOutManager(&bufferOutManager)
		{
			m_BufferOutManager->BeginContext();
			SetBuffer(m_BufferOutManager->GetBuffer(), m_BufferOutManager->GetBufferSize());
			SetBufferCurrentPos(m_BufferOutManager->GetBuffer());
		}

		~BasicBufferOut() override = default;

	public:
		void SetBufferOutManager(BasicBufferOutManager<CharBuffer>& bufferOutManager)
		{
			m_BufferOutManager = &bufferOutManager;
			if (m_BufferOutManager == nullptr)
				throw Detail::FMTShouldNotEndHere{};
				
			m_BufferOutManager->BeginContext();
			SetBuffer(m_BufferOutManager->GetBuffer(), m_BufferOutManager->GetBufferSize());
			SetBufferCurrentPos(m_BufferOutManager->GetBuffer());
		}


		void EndContext()
		{
			m_BufferOutManager->EndContext(GetBufferCurrentSize());
		}

	public:
		template<typename T> void FastWriteInt	(T i);
		template<typename T> void FastWriteUInt	(T i);
		template<typename T> void FastWriteFloat(T i, FloatPrecision floatPrecision = FloatPrecision{});

	public:
		// Basic types
		template<typename Type, typename ...Rest>
		inline void BasicWriteType(Type&& type, Rest&& ...rest) 	{ BasicWriteType(type); if (sizeof...(rest) > 0) BasicWriteType(std::forward<Rest>(rest)...); };
		
		template<typename T> void BasicWriteType(T i) 				{}

#if 0
		inline void BasicWriteType(const std::int8_t i)		{ FastWriteInt(i); }
		inline void BasicWriteType(const std::uint8_t i)	{ FastWriteUInt(i); }
		inline void BasicWriteType(const std::int16_t i)	{ FastWriteInt(i); }
		inline void BasicWriteType(const std::uint16_t i)	{ FastWriteUInt(i); }
		inline void BasicWriteType(const std::int32_t i)	{ FastWriteInt(i); }
		inline void BasicWriteType(const std::uint32_t i)	{ FastWriteUInt(i); }
		inline void BasicWriteType(const std::int64_t i)	{ FastWriteInt(i); }
		inline void BasicWriteType(const std::uint64_t i)	{ FastWriteUInt(i); }
#endif

		inline void BasicWriteType(const signed char i)			{ FastWriteInt(i); }
		inline void BasicWriteType(const unsigned char i)		{ FastWriteUInt(i); }
		inline void BasicWriteType(const short i)				{ FastWriteInt(i); }
		inline void BasicWriteType(const unsigned short i)		{ FastWriteUInt(i); }
		inline void BasicWriteType(const int i)					{ FastWriteInt(i); }
		inline void BasicWriteType(const unsigned int i)		{ FastWriteUInt(i); }
		inline void BasicWriteType(const long i)				{ FastWriteInt(i); }
		inline void BasicWriteType(const unsigned long i)		{ FastWriteUInt(i); }
		inline void BasicWriteType(const long long i)			{ FastWriteInt(i); }
		inline void BasicWriteType(const unsigned long long i)	{ FastWriteUInt(i); }

		inline void BasicWriteType(const float i)		{ FastWriteFloat(i); }
		inline void BasicWriteType(const double i)		{ FastWriteFloat(i); }
		inline void BasicWriteType(const long double i) { FastWriteFloat(i); }

		inline void BasicWriteType(const char i)		{ PushBack(i); }
		inline void BasicWriteType(const wchar_t i)		{ PushBack(i); }
		inline void BasicWriteType(const char16_t i)	{ PushBack(i); }
		inline void BasicWriteType(const char32_t i)	{ PushBack(i); }

		template<std::size_t SIZE> inline void BasicWriteType(const char (&i)[SIZE])		{ WriteCharArray(i); }
		template<std::size_t SIZE> inline void BasicWriteType(const wchar_t (&i)[SIZE])		{ WriteCharArray(i); }
		template<std::size_t SIZE> inline void BasicWriteType(const char16_t (&i)[SIZE])	{ WriteCharArray(i); }
		template<std::size_t SIZE> inline void BasicWriteType(const char32_t (&i)[SIZE])	{ WriteCharArray(i); }

		template<typename CharType> inline void BasicWriteType(const std::basic_string_view<CharType>& i) { WriteStringView(i); }

	public:
		bool AddSize(const std::size_t count)
		{
			if (m_BufferOutManager == nullptr)
				throw Detail::FMTShouldNotEndHere{};
			if (m_CurrentPos > m_BufferEnd)
				throw Detail::FMTBufferError{};
			std::size_t currentSize = GetBufferCurrentSize();
			if (m_BufferOutManager->AddSize(count) == false)
				return false;
			SetBuffer(m_BufferOutManager->GetBuffer(), m_BufferOutManager->GetBufferSize());
			SetBufferCurrentPos(m_BufferOutManager->GetBuffer() + currentSize);
			return true;
		}

		inline bool CanMoveForward()								{ if (m_CurrentPos + 1 <= m_BufferEnd)		return true; return AddSize(1); }
		inline bool CanMoveForward(const std::size_t count)			{ if (m_CurrentPos + count <= m_BufferEnd)	return true; return AddSize(count);}
		inline void CanMoveForwardThrow()							{ if (CanMoveForward())			return; throw FMTBufferFull{}; }
		inline void CanMoveForwardThrow(const std::size_t count)	{ if (CanMoveForward(count))	return; throw FMTBufferFull{}; }

		inline void Forward()										{ CanMoveForwardThrow(); ++m_CurrentPos; }
		inline void Forward(const std::size_t count)				{ CanMoveForwardThrow(count); m_CurrentPos += count; }
		inline void ForwardNoThrow()								{ if (CanMoveForward()) ++m_CurrentPos; }
		inline void ForwardNoThrow(const std::size_t count)			{ if (CanMoveForward(count)) m_CurrentPos += count; }
		inline CharBuffer GetAndForward()							{ CanMoveForwardThrow(); return *m_CurrentPos++; }
		inline CharBuffer GetNext()									{ CanMoveForwardThrow(); return *(m_CurrentPos + 1); }
		inline void Reserve(const std::size_t count)				{ Forward(count); Backward(); }

	public:
		inline void SetChar(const CharBuffer c)						{ *m_CurrentPos = c; }
		inline void PushBack(const CharBuffer c)					{ if (CanMoveForward()) *m_CurrentPos++ = c; }
		inline void PushReverse(const CharBuffer c)					{ if (CanMoveBackward()) *m_CurrentPos-- = c; }
		inline void PushBackNoCheck(const CharBuffer c)				{ *m_CurrentPos++ = c; }
		inline void PushReverseNoCheck(const CharBuffer c)			{ *m_CurrentPos-- = c; }
		inline void PushBack(const CharBuffer c, std::size_t count)			{ if (CanMoveForward(count)) 	while (count-- > 0) PushBackNoCheck(c); }
		inline void PushReverse(const CharBuffer c, std::size_t count)		{ if (CanMoveBackward(count)) 	while (count-- > 0) PushReverseNoCheck(c); }

		inline void PushBackEndChar()								{ PushBack('\0'); }
		inline void AddSpaces(const std::size_t count)				{ PushBack(' ', count); }

	protected:
		template<typename ...Rest>
		inline void PushBackSeqImpl(const CharBuffer c, const Rest... rest) 	{ PushBackNoCheck(c); if constexpr (sizeof...(rest) > 0) PushBackSeqImpl(rest...); }
	
	public:
		template<typename ...CharToPush>
		inline void PushBackSeq(const CharToPush... ele) 	{ if(CanMoveForward(sizeof...(ele))) return PushBackSeqImpl(ele...); }

		template<typename CharStr, std::size_t SIZE>	inline void WriteCharArray(const CharStr(&str)[SIZE])					{ WriteCharPtr(str, SIZE); }
		template<typename CharStr>						inline void WriteStringView(const std::basic_string_view<CharStr>& str)	{ WriteCharPtr(str.data(), str.size()); }
		template<typename CharStr>						inline void WriteCharPtr(const CharStr* str)							{ while (*str != 0) PushBack(*str++); }
		
		template<typename CharStr>
		inline void WriteCharPtr(const CharStr* str, std::size_t size) {
			if (CanMoveForward(size) == false)
				return WriteCharPtr(str, GetBufferRemainingSize());

			while (size-- != 0 && *str != 0)
				PushBackNoCheck(*str++);
		}

		template<typename CharStr>
		inline void Append(const CharStr* begin, const CharStr* end) {
			if (CanMoveForward(end - begin) == false)
				return WriteCharPtr(begin, GetBufferRemainingSize());

			while (*begin != 0 && begin < end)
				PushBackNoCheck(*begin++);
		}

	protected:
		template<typename T>
		static inline DataType GetNumberOfDigitDec(T value) {
			if constexpr (std::numeric_limits<T>::is_signed) {
				if (value < 0)	value = -value;
			}
			DataType nb = 0;
			while(true) {
				if (value < 10)
					return nb + 1;
				else if(value < 100)
					return nb + 2;
				else if (value < 1000)
					return nb + 3;
				else if (value < 10000)
					return nb + 4;
				else {
					value /= (T)10000;
					nb += 4;
				}
			}
		}
	};
}

#include "Integer.h"
