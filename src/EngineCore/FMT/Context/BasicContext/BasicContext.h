#pragma once

#include "FMT/Detail/Detail.h"
#include "FMT/Detail/Buffer/BasicBufferIn.h"
#include "FMT/Detail/Buffer/Format.h"

#include "FMT/Detail/FormatterHandler/FormatterHandler.h"

namespace EngineCore::FMT::Context {

    template<typename CharFormat, typename CharBuffer>
    class BasisCompressedContext
    {
    public:
		using FormatDataType		= Detail::FormatData<CharFormat>;
		using FormatSpecifierType	= Detail::FormatSpecifier<CharFormat>;
		using FormatBufferType		= Detail::FormatterMemoryFormat<CharFormat>;
		using StringViewFormat 		= std::basic_string_view<CharFormat>;

    public:
		BasisCompressedContext(FormatBufferType& format, FormatDataType& formatData)
			: m_Format(format)
			, m_FormatData(formatData)
		{}

	protected:
		FormatBufferType& 	m_Format;
		FormatDataType&		m_FormatData;
    };
    

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
		bool 					m_IsChild;

	public:
		inline FormatBufferType&		Format()					{ return m_Format; }
		inline const FormatBufferType&	Format() const				{ return m_Format; }

		inline FormatDataType&			GetFormatData()										{ return m_FormatData; }
		inline const FormatDataType&	GetFormatData() const								{ return m_FormatData; }
		inline FormatDataType			ForwardFormatData() const							{ return m_FormatData; }
		inline void						SetFormatData(const FormatDataType& formatData)		{ m_FormatData = formatData; }

		inline bool						IsChild() const				{ return m_IsChild; }

	public:
		inline static Detail::FormatterHandler& GetAPI()			{ return Detail::FormatterHandler::GetInstance(); }

	public:
		virtual void Run() = 0;
		void SafeRun();

	public:
		Detail::FormatIndex GetFormatIndexThrow();

	public:
		void FormatDataApplyNextOverride();

	public:
		virtual Detail::FormatIndex GetIndexOfCurrentNameArg() = 0;
		virtual void RunTypeAtIndex(const Detail::FormatIndex& index) = 0;
		
		template <typename T>
		const Detail::GetBaseType<T>* GetTypeAtIndex(const Detail::FormatIndex& index)
					{ return (*reinterpret_cast<Master*>(this)).template GetTypeAtIndex<T>(index); }

		template <typename T>
		T GetTypeAtIndexConvertThrow(const Detail::FormatIndex& index)
					{ return (*reinterpret_cast<Master*>(this)).template GetTypeAtIndexConvertThrow<T>(index); }

		template <typename T>
		bool RunFuncFromTypeAtIndex(const Detail::FormatIndex& index, std::function<void (const T&)> func)
					{ return (*reinterpret_cast<Master*>(this)).template RunFuncFromTypeAtIndex<T>(index, func); }

		template <typename T>
		const Detail::GetBaseType<T>& GetTypeAtIndexThrow(const Detail::FormatIndex& index) {
            const Detail::GetBaseType<T>* value = GetTypeAtIndex<T>(index);
            if (value == nullptr)
                throw Detail::FormatGivenTypeError{};
            return *value;
        }

	protected:
		std::basic_string_view<CharFormat> ParseNextOverrideFormatData();

		void ParseFormatDataBase();
		void ParseFormatDataBase_ValueIntPrint(const Detail::ValueIntPrint type);
		void ParseFormatDataSpecial();
		void ParseFormatDataSpecial_ShiftType(const Detail::ShiftType type);
		void ParseFormatDataCustom();
		void ParseFormatData();

		virtual void ParseFormatDataColor() = 0;
		virtual void ParseFormatDataStyle() = 0;
		virtual void ParseFormatDataFront() = 0;
		virtual ContextPackageSaving ContextStyleSave() = 0;
		virtual void ContextStyleRestore(const ContextPackageSaving& package) = 0;

		void ParseSpecial();
		void ParseVariable(Detail::FormatIndex formatIdx);
		bool Parse();

	protected:
		virtual void ParseTimer() = 0;
		virtual void ParseDate() = 0;

		virtual void ParseColor() = 0;
		virtual void ParseStyle() = 0;
		virtual void ParseFront() = 0;
		virtual void ContextStyleBegin() = 0;
		virtual void ContextStyleEnd() = 0;
		
		virtual void ParseSetter() = 0;

	public:
		template<typename T> void FormatReadParameterThrow(T& i);

	public:
		// Type formating from FormatterType<>
		template<typename Type, typename ...Rest>
		inline void RunType(Type&& type, const Rest&& ...rest) 			{ RunType(type); RunType(std::forward<Rest>(rest)...); }
		template<typename Type> inline void RunType(Type&& type) 		{ return reinterpret_cast<Master*>(this)->RunType(type); }

		template<typename Type, typename ...Rest>
		inline void RunSubType(Type&& type, const Rest&& ...rest) 		{ RunSubType(type); RunSubType(std::forward<Rest>(rest)...); }
		template<typename Type> inline void RunSubType(Type&& type) 	{
			if (m_FormatData.NextOverride.size() == 0)
				return reinterpret_cast<Master*>(this)->RunType(type);
			FormatDataType formatDataCopy = m_FormatData;
			FormatDataApplyNextOverride();
			reinterpret_cast<Master*>(this)->RunType(type); 
			m_FormatData = formatDataCopy;
			return;
			throw Detail::FormatShouldNotEndHere();
		}

		// Only support basic type that are considered as basic by Buffer class
		template<typename Type, typename ...Rest>
		inline void BasicRunType(Type&& type, Rest&& ...rest) 			{ BasicRunType(type); BasicRunType(std::forward<Rest>(rest)...); };
		template<typename Type> inline void BasicRunType(Type&& type)	{ return reinterpret_cast<Master*>(this)->BasicRunType(type); }

		template<typename Type, typename ...Rest>
		inline void BasicRunSubType(Type&& type, Rest&& ...rest) 		 	{ BasicRunSubType(type); BasicRunSubType(std::forward<Rest>(rest)...); };

		template<typename Type> inline void BasicRunSubType(Type&& type) 	{
			if (m_FormatData.NextOverride.size() == 0)
				return reinterpret_cast<Master*>(this)->BasicRunType(type);
			FormatDataType formatDataCopy = m_FormatData;
			FormatDataApplyNextOverride();
			reinterpret_cast<Master*>(this)->BasicRunType(type); 
			m_FormatData = formatDataCopy;
			return;
			throw Detail::FormatShouldNotEndHere();
		}

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