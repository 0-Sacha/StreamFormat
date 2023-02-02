#pragma once

#include "BasicBufferManager.h"

namespace EngineCore::FMT::Detail {

    template <typename CharType>
    class DynamicBufferManager : public BasicBufferManager<CharType>
    {
    public:
		DynamicBufferManager(std::size_t beginSize = DEFAULT_BEGIN_SIZE)
		{
			m_Buffer = new CharType[beginSize];
			m_BufferSize = beginSize;
		}

		~DynamicBufferManager()
		{
			delete[] m_Buffer;
		}

    public:
		static constexpr std::size_t	DEFAULT_BEGIN_SIZE	= 128;
		static constexpr std::size_t	GROW_UP_BUFFER_SIZE = 2;
		static constexpr bool			DEBUG_RESIZE		= true;

    public:
		void BeginContext() {}
		void EndContext() {}

	public:
		CharType* GetBuffer() override { return m_Buffer; }
		const CharType* GetBuffer() const override { return m_Buffer; }
		std::size_t GetBufferSize() const override { return m_BufferSize; }
	
	public:
		bool Resize(const std::size_t count) override;

	private:
		CharType* m_Buffer;
		std::size_t m_BufferSize;
    };

	template <typename CharType>
	bool DynamicBufferManager<CharType>::Resize(const std::size_t count) {
		const std::size_t targetBufferSize = count + m_BufferSize;
		std::size_t newBufferSize = m_BufferSize;
		
		while(newBufferSize < targetBufferSize)
			newBufferSize *= GROW_UP_BUFFER_SIZE;

		CharType* safeBuffer = new CharType[newBufferSize];
		if (safeBuffer == nullptr) return false;

		std::memcpy(safeBuffer, m_Buffer, m_BufferSize);

		if constexpr (DEBUG_RESIZE)
			std::cout << "Resize from " << m_BufferSize << " to " << newBufferSize << std::endl;

		delete[] m_Buffer;
		m_Buffer = safeBuffer;
		m_BufferSize = newBufferSize;

		return true;
	}

}
