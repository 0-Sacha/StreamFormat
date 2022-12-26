
#pragma once

#include "FMT/Context/BasicContext/BasicContextInclude.h"

#include "Utils/ParserType.h"

#include "ParserContextArgsTuple.h"

namespace EngineCore::FMT::Context {

	template<typename CharFormat, typename CharBuffer>
	class BasicParserContext : public BasicContext<CharFormat, int, BasicParserContext<CharFormat, CharBuffer, ContextArgs...>>
	{
	public:
		using Base = BasicContext<CharFormat, int, BasicParserContext<CharFormat, CharBuffer, ContextArgs...>>;
		using M_Type = BasicParserContext<CharFormat, CharBuffer, ContextArgs...>;

		friend Base;

		using typename Base::CharFormatType;
		using typename Base::FormatDataType;
		using typename Base::StringViewFormat;
		using typename Base::FormatBufferType;

		using CharBufferType	= CharBuffer;
		using StringViewBuffer	= std::basic_string_view<CharBuffer>;
		using BufferInType		= Detail::BasicFormatterMemoryBufferIn<CharBuffer>;
		using ContextArgsType	= Detail::ParserContextArgsTuple<ContextArgs...>;

	public:
		BasicParserContext(const std::basic_string_view<CharFormat>& format, const std::basic_string_view<CharBuffer>& buffer, ContextArgs&& ...args);

		// Used for SubContext
		template<typename ParentCharFormat, typename ...ParentContextArgs>
		BasicParserContext(const std::basic_string_view<CharFormat>& format, BasicParserContext<ParentCharFormat, CharBuffer, ParentContextArgs...>& parentContext, ContextArgs &&...args);

		~BasicParserContext();

	protected:
		using Base::m_Format;
		using Base::m_ValuesIndex;
		using Base::m_FormatData;

		BufferInType 		m_BufferIn;
		ContextArgsType 	m_ContextArgsInterface;

	public:
		using Base::Format;
		using Base::GetFormatData;
		using Base::ForwardFormatData;
		using Base::SetFormatData;
		using Base::FormatterHandler::GetInstance;

		inline BufferInType& BufferIn()					{ return m_BufferIn; }
		inline const BufferInType& BufferIn() const		{ return m_BufferIn; }

	public:
		using Base::SafeRun;
		void Run();

	public:
        template<typename CharType, std::size_t SIZE, typename ...NewContextArgs>
		inline void SubContext(const CharType (&format)[SIZE], NewContextArgs&& ...args)
		{ SubContext(std::basic_string_view<CharType>(format), std::forward<NewContextArgs>(args)...); }

		template<typename NewCharFormat, typename ...NewContextArgs>
		void SubContext(const std::basic_string_view<NewCharFormat>& format, NewContextArgs&& ...args);

	public:
		using Base::GetFormatIndexThrow;

	public:
		// TupleInterface
		using Base::GetTypeAtIndexThrow;
		using Base::GetTypeAtIndexConvertThrow;
		using Base::GetIndexOfCurrentNameArg;

		Detail::FormatIndex GetIndexOfCurrentNameArg() override
					{ return m_ContextArgsInterface.GetIndexOfCurrentNameArg(*this, Detail::FormatIndex(0, m_ValuesIndex.MaxValue)); }

		void RunTypeAtIndex(const Detail::FormatIndex& index)
					{ m_ContextArgsInterface.RunTypeAtIndex(*this, index); }

		template <typename T>
		const Detail::GetBaseType<T>* GetTypeAtIndex(const Detail::FormatIndex& index)
					{ return m_ContextArgsInterface.template GetTypeAtIndexThrow<T>(index); }

		template <typename T>
		T GetTypeAtIndexConvertThrow(const Detail::FormatIndex& index)
					{ return m_ContextArgsInterface.template GetTypeAtIndexConvertThrow<T>(index); }

		template <typename T>
		bool RunFuncFromTypeAtIndex(const Detail::FormatIndex& index, std::function<void(const T&)> func)
		{
			const T* value = m_ContextArgsInterface.template GetTypeAtIndexThrow<T>(index);
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


		void ParseFormatDataColor() override {}
		void ParseFormatDataStyle() override {}
		void ParseFormatDataFront() override {}

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

		void ParseTimer() override;
		void ParseDate() override;

		void ParseColor() override			{}
		void ParseStyle() override			{}
		void ParseFront() override			{}
		void ContextStyleBegin() override	{}
		void ContextStyleEnd() override		{}

		void ParseSetter() override;

	public:
		using Base::FormatReadParameterThrow;

	public:
		// Type formating from FormatterType<>
		template<typename Type, typename ...Rest>
		inline void RunType(Type&& type, const Rest&& ...rest) 			{ RunType(type); RunType(std::forward<Rest>(rest)...); }
		template<typename Type> inline void RunType(Type&& type) 		{ FormatterType<typename FormatTypeForwardAs<Detail::GetBaseType<Type>>::Type, M_Type>::Write(type, *this); }

		template<typename Type, typename ...Rest>
		inline void RunSubType(Type&& type, const Rest&& ...rest) 		{ RunSubType(type); RunSubType(std::forward<Rest>(rest)...); }
		template<typename Type> inline void RunSubType(Type&& type) 	{
			if (m_FormatData.NextOverride.size() == 0)
				return RunType(type);
			FormatDataType formatDataCopy = m_FormatData;
			FormatDataApplyNextOverride();
			RunType(type); 
			m_FormatData = formatDataCopy;
		}

		// Only support basic type that are considered as basic by Buffer class
		template<typename Type, typename ...Rest>
		inline void BasicRunType(Type&& type, Rest&& ...rest) 			{ BasicRunType(type); BasicRunType(std::forward<Rest>(rest)...); };
		template<typename Type> inline void BasicRunType(Type&& type)	{ ParserType<typename FormatTypeForwardAs<Detail::GetBaseType<Type>>::Type, M_Type>::Read(type, *this); }

		template<typename Type, typename ...Rest>
		inline void BasicRunSubType(Type&& type, Rest&& ...rest) 		 	{ m_BufferIn.BasicReadType(type); };

		template<typename Type> inline void BasicRunSubType(Type&& type) 	{
			if (m_FormatData.NextOverride.size() == 0)
				return BasicRunType(type);
			FormatDataType formatDataCopy = m_FormatData;
			FormatDataApplyNextOverride();
			BasicRunType(type); 
			m_FormatData = formatDataCopy;
		}

		// Type formating from ParserType<>
		template<typename Type, typename ...Rest>
		inline void ReadType(Type&& type, Rest&& ...rest)		{ RunType(type, std::forward<Rest>(rest)...); }
		template<typename Type, typename ...Rest>
		inline void ReadSubType(Type&& type, Rest&& ...rest)	{ RunSubType(type, std::forward<Rest>(rest)...); }

		// Only support basic type that are considered as basic by Buffer class
		template<typename Type, typename ...Rest>
		inline void BasicReadType(Type&& type, Rest&& ...rest)		{ BasicRunType(type, std::forward<Rest>(rest)...); }
		template<typename Type, typename ...Rest>
		inline void BasicSubReadType(Type&& type, Rest&& ...rest)	{ BasicSubRunType(type, std::forward<Rest>(rest)...); }

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
