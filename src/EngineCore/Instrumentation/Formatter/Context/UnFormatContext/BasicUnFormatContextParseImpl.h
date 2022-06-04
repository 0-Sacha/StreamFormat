#pragma once

#include "BasicUnFormatContext.h"
#include "BasicUnFormatContextCoreImpl.h"


namespace EngineCore::FMT {

	template<typename FormatContext>
	struct FormatType<UnFormatContextError, FormatContext>
	{
		static void Write(const UnFormatContextError t, FormatContext& context) {
			if (t)	context.LittleFormat("Format error idx : {} -- Buffer error idx : {}", t.FormatPosError, t.BufferPosError);
			else	context.LittleFormat("No-Error");
		}
	};

	template<typename T, typename CharName, typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	struct UnFormatType<StringViewNamedArgs<T, CharName>, BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>>
	{
		inline static void Read(StringViewNamedArgs<T, CharName>& t, BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>& context) {
			UnFormatType<Detail::GetBaseType<T>, BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>>::Read(t.GetValue(), context);
		}
	};

	template<typename T, typename CharName, typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	struct UnFormatType<StringNamedArgs<T, CharName>, BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>>
	{
		inline static void Read(StringNamedArgs<T, CharName>& t, BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>& context) {
			UnFormatType<Detail::GetBaseType<T>, BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>>::Read(t.GetValue(), context);
		}
	};


	/////---------- Get format parameter ----------/////
	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	template<typename T>
	bool BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>::FormatReadParameter(T& i) {
		if (!m_Format.IsEqualTo('{'))	return Format().ReadUInt(i);

		const CharFormat* const mainSubFormat = m_Format.GetBufferCurrentPos();
		FormatIdx formatIdx = FORMAT_IDX_NOT_FOUND;
		if (GetFormatIdx(formatIdx)) {
			m_Format.Forward();
			m_ContextArgs.GetFormatValueAt(i, formatIdx);
			return true;
		}
		m_Format.SetBufferCurrentPos(mainSubFormat);
		return false;
	}

	/////---------- Impl ----------/////


	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParameterParseDataStyle() {
		
			 if (m_Format.IsEqualForward('C')) { m_AnsiFormatterChange.HasMadeChange = true; m_FormatData.AnsiTextColorChange.HasChangeColor = true; m_AnsiTextCurrentColor = Detail::AnsiTextCurrentColor();	ReadAnsiTextColorParameter(); }
		else if (m_Format.IsEqualForward('S')) { m_AnsiFormatterChange.HasMadeChange = true; m_FormatData.AnsiStyleChange.HasChangeStyle = true; m_AnsiStyle = Detail::AnsiStyle();	ReadAnsiTextStyleParameter(); }
		else if (m_Format.IsEqualForward('F')) { m_AnsiFormatterChange.HasMadeChange = true; m_FormatData.AnsiFrontChange.HasChangeFront = true; m_AnsiTextCurrentFront = Detail::AnsiTextCurrentFront();	ReadAnsiFrontParameter(); }

		else if (m_Format.IsEqualForward('B')) { m_FormatData.IntPrint = Detail::ValueIntPrint::Bin;	FormatReadParameter(m_FormatData.DigitSize); }
		else if (m_Format.IsEqualForward('X')) { m_FormatData.IntPrint = Detail::ValueIntPrint::Hex;	FormatReadParameter(m_FormatData.DigitSize); }
		else if (m_Format.IsEqualForward('O')) { m_FormatData.IntPrint = Detail::ValueIntPrint::Oct;	FormatReadParameter(m_FormatData.DigitSize); }
		else if (m_Format.IsEqualForward('D')) { m_FormatData.IntPrint = Detail::ValueIntPrint::Int;	FormatReadParameter(m_FormatData.DigitSize); }

		else if (m_Format.IsEqualForward('L')) { m_FormatData.PrintStyle = Detail::PrintStyle::LowerCase; }
		else if (m_Format.IsEqualForward('U')) { m_FormatData.PrintStyle = Detail::PrintStyle::UpperCase; }

	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParameterParseDataSpecial() {
		if (m_Format.IsEqualForward('{')) {		// Forward specifier
			FormatIdx dataIdx;
			GetFormatIdx(dataIdx);
			m_ContextArgs.GetParameterDataFromIdx(*this, dataIdx);
			m_Format.Forward();
		}
		else if (m_Format.IsEqualForward('=')) { m_FormatData.TrueValue = true; }

		else if (m_Format.IsEqualForward('.')) { FormatReadParameter(m_FormatData.FloatPrecision); }

		else if (m_Format.IsEqualForward('>')) { m_FormatData.ShiftType = Detail::ShiftType::Right;	FormatReadParameter(m_FormatData.ShiftValue); }
		else if (m_Format.IsEqualForward('<')) { m_FormatData.ShiftType = Detail::ShiftType::Left;	FormatReadParameter(m_FormatData.ShiftValue); }
		else if (m_Format.IsEqualForward('^')) { m_FormatData.ShiftType = Detail::ShiftType::Center;	FormatReadParameter(m_FormatData.ShiftValue); }
		else if (m_Format.IsEqualForward('0')) { m_FormatData.ShiftPrint = Detail::ShiftPrint::Zeros; }
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParameterParseDataCustom() {
		const char* const namePos = m_Format.GetBufferCurrentPos();
		m_Format.ParamGoTo(' ', '=');
		StringViewFormat name(namePos, m_Format.GetBufferCurrentPos() - namePos);

		m_Format.ParamGoTo('=', '\'');
		m_Format.IsEqualForward('=');
		m_Format.IgnoreSpace();

		if (m_Format.IsEqualForward('\'')) {
			const char* const valuePos = m_Format.GetBufferCurrentPos();
			m_Format.GoTo('\'');
			std::size_t valueSize = m_Format.GetBufferCurrentPos() - valuePos;
			m_FormatData.AddSpecifier(name, StringViewFormat(valuePos, valueSize));
		}
		else if (m_Format.IsADigit()) {
			Detail::DataType value = 0;
			m_Format.ReadInt(value);
			m_FormatData.AddSpecifier(name, value);
		}
		else if (m_Format.IsEqualForward('{')) {
			Detail::DataType value = 0;
			FormatIdx idx = 0;
			GetFormatIdx(idx);
			m_Format.IsEqualForward('}');
			m_ContextArgs.GetFormatValueAt(value, idx);
			m_FormatData.AddSpecifier(name, value);
		}
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParameterParseData() {
		if (m_Format.IsEqualTo(':')) {
			m_FormatData.HasSpec = true;
			while (!FormatIsEndOfParameter()) {
				m_Format.Forward();
				m_Format.IgnoreSpace();

				if (m_Format.IsUpperCase())
					ParameterParseDataSpecial();
				else if (!m_Format.IsLowerCase())
					ParameterParseDataSpecial();
				else
					ParameterParseDataCustom();

				m_Format.ParamGoTo(',');
			}
		}
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	bool BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>::GetFormatIdx(FormatIdx& idx) {
		const CharFormat* mainSubFormat = m_Format.GetBufferCurrentPos();

		// I : if there is no number specified : ':' or '}'
		if (m_Format.IsEqualTo(':') || m_Format.IsEqualTo('}')) {
			idx = m_ValuesIdx++;
			if (idx < m_ContextArgs.Size())	return true;
			--m_ValuesIdx;
		}

		// II: A number(idx)
		if (m_Format.ReadUInt(idx))
			if (m_Format.IsEqualTo(':') || m_Format.IsEqualTo('}'))
				if (idx < m_ContextArgs.Size())	return true;
		m_Format.SetBufferCurrentPos(mainSubFormat);

		// III : A name
		m_ContextArgs.GetNamedArgsIdx(*this, idx, 0);
		if (idx < m_ContextArgs.Size() /* || idx != FormatIdxNotFound */)
			return true;
		m_Format.SetBufferCurrentPos(mainSubFormat);

		// VI : { which is a idx to a number
		if (m_Format.IsEqualForward('{'))
		{
			FormatIdx newIdx;
			if (GetFormatIdx(newIdx)) {
				if (newIdx != idx && newIdx < m_ContextArgs.Size())
				{
					m_ContextArgs.GetFormatValueAt(idx, newIdx);
					m_Format.IsEqualForwardThrow('}');
					return true;
				}
				else
					throw Detail::FormatParseError();
			}
		}
		m_Format.SetBufferCurrentPos(mainSubFormat);

		return false;
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParameterParseSpecial() {
		if		(m_Format.IsEqualForward('C'))		ReadAnsiTextColorParameter();
		else if (m_Format.IsEqualForward('T'))		ReadTimerParameter();
		else if (m_Format.IsEqualForward('D'))		ReadDateParameter();
		else if (m_Format.IsEqualForward('I'))		IgnoreParameter();
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParameterParseVariable(FormatIdx formatIdx) {
		DataType data;
		data.Clone(m_FormatData);
		m_FormatData = DataType();

		if (!m_FormatData.IsInit)	ParameterParseData();

		m_ContextArgs.ReadTypeFromIdx(*this, formatIdx);

		m_FormatData.Clone(data);
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	bool BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParameterParse() {
		m_Format.Forward();				// Skip {

		if (m_Format.IsUpperCase())
			ParameterParseSpecial();
		else {
			FormatIdx formatIdx;
			if (!GetFormatIdx(formatIdx))
				return false;
			ParameterParseVariable(formatIdx);
		}

		m_Format.GoOutOfParameter();		// Skip}
		return true;
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>::Run() {

		while (!m_Format.IsEnd()) {

			if (CheckUntilNextParameter())
			{
				if (m_Format.IsEqualTo('{'))
					ParameterParse();
			}
			else if (!Check())
				throw Detail::FormatParseError();
		}

	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	UnFormatContextError BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>::SafeRun() {
		UnFormatContextError error;

		try {
			Run();
		} catch (...) {
			error = UnFormatContextError((std::int16_t)m_Format.GetBufferCurrentSize(), (std::int16_t)m_BufferIn.GetBufferSize());
		}

		if (!m_BufferIn.IsEnd())
			error = UnFormatContextError((std::int16_t)m_Format.GetBufferCurrentSize(), (std::int16_t)m_BufferIn.GetBufferSize());
		
		return error;
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	template<typename NewCharFormat, typename ...Args>
	void BasicUnFormatContext<CharFormat, CharBuffer, ContextArgs...>::LittleUnFormat(const std::basic_string_view<NewCharFormat>& format, Args&& ...args) {
		BasicUnFormatContext<NewCharFormat, CharBuffer, Args...> child(format, *this, std::forward<Args>(args)...);
		child.Format();
		UpdateContextFromChild(child);
	}
}