#pragma once

#include "BasicFormatContext.h"
#include "BasicFormatContextCoreImpl.h"

namespace EngineCore::Instrumentation::Fmt {

	/////---------- Get format parameter ----------/////
	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	template<typename T>
	bool BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::FormatReadParameter(T& i) {
		if (!m_FormatStr.IsEqualTo('{'))	return FormatStr().ReadUInt(i);

		const CharFormat* const mainSubFormat = m_FormatStr.GetBufferCurrentPos();
		FormatIdx formatIdx = FORMAT_IDX_NOT_FOUND;
		if (GetFormatIdx(formatIdx)) {
			m_FormatStr.Forward();
			m_ContextArgs.GetFormatValueAt(i, formatIdx);
			return true;
		}
		m_FormatStr.SetBufferCurrentPos(mainSubFormat);
		return false;
	}


	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParameterParseDataStyle() {

			 if (m_FormatStr.IsEqualForward('C')) { m_AnsiFormatterChange.HasMadeChange = true; m_FormatData.AnsiTextColorChange.HasChangeColor = true; m_AnsiTextCurrentColor = Detail::AnsiTextCurrentColor();	ReadAnsiTextColorParameter(); }
		else if (m_FormatStr.IsEqualForward('S')) { m_AnsiFormatterChange.HasMadeChange = true; m_FormatData.AnsiTextStyleChange.HasChangeStyle = true; m_AnsiTextCurrentStyle = Detail::AnsiTextCurrentStyle();	ReadAnsiTextStyleParameter(); }
		else if (m_FormatStr.IsEqualForward('F')) { m_AnsiFormatterChange.HasMadeChange = true; m_FormatData.AnsiTextFrontChange.HasChangeFront = true; m_AnsiTextCurrentFront = Detail::AnsiTextCurrentFront();	ReadAnsiTextFrontParameter(); }

		else if (m_FormatStr.IsEqualForward('B')) { m_FormatData.IntPrint = Detail::ValueIntPrint::Bin;	FormatReadParameter(m_FormatData.DigitSize); }
		else if (m_FormatStr.IsEqualForward('X')) { m_FormatData.IntPrint = Detail::ValueIntPrint::Hex;	FormatReadParameter(m_FormatData.DigitSize); }
		else if (m_FormatStr.IsEqualForward('O')) { m_FormatData.IntPrint = Detail::ValueIntPrint::Oct;	FormatReadParameter(m_FormatData.DigitSize); }
		else if (m_FormatStr.IsEqualForward('D')) { m_FormatData.IntPrint = Detail::ValueIntPrint::Int;	FormatReadParameter(m_FormatData.DigitSize); }

		else if (m_FormatStr.IsEqualForward('L')) { m_FormatData.PrintStyle = Detail::PrintStyle::LowerCase; }
		else if (m_FormatStr.IsEqualForward('U')) { m_FormatData.PrintStyle = Detail::PrintStyle::UpperCase; }

	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParameterParseDataSpecial() {
		if (m_FormatStr.IsEqualForward('{')) {		// Forward specifier
			FormatIdx dataIdx;
			GetFormatIdx(dataIdx);
			m_ContextArgs.GetParameterDataFromIdx(*this, dataIdx);
			m_FormatStr.Forward();
		}

		else if (m_FormatStr.IsEqualForward('=')) { m_FormatData.TrueValue = true; }

		else if (m_FormatStr.IsEqualForward('.')) { FormatReadParameter(m_FormatData.FloatPrecision); }

		else if (m_FormatStr.IsEqualForward('>')) { m_FormatData.ShiftType = Detail::ShiftType::Right;	FormatReadParameter(m_FormatData.ShiftValue); }
		else if (m_FormatStr.IsEqualForward('<')) { m_FormatData.ShiftType = Detail::ShiftType::Left;	FormatReadParameter(m_FormatData.ShiftValue); }
		else if (m_FormatStr.IsEqualForward('^')) { m_FormatData.ShiftType = Detail::ShiftType::Center;	FormatReadParameter(m_FormatData.ShiftValue); }
		else if (m_FormatStr.IsEqualForward('0')) { m_FormatData.ShiftPrint = Detail::ShiftPrint::Zeros; }
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParameterParseDataCustom() {
		const char* namePos = m_FormatStr.GetBufferCurrentPos();
		m_FormatStr.ParamGoTo(' ', '=');
		StringViewFormat name(namePos, m_FormatStr.GetBufferCurrentPos() - namePos);

		m_FormatStr.ParamGoTo('=', '\'');
		m_FormatStr.IsEqualForward('=');
		m_FormatStr.IgnoreSpace();

		if (m_FormatStr.IsEqualForward('\'')) {
			const char* valuePos = m_FormatStr.GetBufferCurrentPos();
			m_FormatStr.ParamGoTo('\'');
			std::size_t valueSize = m_FormatStr.GetBufferCurrentPos() - valuePos;
			m_FormatData.AddSpecifier(name, StringViewFormat(valuePos, valueSize));
		}
		else if (m_FormatStr.IsADigit()) {
			Detail::FormatDataType value = 0;
			m_FormatStr.ReadInt(value);
			m_FormatData.AddSpecifier(name, value);
		}
		else if (m_FormatStr.IsEqualForward('{')) {
			Detail::FormatDataType value = 0;
			FormatIdx idx = 0;
			bool get = GetFormatIdx(idx);
			m_FormatStr.IsEqualForward('}');
			m_ContextArgs.GetFormatValueAt(value, idx);
			m_FormatData.AddSpecifier(name, value);
		}
	}

	/////---------- Impl ----------/////
	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParameterParseData() {
		if (m_FormatStr.IsEqualTo(':')) {
			m_FormatData.HasSpec = true;
			while (!m_FormatStr.IsEndOfParameter()) {
				m_FormatStr.Forward();
				m_FormatStr.IgnoreSpace();

				if(m_FormatStr.IsUpperCase())
					ParameterParseDataStyle();
				else if(!m_FormatStr.IsLowerCase())
					ParameterParseDataSpecial();
				else
					ParameterParseDataCustom();

				m_FormatStr.ParamGoTo(',');
			}
		}
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	bool BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::GetFormatIdx(FormatIdx& idx) {
		const CharFormat* mainSubFormat = m_FormatStr.GetBufferCurrentPos();

		// I : if there is no number specified : ':' or '}'
		if (m_FormatStr.IsEqualTo(':') || m_FormatStr.IsEqualTo('}')) {
			idx = m_ValuesIdx++;
			if(idx < m_ContextArgs.Size())	return true;
			--m_ValuesIdx;
		}

		// II: A number(idx)
		if (m_FormatStr.ReadUInt(idx))
			if (m_FormatStr.IsEqualTo(':') || m_FormatStr.IsEqualTo('}'))
				if (idx < m_ContextArgs.Size())	return true;
		m_FormatStr.SetBufferCurrentPos(mainSubFormat);

		// III : A name
		m_ContextArgs.GetNamedArgsIdx(*this, idx, 0);
		if (idx < m_ContextArgs.Size() /* || idx != FormatIdxNotFound */)
			return true;
		m_FormatStr.SetBufferCurrentPos(mainSubFormat);

		// VI : { which is a idx to a number
		if (m_FormatStr.IsEqualForward('{'))
		{
			FormatIdx newIdx;
			if (GetFormatIdx(newIdx)) {
				if (newIdx != idx && newIdx < m_ContextArgs.Size())
				{
					m_ContextArgs.GetFormatValueAt(idx, newIdx);
					m_FormatStr.IsEqualForwardThrow('}');
					return true;
				}
				else
					throw Detail::FormatParseError();
			}
		}
		m_FormatStr.SetBufferCurrentPos(mainSubFormat);

		return false;
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParameterParseSpecial() {
			 if (m_FormatStr.IsEqualTo('C') && m_FormatStr.NextIsEqualForward(':', '}'))		{ m_AnsiFormatterChange.HasMadeChange = true; ReadAnsiTextColorParameter(); }
		else if (m_FormatStr.IsEqualTo('T') && m_FormatStr.NextIsEqualForward(':', '}'))		{ m_AnsiFormatterChange.HasMadeChange = true; ReadTimerParameter();		    }
		else if (m_FormatStr.IsEqualTo('D') && m_FormatStr.NextIsEqualForward(':', '}'))		{ m_AnsiFormatterChange.HasMadeChange = true; ReadDateParameter();		    }
		else if (m_FormatStr.IsEqualTo('S') && m_FormatStr.NextIsEqualForward(':', '}'))		{ m_AnsiFormatterChange.HasMadeChange = true; ReadAnsiTextStyleParameter(); }
		else if (m_FormatStr.IsEqualTo('F') && m_FormatStr.NextIsEqualForward(':', '}'))		{ m_AnsiFormatterChange.HasMadeChange = true; ReadAnsiTextFrontParameter(); }
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParameterParseVariable(FormatIdx formatIdx) {
		FormatDataType data;
		data.Clone(m_FormatData);
		m_FormatData = FormatDataType();

		Detail::AnsiTextCurrentColor ansiTextColor(m_AnsiTextCurrentColor);
		Detail::AnsiTextCurrentStyle ansiTextStyle(m_AnsiTextCurrentStyle);
		Detail::AnsiTextCurrentFront ansiTextFront(m_AnsiTextCurrentFront);

		if (!m_FormatData.IsInit)		ParameterParseData();

		m_ContextArgs.FormatTypeFromIdx(*this, formatIdx);

		if (m_FormatData.AnsiTextColorChange.HasChangeColor) { m_AnsiTextCurrentColor = ansiTextColor;	ReloadColor(m_AnsiTextCurrentColor, m_FormatData.AnsiTextColorChange); }
		if (m_FormatData.AnsiTextStyleChange.HasChangeStyle) { m_AnsiTextCurrentStyle = ansiTextStyle;	ReloadStyle(m_AnsiTextCurrentStyle, m_FormatData.AnsiTextStyleChange); }
		if (m_FormatData.AnsiTextFrontChange.HasChangeFront) { m_AnsiTextCurrentFront = ansiTextFront;	ReloadFront(m_AnsiTextCurrentFront, m_FormatData.AnsiTextFrontChange); }

		m_FormatData.Clone(data);
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	bool BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParameterParse() {
		m_FormatStr.Forward();				// Skip {

		if (m_FormatStr.IsUpperCase())
			ParameterParseSpecial();
		else {
			FormatIdx formatIdx;
			if (!GetFormatIdx(formatIdx))
				return false;
			ParameterParseVariable(formatIdx);
		}

		m_FormatStr.GoOutOfParameter();		// Skip}
		return true;
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::Run() {
		while (!m_FormatStr.IsEnd()) {

			WriteUntilNextParameter();

			if (m_FormatStr.IsEqualTo('{'))
				if (!ParameterParse())
					m_BufferOut.PushBack('{');
		}
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::SafeRun() {
		try {
			Run();
		}
		catch (...) { }

		CheckEndStr();
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	template<typename NewCharFormat, typename ...Args>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::LittleFormat(const std::basic_string_view<NewCharFormat> format, Args&& ...args) {
		BasicFormatContext<NewCharFormat, CharBuffer, Args...> child(format, *this, std::forward<Args>(args)...);
		child.Run();
		UpdateContextFromChild(child);
	}
}


