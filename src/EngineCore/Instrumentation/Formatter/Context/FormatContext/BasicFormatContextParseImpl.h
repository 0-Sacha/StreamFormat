#pragma once

#include "BasicFormatContext.h"
#include "BasicFormatContextCoreImpl.h"

namespace EngineCore::Instrumentation::FMT {

	/////---------- Get format parameter ----------/////
	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	template<typename T>
	bool BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::FormatReadParameter(T& i) {
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


	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParameterParseDataStyle() {

			 if (m_Format.IsEqualForward('C')) { m_AnsiFormatterChange.HasMadeChange = true; m_FormatData.AnsiTextColorChange.HasChangeColor = true; m_AnsiTextCurrentColor = Detail::AnsiTextCurrentColor();	ReadAnsiTextColorParameter(); }
		else if (m_Format.IsEqualForward('S')) { m_AnsiFormatterChange.HasMadeChange = true; m_FormatData.AnsiStyleChange.HasChangeStyle = true; m_AnsiStyle = Detail::AnsiStyle();	ReadAnsiTextStyleParameter(); }
		else if (m_Format.IsEqualForward('F')) { m_AnsiFormatterChange.HasMadeChange = true; m_FormatData.AnsiTextFrontChange.HasChangeFront = true; m_AnsiTextCurrentFront = Detail::AnsiTextCurrentFront();	ReadAnsiTextFrontParameter(); }

		else if (m_Format.IsEqualForward('B')) { m_FormatData.IntPrint = Detail::ValueIntPrint::Bin;	FormatReadParameter(m_FormatData.DigitSize); }
		else if (m_Format.IsEqualForward('X')) { m_FormatData.IntPrint = Detail::ValueIntPrint::Hex;	FormatReadParameter(m_FormatData.DigitSize); }
		else if (m_Format.IsEqualForward('O')) { m_FormatData.IntPrint = Detail::ValueIntPrint::Oct;	FormatReadParameter(m_FormatData.DigitSize); }
		else if (m_Format.IsEqualForward('D')) { m_FormatData.IntPrint = Detail::ValueIntPrint::Int;	FormatReadParameter(m_FormatData.DigitSize); }

		else if (m_Format.IsEqualForward('L')) { m_FormatData.PrintStyle = Detail::PrintStyle::LowerCase; }
		else if (m_Format.IsEqualForward('U')) { m_FormatData.PrintStyle = Detail::PrintStyle::UpperCase; }

		else if (m_Format.IsEqualForward('K')) { m_FormatData.Safe = true; }

	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParameterParseDataSpecial() {
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
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParameterParseDataCustom() {
		const char* namePos = m_Format.GetBufferCurrentPos();
		m_Format.ParamGoTo(' ', '=');
		StringViewFormat name(namePos, m_Format.GetBufferCurrentPos() - namePos);

		m_Format.ParamGoTo('=', '\'');
		m_Format.IsEqualForward('=');
		m_Format.IgnoreSpace();

		if (m_Format.IsEqualForward('\'')) {
			const char* valuePos = m_Format.GetBufferCurrentPos();
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
			if (GetFormatIdx(idx))
				throw Detail::FormatBufferWrongIndex();
			m_Format.IsEqualForward('}');
			m_ContextArgs.GetFormatValueAt(value, idx);
			m_FormatData.AddSpecifier(name, value);
		}
	}

	/////---------- Impl ----------/////
	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParameterParseData() {
		if (m_Format.IsEqualTo(':')) {
			m_FormatData.HasSpec = true;
			while (!m_Format.IsEndOfParameter()) {
				m_Format.Forward();
				m_Format.IgnoreSpace();

				if(m_Format.IsUpperCase())
					ParameterParseDataStyle();
				else if(!m_Format.IsLowerCase())
					ParameterParseDataSpecial();
				else
					ParameterParseDataCustom();

				m_Format.ParamGoTo(',');
			}
		}
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	bool BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::GetFormatIdx(FormatIdx& idx) {
		const CharFormat* mainSubFormat = m_Format.GetBufferCurrentPos();

		// I : if there is no number specified : ':' or '}'
		if (m_Format.IsEqualTo(':') || m_Format.IsEqualTo('}')) {
			idx = m_ValuesIdx++;
			if(idx < m_ContextArgs.Size())	return true;
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
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParameterParseSpecial() {
			 if (m_Format.IsEqualTo('C') && m_Format.NextIsEqualForward(':', '}'))		{ ReadAnsiTextColorParameter(); }
		else if (m_Format.IsEqualTo('S') && m_Format.NextIsEqualForward(':', '}'))		{ ReadAnsiTextStyleParameter(); }
		else if (m_Format.IsEqualTo('F') && m_Format.NextIsEqualForward(':', '}'))		{ ReadAnsiTextFrontParameter(); }
		else if (m_Format.IsEqualTo('T') && m_Format.NextIsEqualForward(':', '}'))		{ ReadTimerParameter();		    }
		else if (m_Format.IsEqualTo('D') && m_Format.NextIsEqualForward(':', '}'))		{ ReadDateParameter();		    }
		else if (m_Format.IsEqualTo('K') && m_Format.NextIsEqualForward(':'))				{ ReadSetterParameter(); 		}
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	void BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParameterParseVariable(FormatIdx formatIdx) {
		DataType data;
		data.Clone(m_FormatData);
		m_FormatData = DataType();

		Detail::AnsiTextCurrentColor ansiTextColor(m_AnsiTextCurrentColor);
		Detail::AnsiStyle ansiTextStyle(m_AnsiStyle);
		Detail::AnsiTextCurrentFront ansiTextFront(m_AnsiTextCurrentFront);

		if (!m_FormatData.IsInit)		ParameterParseData();

		m_ContextArgs.FormatTypeFromIdx(*this, formatIdx);

		if (m_FormatData.AnsiTextColorChange.HasChangeColor) { m_AnsiTextCurrentColor = ansiTextColor;	ReloadColor(m_AnsiTextCurrentColor, m_FormatData.AnsiTextColorChange); }
		if (m_FormatData.AnsiStyleChange.HasChangeStyle) { m_AnsiStyle = ansiTextStyle;	ReloadStyle(m_AnsiStyle, m_FormatData.AnsiStyleChange); }
		if (m_FormatData.AnsiTextFrontChange.HasChangeFront) { m_AnsiTextCurrentFront = ansiTextFront;	ReloadFront(m_AnsiTextCurrentFront, m_FormatData.AnsiTextFrontChange); }

		m_FormatData.Clone(data);
	}

	template<typename CharFormat, typename CharBuffer, typename ...ContextArgs>
	bool BasicFormatContext<CharFormat, CharBuffer, ContextArgs...>::ParameterParse() {
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
}


