#pragma once

#include "BasicBufferManager.h"

#include <string>

namespace EngineCore::FMT::Detail {

    template <typename CharType>
    class STDStringBufferManager : public BasicBufferManager<CharType>
    {
    public:
		STDStringBufferManager(std::size_t beginSize = DEFAULT_BEGIN_SIZE)
		{
			m_Buffer.reserve(beginSize);
		}

    public:
		static constexpr std::size_t	DEFAULT_BEGIN_SIZE	= 128;
		static constexpr std::size_t	GROW_UP_BUFFER_SIZE = 2;
		static constexpr bool			DEBUG_RESIZE		= false;

	public:
		CharType* GetBuffer() override { return m_Buffer.data(); }
		const CharType* GetBuffer() const override { return m_Buffer.data(); }
		std::size_t GetBufferSize() const override { return m_Buffer.size(); }
	
		std::basic_string<CharType>& GetSTDString() { return m_Buffer; }
		const std::basic_string<CharType>& GetSTDString() const { return m_Buffer; }

	public:
		bool AddSize(const std::size_t count) override
		{
			std::size_t newBufferSize = m_Buffer.size();
			while (newBufferSize < m_Buffer.size() + count)
				newBufferSize *= GROW_UP_BUFFER_SIZE;

			try
			{
				m_Buffer.reserve(newBufferSize);
			}
			catch(std::bad_alloc& e)
			{
				return false;
			}
			return true;
		}

	protected:
		std::basic_string<CharType> m_Buffer;
    };
}
