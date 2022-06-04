#pragma once

#include "EngineCore/Instrumentation/Formatter/Core/Detail/Detail.h"
#include "EngineCore/Instrumentation/Formatter/Core/Buffer/Buffer.h"
#include "EngineCore/Instrumentation/Formatter/Core/FormatterHandler/FormatterHandler.h"

namespace EngineCore::FMT::Context {
	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	class BasicContext {
	public:
		friend Master;

		using CharFormatType 		= CharFormat;

		using FormatDataType		= Detail::FormatData<CharFormat>;
		using FormatSpecifierType	= Detail::FormatSpecifier<CharFormat>;

		using FormatBufferType		= Detail::FormatterMemoryFormat<CharFormat>;

		using StringViewFormat 		= std::basic_string_view<CharFormat>;

	public:
		explicit BasicContext(const std::basic_string_view<CharFormat>& format, const std::size_t maxIndex);

		template<typename ParentFormat, typename ParentMaster>
		explicit BasicContext(const std::basic_string_view<CharFormat>& format, BasicContext<ParentFormat, ContextPackageSaving, ParentMaster>& parent, const std::size_t maxIndex);

	protected:
		FormatBufferType		m_Format;
		Detail::FormatIndex		m_ValuesIndex;
		FormatDataType			m_FormatData;

	public:
		inline FormatBufferType&		Format()					{ return m_Format; }
		inline const FormatBufferType&	Format() const				{ return m_Format; }

		inline FormatDataType&			GetFormatData()				{ return m_FormatData; }
		inline const FormatDataType&	GetFormatData() const		{ return m_FormatData; }
		inline FormatDataType			ForwardFormatData() const	{ return m_FormatData; }

	public:
		inline static FormatterHandler& GetAPI()					{ return FormatterHandler::GetInstance(); }

	public:
		void Run() 																							{ reinterpret_cast<Master*>(this)->Run(); 				return; throw Detail::FormatShouldNotEndHere(); }
		template<typename NewCharFormat, typename ...NewContextArgs>
		void LittleFormat(const std::basic_string_view<NewCharFormat>& format, NewContextArgs&& ...args) 	{ reinterpret_cast<Master*>(this)->LittleFormat(format, std::forward<NewContextArgs>(args)...); 	return; throw Detail::FormatShouldNotEndHere(); }

		void SafeRun();
		template<typename CharType, std::size_t SIZE, typename ...NewContextArgs>
		inline void LittleFormat(const CharType (&format)[SIZE], NewContextArgs&& ...args)
		{ LittleFormat(std::basic_string_view<CharType>(format), std::forward<NewContextArgs>(args)...); }

	public:
		Detail::FormatIndex GetFormatIndexThrow();

	public:
		template <typename T>
		const Detail::GetBaseType<T>* GetTypeAtIndex(const Detail::FormatIndex& index) 				{ return (*reinterpret_cast<Master*>(this)).template GetTypeAtIndex<T>(index); 	throw Detail::FormatShouldNotEndHere(); }
		template <typename T>
		T GetTypeAtIndexConvertThrow(const Detail::FormatIndex& index) 			{ return (*reinterpret_cast<Master*>(this)).template GetTypeAtIndexConvertThrow<T>(index); 	throw Detail::FormatShouldNotEndHere(); }
		Detail::FormatIndex GetIndexOfCurrentNameArg() 							{ return reinterpret_cast<Master*>(this)->GetIndexOfCurrentNameArg(); 		throw Detail::FormatShouldNotEndHere(); }
		void RunTypeAtIndex(const Detail::FormatIndex& index) 					{ return reinterpret_cast<Master*>(this)->RunTypeAtIndex(index); 			throw Detail::FormatShouldNotEndHere(); }

		template <typename T>
		bool RunFuncFromTypeAtIndex(const Detail::FormatIndex& index, std::function<void (const T&)> func)
																				{ return (*reinterpret_cast<Master*>(this)).template RunFuncFromTypeAtIndex<T>(index, func); 	throw Detail::FormatShouldNotEndHere(); }

		template <typename T>
		const Detail::GetBaseType<T>& GetTypeAtIndexThrow(const Detail::FormatIndex& index) {
            const Detail::GetBaseType<T>* value = GetTypeAtIndex<T>(index);
            if (value == nullptr)
                throw Detail::FormatGivenTypeError{};
            return *value;
        }

	protected:
		void ParseFormatDataBase();
		void ParseFormatDataSpecial();
		void ParseFormatDataCustom();
		void ParseFormatData();

		void ParseFormatDataColor() 									{ return reinterpret_cast<Master*>(this)->ParseFormatDataColor(); 	throw Detail::FormatShouldNotEndHere(); }
		void ParseFormatDataStyle() 									{ return reinterpret_cast<Master*>(this)->ParseFormatDataStyle(); 	throw Detail::FormatShouldNotEndHere(); }
		void ParseFormatDataFront() 									{ return reinterpret_cast<Master*>(this)->ParseFormatDataFront(); 	throw Detail::FormatShouldNotEndHere(); }
		ContextPackageSaving ContextStyleSave() 						{ return reinterpret_cast<Master*>(this)->ContextStyleSave(); 		throw Detail::FormatShouldNotEndHere(); }
		void ContextStyleRestore(const ContextPackageSaving& package) 	{ return reinterpret_cast<Master*>(this)->ContextStyleRestore(package); 	throw Detail::FormatShouldNotEndHere(); }

		void ParseSpecial();
		void ParseVariable(Detail::FormatIndex formatIdx);
		bool Parse();

	protected:
		void ParseTimer() 			{ return reinterpret_cast<Master*>(this)->ParseTimer(); 		throw Detail::FormatShouldNotEndHere(); }
		void ParseDate() 			{ return reinterpret_cast<Master*>(this)->ParseDate(); 			throw Detail::FormatShouldNotEndHere(); }

		void ParseColor() 			{ return reinterpret_cast<Master*>(this)->ParseColor(); 		throw Detail::FormatShouldNotEndHere(); }
		void ParseStyle() 			{ return reinterpret_cast<Master*>(this)->ParseStyle(); 		throw Detail::FormatShouldNotEndHere(); }
		void ParseFront() 			{ return reinterpret_cast<Master*>(this)->ParseFront(); 		throw Detail::FormatShouldNotEndHere(); }
		void ContextStyleBegin() 	{ return reinterpret_cast<Master*>(this)->ContextStyleBegin(); 	throw Detail::FormatShouldNotEndHere(); }
		void ContextStyleEnd() 		{ return reinterpret_cast<Master*>(this)->ContextStyleEnd(); 	throw Detail::FormatShouldNotEndHere(); }

		void ParseSetter() 			{ return reinterpret_cast<Master*>(this)->ParseSetter(); 		throw Detail::FormatShouldNotEndHere(); }

	public:
		template<typename T> void FormatReadParameterThrow(T& i);

	public:
		// Type formating from FormatType<>
		template<typename Type, typename ...Rest>
		inline void RunType(Type&& type, const Rest&& ...rest) 			{ RunType(type); RunType(std::forward<Rest>(rest)...); }
		template<typename Type> inline void RunType(Type&& type) 		{ return reinterpret_cast<Master*>(this)->RunType(type); 		throw Detail::FormatShouldNotEndHere(); }

		// Only support basic type that are considered as basic by Buffer class
		template<typename Type, typename ...Rest>
		inline void BasicRunType(Type&& type, Rest&& ...rest) 			{ BasicRunType(type); BasicRunType(std::forward<Rest>(rest)...); };
		template<typename Type> inline void BasicRunType(Type&& type)	{ return reinterpret_cast<Master*>(this)->BasicRunType(type); 	throw Detail::FormatShouldNotEndHere(); }

	public:
		template <typename ...CharToTest>
		inline StringViewFormat GetStringViewParamUntil(CharToTest ...c) {
			const char* namePos = m_Format.GetBufferCurrentPos();
			m_Format.ParamGoTo(c...);
			return StringViewFormat(namePos, m_Format.GetBufferCurrentPos() - namePos);
		}

		template <typename ...CharToTest>
		inline StringViewFormat GetStringViewUntil(CharToTest ...c) {
			const char* namePos = m_Format.GetBufferCurrentPos();
			m_Format.GoTo(c...);
			return StringViewFormat(namePos, m_Format.GetBufferCurrentPos() - namePos);
		}

		inline Detail::DataType ReadDataType()
		{
			Detail::DataType res;
			m_Format.ReadInt(res);
			return res;
		}
	};
}