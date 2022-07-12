
#pragma once

#include "../BasicContext/BasicContextInclude.h"

#include "Utils/UnFormatType.h"

#include "UnFormatContextArgsTuple.h"

namespace EngineCore::FMT::Context {

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	class BasicUnFormatContext : public BasicContext<CharFormat, int, BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>>
	{
	public:
		using Base = BasicContext<CharFormat, int, BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>>;
		using M_Type = BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>;

		friend Base;

		using typename Base::CharFormatType;
		using typename Base::FormatDataType;
		using typename Base::StringViewFormat;
		using typename Base::FormatBufferType;

		using CharBufferType	= CharBuffer;
		using StringViewBuffer	= std::basic_string_view<CharBuffer>;
		using BufferInType		= Detail::BasicFormatterMemoryBufferIn<CharBuffer>;
		using ContextArgsType	= Detail::UnFormatContextArgsTuple<ContextArgs...>;

	public:
		BasicUnFormatContext(const std::basic_string_view<CharFormat>& format, const std::basic_string_view<CharBuffer>& buffer, ContextArgs&& ...args);

		// Used for LittleFormat
		template<typename ParentCharFormat, typename ...ParentContextArgs>
		BasicUnFormatContext(const std::basic_string_view<CharFormat>& format, BasicUnFormatContext<ParentCharFormat, CharBuffer, ParentContextArgs...>& parentContext, ContextArgs &&...args);

		~BasicUnFormatContext();

	protected:
		using Base::m_Format;
		using Base::m_ValuesIndex;
		using Base::m_FormatData;

		BufferInType 		m_BufferIn;
		ContextArgsType 	m_ContextArgs;

	public:
		using Base::Format;
		using Base::GetFormatData;
		using Base::ForwardFormatData;
		using Base::GetAPI;

		inline BufferInType& BufferIn()					{ return m_BufferIn; }
		inline const BufferInType& BufferIn() const		{ return m_BufferIn; }

	public:
		using Base::SafeRun;
		using Base::LittleFormat;

		void Run();

		template<typename NewCharFormat, typename ...NewContextArgs>
		void LittleUnFormat(const std::basic_string_view<NewCharFormat>& format, NewContextArgs&& ...args);

	public:
		using Base::GetFormatIndexThrow;

	public:
		// TupleInterface
		using Base::GetTypeAtIndexThrow;
		using Base::GetTypeAtIndexConvertThrow;
		using Base::GetIndexOfCurrentNameArg;
		using Base::RunTypeAtIndex;

		void RunTypeAtIndex(const Detail::FormatIndex& index)	{ m_ContextArgs.RunTypeAtIndex(*this, index); }
		Detail::FormatIndex GetIndexOfCurrentNameArg()			{ return m_ContextArgs.GetIndexOfCurrentNameArg(*this, Detail::FormatIndex(0, m_ValuesIndex.MaxValue)); }

		template <typename T>
		const Detail::GetBaseType<T>* GetTypeAtIndex(const Detail::FormatIndex& index) { return m_ContextArgs.template GetTypeAtIndexThrow<T>(*this, index); }

		template <typename T>
		T GetTypeAtIndexConvertThrow(const Detail::FormatIndex& index) {
			return m_ContextArgs.template GetTypeAtIndexConvertThrow<T>(*this, index);
		}

		template <typename T>
		bool RunFuncFromTypeAtIndex(const Detail::FormatIndex& index, std::function<void(const T&)> func)
		{
			const T* value = m_ContextArgs.template GetTypeAtIndexThrow<T>(*this, index);
			if (value != nullptr)
			{
				func(*value);
				return true;
			}
			return false;
		}

	protected:
		using Base::ParseFormatDataBase;
		using Base::ParseFormatDataSpecial;
		using Base::ParseFormatDataCustom;
		using Base::ParseFormatData;

		using Base::ParseFormatDataColor;
		using Base::ParseFormatDataStyle;
		using Base::ParseFormatDataFront;
		using Base::ContextStyleSave;
		using Base::ContextStyleRestore;

		using Base::ParseSpecial;
		using Base::ParseVariable;
		using Base::Parse;


		void ParseFormatDataColor() {}
		void ParseFormatDataStyle() {}
		void ParseFormatDataFront() {}

		int ContextStyleSave()						{ return 0; }
		void ContextStyleRestore(const int& data)	{ }

	protected:
		using Base::ParseTimer;
		using Base::ParseDate;

		using Base::ParseColor;
		using Base::ParseStyle;
		using Base::ParseFront;
		using Base::ContextStyleBegin;
		using Base::ContextStyleEnd;

		using Base::ParseSetter;

		void ParseTimer();
		void ParseDate();

		void ParseColor()			{}
		void ParseStyle()			{}
		void ParseFront()			{}

		void ContextStyleBegin()	{}
		void ContextStyleEnd()		{}

		void ParseSetter();

	public:
		using Base::FormatReadParameterThrow;

	public:
		using Base::RunType;
		using Base::BasicRunType;

		// Type formating from UnFormatType<>
		template<typename Type>
		inline void RunType(Type&& type)						{ UnFormatType<typename FormatTypeForwardAs<Detail::GetBaseType<Type>>::Type, M_Type>::Read(type, *this); }
		template<typename Type, typename ...Rest>
		inline void ReadType(Type&& type, Rest&& ...rest)		{ RunType(type, std::forward<Rest>(rest)...); }

		// Only support basic type that are considered as basic by Buffer class
		template<typename Type>
		inline void BasicRunType(Type&& type)					{ m_BufferIn.BasicReadType(type); }
		template<typename Type, typename ...Rest>
		inline void BasicReadType(Type&& type, Rest&& ...rest)	{ BasicRunType(type, std::forward<Rest>(rest)...); }

	public:
		using Base::GetStringViewParamUntil;
		using Base::GetStringViewUntil;
		using Base::ReadDataType;

	public:
		inline bool FormatIsEndOfParameter()	{ return m_Format.IsEqualTo('}'); }
		inline void FormatGoToEndOfParameter()	{ while (m_Format.IsNotEqualTo('}') && m_Format.CanMoveForward()) m_Format.ForwardNoCheck(); }
		inline void FormatGoOutOfParameter()	{ while (m_Format.IsNotEqualTo('}') && m_Format.CanMoveForward()) m_Format.ForwardNoCheck(); m_Format.Forward(); }

		inline bool Check()						{ return m_BufferIn.IsEqualTo(m_Format.Get()); }
		inline bool CheckAndNext()				{ if (m_BufferIn.IsEqualTo(m_Format.Get())) { m_BufferIn.Forward(); m_Format.Forward(); return true; } return false; }

		template<typename ...CharToTest>
		inline bool CheckUntilNextParameter(const CharToTest ...ele) {
			while (m_Format.IsNotEqualTo('{', ele...) && m_Format.CanMoveForward()) {
				if (!Check()) return false;
				m_Format.ForwardNoCheck(); m_BufferIn.Forward();
			}
			return true;
		}

		template<typename ...CharToTest>
		inline bool CheckUntilEndOfParameter(const CharToTest ...ele) {
			while (m_Format.IsNotEqualTo('}', ele...) && m_Format.CanMoveForward()) {
				if (!Check()) return false;
				m_Format.ForwardNoCheck(); m_BufferIn.Forward();
			}
			return true;
		}
	};
}

#include "BaseFormat\BaseAnsiTextColor.h"
#include "BaseFormat\BaseAnsiTextFront.h"
#include "BaseFormat\BaseAnsiTextStyle.h"
#include "BaseFormat\BaseFormat.h"
#include "BaseFormat\BaseSTDLib.h"
#include "BaseFormat\Chrono.h"
