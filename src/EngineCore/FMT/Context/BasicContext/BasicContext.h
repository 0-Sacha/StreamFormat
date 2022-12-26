#pragma once

#include "FMT/Detail/Detail.h"
#include "FMT/Detail/Buffer/BasicBufferIn.h"
#include "FMT/Detail/Buffer/Format.h"

#include "FMT/Detail/FormatterHandler/FormatterHandler.h"
#include "Utils/BasicContextArgsTupleInterface.h"
#include "Utils/FormatterContextTemplate.h"

namespace EngineCore::FMT::Context {

	template<typename CharFormat, typename ContextPackageSaving>
	class BasicContext {
	private:
		using M_Type 				= BasicContext<CharFormat, ContextPackageSaving>;
	
	public:
		using CharFormatType 		= CharFormat;

		using FormatDataType		= Detail::FormatData<CharFormat>;
		using FormatSpecifierType	= Detail::FormatSpecifier<CharFormat>;

		using FormatBufferType		= Detail::FormatterMemoryFormat<CharFormat>;

		using StringViewFormat 		= std::basic_string_view<CharFormat>;

        using ContextArgsInterface 	= Detail::BasicArgsTupleInterface<CharFormatType>;

	public:
		explicit BasicContext(const std::basic_string_view<CharFormat>& format, ContextArgsInterface* argsInterface, bool ownArgsInterface);
		BasicContext(const std::basic_string_view<CharFormat>& format);
		
		~BasicContext();

	protected:
		FormatBufferType		m_Format;
		Detail::FormatIndex		m_ValuesIndex;
		FormatDataType			m_FormatData;
		ContextArgsInterface* 	m_ContextArgsInterface;
        bool                    m_OwnArgsInterface;

	public:
		inline FormatBufferType&		Format()					{ return m_Format; }
		inline const FormatBufferType&	Format() const				{ return m_Format; }

		inline FormatDataType&			GetFormatData()										{ return m_FormatData; }
		inline const FormatDataType&	GetFormatData() const								{ return m_FormatData; }
		inline FormatDataType			ForwardFormatData() const							{ return m_FormatData; }
		inline void						SetFormatData(const FormatDataType& formatData)		{ m_FormatData = formatData; }

		inline ContextArgsInterface&		GetContextArgsInterface()						{ return *m_ContextArgsInterface; }
		inline const ContextArgsInterface&	GetContextArgsInterface() const					{ return *m_ContextArgsInterface; }

		inline void SetContextArgsInterface(ContextArgsInterface* contextArgsInterface, bool own)
		{
			m_ValuesIndex = Detail::FormatIndex(0, contextArgsInterface->Size());
			m_ContextArgsInterface = contextArgsInterface;
			m_OwnArgsInterface = own;
		}

	public:
		virtual void Run() = 0;
		void SafeRun();

	public:
		Detail::FormatIndex GetFormatIndexThrow();

	public:
		void FormatDataApplyNextOverride();

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