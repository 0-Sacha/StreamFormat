#pragma once

#include "FormatType.h"

namespace EngineCore::FMT {
	template<typename T, typename FormatContext>
	struct FCIndexArgs {

		FCIndexArgs(const std::uint8_t idx, const T& t)
			: m_Value(t), m_Idx(idx) {}

	public:
		inline bool IsRightIdx(std::uint8_t idx) const { return idx == m_Idx; }

	public:
		inline const T& GetValue() const { return m_Value; }

	protected:
		const T& m_Value;
		const std::uint8_t m_Idx;
	};

	template<typename T, typename FormatContext>
	struct FormatType<FCIndexArgs<T, FormatContext>, FormatContext>
	{
		template<typename Char>
		inline static void Write(const FCIndexArgs<T, FormatContext>& t, FormatContext& context) {
			context.RunType(t.GetValue());
		}
	};
}