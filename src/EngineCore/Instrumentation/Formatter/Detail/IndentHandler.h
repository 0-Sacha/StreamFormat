#pragma once

#include "EngineCore/Instrumentation/Formatter/Detail/Detail.h"

namespace EngineCore::FMT::Detail {
	template<typename T, typename CharFormat>	struct CopyFormatData										{ static void Copy(FormatData<CharFormat>& data, const T& t) { } };
	template<typename CharFormat>				struct CopyFormatData<FormatData<CharFormat>, CharFormat>	{ static void Copy(FormatData<CharFormat>& data, const FormatData<CharFormat>& t) { data = t; } };
	
	template <typename BufferContext>
	struct NoStrideFunction {
		inline explicit NoStrideFunction(BufferContext& buffer)
			: Buffer(buffer)
			, SizeBuffer(Buffer.GetBufferCurrentSize()) {}

		~NoStrideFunction() {
			Buffer.AddNoStride(Buffer.GetBufferCurrentSize() - SizeBuffer);
		}

		BufferContext&	Buffer;
		std::size_t		SizeBuffer;
	};

	template <typename Char>
	struct GetIndentInfo {
		inline GetIndentInfo()
			: Restore(true)
			, AddIndent(0)
		{}

		inline explicit GetIndentInfo(const std::basic_string_view<Char>& txt)
			: Restore(false)
			, AddIndent(txt.size())
		{
			for (std::size_t k = 0; k < txt.size(); ++k)
			{
				if (txt[k] == '\n')
				{
					Restore = true;
					AddIndent = txt.size() - k - 1;
				}
			}
		}

		bool 		Restore;
		std::size_t AddIndent;
	};

	template <typename FormatContext>
	struct RestoreIndentFunction {
		inline explicit RestoreIndentFunction(FormatContext& context)
			: Context(context)
			, OldIndent(context.GetIndent())
			, GetIndentInfo()
			, AddIndentEnd(false)
		{}

		template <typename Char>
		inline RestoreIndentFunction(FormatContext& context, const std::basic_string_view<Char>& txt, bool addIndentEnd = true)
			: Context(context)
			, OldIndent(context.BufferOut().GetIndent())
			, GetIndentInfo(txt)
			, AddIndentEnd(addIndentEnd)
		{}

		~RestoreIndentFunction() {
			if (GetIndentInfo.Restore)
				Context.BufferOut().SetIndent(OldIndent);
			if (AddIndentEnd)
				Context.BufferOut().AddIndent(GetIndentInfo.AddIndent);
		}

		FormatContext&											Context;
		std::size_t 											OldIndent;
		GetIndentInfo<typename FormatContext::CharFormatType> 	GetIndentInfo;
		bool 													AddIndentEnd;
	};

	template <typename FormatContext>
	struct GetIndentFunction {
		inline explicit GetIndentFunction(FormatContext& context)
			: Context(context)
			, OldNoStride(context.BufferOut().GetNoStride())
			, OldBufferSize(context.BufferOut().GetBufferCurrentSize())
		{}

		inline std::size_t GetIndent()
		{
			return (Context.BufferOut().GetBufferCurrentSize() - OldBufferSize) - (Context.BufferOut().GetNoStride() - OldNoStride);
		}

		FormatContext&	Context;
		std::size_t 	OldNoStride;
		std::size_t 	OldBufferSize;
	};
	
	template <typename FormatContext>
	struct IndentFunction {
		explicit inline IndentFunction(FormatContext& context)
			: GetIndentFunction(context)
		{}

		~IndentFunction() {
			GetIndentFunction.Context.AddIndent(GetIndentFunction.GetIndent());
		}

		GetIndentFunction<FormatContext>	GetIndentFunction;
	};
}