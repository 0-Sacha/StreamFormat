#pragma once

#include "EngineCore/FMT/Detail/Detail.h"

namespace EngineCore::FMT::Detail {

    template <typename CharType>
    class BasicBufferManager
    {
	protected:
		virtual void BeginContextImpl() {}
		virtual void EndContextImpl(std::size_t totalGeneratedLength) {}

	public:
		void BeginContext() { BeginContextImpl(); }
		void EndContext(std::size_t totalGeneratedLength) { EndContextImpl(totalGeneratedLength); SetLastGeneratedDataSize(totalGeneratedLength); }

	public:
		virtual CharType* GetBuffer() = 0;
		virtual const CharType* GetBuffer() const = 0;
		virtual std::size_t GetBufferSize() const = 0;

	public:
		virtual bool AddSize(const std::size_t count) = 0;

	public:
		std::basic_string_view<CharType> GetLastGeneratedStringView() const { return std::basic_string_view<CharType>(GetBuffer(), m_LastGeneratedDataSize); }
		operator std::basic_string_view<CharType>() const 					{ return GetLastGeneratedStringView(); }
		std::basic_string<CharType> GetLastGeneratedString() const 			{ return std::basic_string<CharType>(GetBuffer(), m_LastGeneratedDataSize); }
		operator std::basic_string<CharType>() const 						{ return GetLastGeneratedString(); }

	public:
		std::size_t GetLastGeneratedDataSize() const { return m_LastGeneratedDataSize; }

	private:
		void SetLastGeneratedDataSize(const std::size_t size) { m_LastGeneratedDataSize = size; }

	protected:
		std::size_t m_LastGeneratedDataSize;
    };

}
