#pragma once

#include "BasicBufferManager.h"

#include <memory>
#include <iostream>

namespace EngineCore::FMT::Detail {

    template <typename CharType>
    class DynamicBufferManager : public BasicBufferManager<CharType>
    {
    public:
		DynamicBufferManager(std::size_t beginSize = DEFAULT_BEGIN_SIZE)
		{
			m_Buffer.reset(new CharType[beginSize]);
			m_BufferSize = beginSize;
		}

    public:
		static constexpr std::size_t	DEFAULT_BEGIN_SIZE	= 128;
		static constexpr std::size_t	GROW_UP_BUFFER_SIZE = 2;
		static constexpr bool			DEBUG_RESIZE		= false;

	public:
		CharType* GetBuffer() override { return m_Buffer.get(); }
		const CharType* GetBuffer() const override { return m_Buffer.get(); }
		std::size_t GetBufferSize() const override { return m_BufferSize; }
	
	public:
		bool AddSize(const std::size_t count) override { return Resize(count + m_BufferSize); }
		bool Resize(const std::size_t targetBufferSize);

	protected:
		std::unique_ptr<CharType[]> m_Buffer;
		std::size_t m_BufferSize;
    };

	template <typename CharType>
    class ShrinkDynamicBufferManager : public DynamicBufferManager<CharType>
	{
		public:
			using Base = DynamicBufferManager<CharType>;
			using Base::DEFAULT_BEGIN_SIZE;
			using Base::GROW_UP_BUFFER_SIZE;
			using Base::DEBUG_RESIZE;

			using Base::GetBuffer;
			using Base::GetBufferSize;
			using Base::Resize;

			using Base::m_Buffer;
			using Base::m_BufferSize;

			static constexpr float MEAN_SIZE_OVERFLOW = 4.2;
			static constexpr float MEAN_SIZE_RESIZE = 1.4;

			static constexpr float MEAN_CALCFACT_OLD = 5;
			static constexpr float MEAN_CALCFACT_LAST = 1;

		public:
			ShrinkDynamicBufferManager(std::size_t beginSize = DEFAULT_BEGIN_SIZE)
				: Base(beginSize)
				, m_MeanGeneratedSize(beginSize)
			{}
			
			~ShrinkDynamicBufferManager()
			{}

		public:
			void BeginContextImpl() override { ShrinkIfNeeded(); }
			void EndContextImpl(std::size_t totalGeneratedLength) override
			{ m_MeanGeneratedSize = (m_MeanGeneratedSize * MEAN_CALCFACT_OLD + totalGeneratedLength * MEAN_CALCFACT_LAST) / (MEAN_CALCFACT_OLD + MEAN_CALCFACT_LAST); }
			
			void ShrinkIfNeeded()
			{
				if (m_BufferSize > static_cast<std::size_t>(m_MeanGeneratedSize * MEAN_SIZE_OVERFLOW))
					Resize(static_cast<std::size_t>(m_MeanGeneratedSize * MEAN_SIZE_RESIZE));
			}

		private:
			std::size_t m_MeanGeneratedSize;
	};

	template <typename CharType>
	bool DynamicBufferManager<CharType>::Resize(const std::size_t targetBufferSize) {
		std::size_t newBufferSize = targetBufferSize;
		
		if (m_BufferSize < targetBufferSize)
		{
			newBufferSize = m_BufferSize;
			while(newBufferSize < targetBufferSize)
				newBufferSize *= GROW_UP_BUFFER_SIZE;
		}

		CharType* safeBuffer = new CharType[newBufferSize];
		if (safeBuffer == nullptr) return false;

		std::memcpy(safeBuffer, m_Buffer.get(), std::min(newBufferSize, m_BufferSize));

		if constexpr (DEBUG_RESIZE)
			std::cout << "Resize from " << m_BufferSize << " to " << newBufferSize << std::endl;

		m_Buffer.reset(safeBuffer);
		m_BufferSize = newBufferSize;

		return true;
	}

}
