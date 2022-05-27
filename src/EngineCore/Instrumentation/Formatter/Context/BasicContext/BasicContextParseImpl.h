#pragma once

#include "BasicContext.h"
#include "BasicContextCoreImpl.h"

namespace EngineCore::Instrumentation::FMT::Context {

	template<typename CharFormat, typename ContextPackageSaving>
	void BasicContext<CharFormat, ContextPackageSaving>::ParseFormatDataBase() {

			 if (m_Format.IsEqualForward('C')) { ParseFormatDataColor(); }
		else if (m_Format.IsEqualForward('S')) { ParseFormatDataStyle(); }
		else if (m_Format.IsEqualForward('F')) { ParseFormatDataFront(); }

		else if (m_Format.IsEqualForward('B')) { m_FormatData.IntPrint = Detail::ValueIntPrint::Bin;	FormatReadParameter(m_FormatData.DigitSize); }
		else if (m_Format.IsEqualForward('X')) { m_FormatData.IntPrint = Detail::ValueIntPrint::Hex;	FormatReadParameter(m_FormatData.DigitSize); }
		else if (m_Format.IsEqualForward('O')) { m_FormatData.IntPrint = Detail::ValueIntPrint::Oct;	FormatReadParameter(m_FormatData.DigitSize); }
		else if (m_Format.IsEqualForward('D')) { m_FormatData.IntPrint = Detail::ValueIntPrint::Int;	FormatReadParameter(m_FormatData.DigitSize); }

		else if (m_Format.IsEqualForward('L')) { m_FormatData.PrintStyle = Detail::PrintStyle::LowerCase; }
		else if (m_Format.IsEqualForward('U')) { m_FormatData.PrintStyle = Detail::PrintStyle::UpperCase; }

		else if (m_Format.IsEqualForward('A')) { m_FormatData.Safe = true; }

	}

	template<typename CharFormat, typename ContextPackageSaving>
	void BasicContext<CharFormat, ContextPackageSaving>::ParseFormatDataSpecial() {
		if (m_Format.IsEqualForward('{'))
		{
			Detail::FormatIndex formatIndex = GetFormatIndexThrow();
			m_FormatData.Modif(GetTypeAtIndexThrow<FormatDataType>(formatIndex));
			m_Format.IsEqualForwardThrow('}');
		}
		else if (m_Format.IsEqualForward('=')) { m_FormatData.TrueValue = true; }

		else if (m_Format.IsEqualForward('.')) { FormatReadParameter(m_FormatData.FloatPrecision); }

		else if (m_Format.IsEqualForward('>')) { m_FormatData.ShiftType = Detail::ShiftType::Right;		FormatReadParameter(m_FormatData.ShiftValue); }
		else if (m_Format.IsEqualForward('<')) { m_FormatData.ShiftType = Detail::ShiftType::Left;		FormatReadParameter(m_FormatData.ShiftValue); }
		else if (m_Format.IsEqualForward('^')) { m_FormatData.ShiftType = Detail::ShiftType::Center;	FormatReadParameter(m_FormatData.ShiftValue); }
		else if (m_Format.IsEqualForward('0')) { m_FormatData.ShiftPrint = Detail::ShiftPrint::Zeros; }
	}

	template<typename CharFormat, typename ContextPackageSaving>
	void BasicContext<CharFormat, ContextPackageSaving>::ParseFormatDataCustom() {
		StringViewFormat name = GetStringViewParamUntil(' ', '=');
		m_Format.ParamGoTo('=', '\'');
		m_Format.IsEqualForward('=');
		m_Format.IgnoreSpace();

		if (m_Format.IsEqualForward('\'')) {
			StringViewFormat value = GetStringViewParamUntil('\'');
			m_FormatData.AddSpecifier(name, value);
		}
		else if (m_Format.IsADigit()) {
			Detail::DataType value = ReadDataType();
			m_FormatData.AddSpecifier(name, value);
		}
		else if (m_Format.IsEqualForward('{')) {
			Detail::FormatIndex idx = GetFormatIndexThrow(idx);
			// m_FormatData.AddSpecifier(name, GetTypeAtIndexAuto(idx));
			m_Format.IsEqualForward('}');
		}
	}

	/////---------- Impl ----------/////
	template<typename CharFormat, typename ContextPackageSaving>
	void BasicContext<CharFormat, ContextPackageSaving>::ParseFormatData() {
		if (m_Format.IsEqualTo(':')) {
			m_FormatData.HasSpec = true;
			while (!m_Format.IsEndOfParameter()) {
				m_Format.Forward();
				m_Format.IgnoreSpace();

				if(m_Format.IsUpperCase())
					ParseFormatDataBase();
				else if(!m_Format.IsLowerCase())
					ParseFormatDataSpecial();
				else
					ParseFormatDataCustom();

				m_Format.ParamGoTo(',');
			}
		}
	}

	template<typename CharFormat, typename ContextPackageSaving>
	Detail::FormatIndex BasicContext<CharFormat, ContextPackageSaving>::GetFormatIndexThrow() {
		const CharFormat* mainSubFormat = m_Format.GetBufferCurrentPos();

		// I : if there is no number specified : ':' or '}'
		if (m_Format.IsEqualTo(':') || m_Format.IsEqualTo('}'))
			if(m_ValuesIndex.IsValid())
				return m_ValuesIndex.GetAndNext();

		// II: A number(idx)
		Detail::DataType idx;
		if (m_Format.ReadUInt(idx))
			if (m_Format.IsEqualTo(':') || m_Format.IsEqualTo('}'))
				if (idx < m_ContextArgs.Size())	return idx;

		m_Format.SetBufferCurrentPos(mainSubFormat);

		// III : A name
		Detail::FormatIndex index = GetIndexOfCurrentNameArg();
		if(m_ValuesIndex.IsValid())
			return index;

		m_Format.SetBufferCurrentPos(mainSubFormat);

		// VI : { which is a idx to a number
		if (m_Format.IsEqualForward('{'))
		{
			try {

				Detail::FormatIndex recIndex = GetFormatIndexThrow(newIdx);
				if(m_ValuesIndex.IsValid())
				{
					Detail::FormatIndex finalRecIndex = GetTypeAtIndexThrow(recIndex);
					m_Format.IsEqualForwardThrow('}');
					return finalRecIndex;
				}
				else
					throw Detail::FormatParseError();

			} catch (const Detail::FormatError&)
			{}
		}
		m_Format.SetBufferCurrentPos(mainSubFormat);

		throw Detail::FormatParseError();
		return {};
	}

	template<typename CharFormat, typename ContextPackageSaving>
	void BasicContext<CharFormat, ContextPackageSaving>::ParseSpecial() {
			 if (m_Format.IsEqualTo('C') && m_Format.NextIsEqualForward(':', '}'))		{ ParseColor(); 	}
		else if (m_Format.IsEqualTo('S') && m_Format.NextIsEqualForward(':', '}'))		{ ParseStyle(); 	}
		else if (m_Format.IsEqualTo('F') && m_Format.NextIsEqualForward(':', '}'))		{ ParseFront(); 	}
		else if (m_Format.IsEqualTo('T') && m_Format.NextIsEqualForward(':', '}'))		{ ParseTimer(); 	}
		else if (m_Format.IsEqualTo('D') && m_Format.NextIsEqualForward(':', '}'))		{ ParseDate(); 		}
		else if (m_Format.IsEqualTo('K') && m_Format.NextIsEqualForward(':'))			{ ParseSetter();	}
	}

	template<typename CharFormat, typename ContextPackageSaving>
	void BasicContext<CharFormat, ContextPackageSaving>::ParseVariable(Detail::FormatIndex formatIdx) {
		FormatDataType data = m_FormatData;
		m_FormatData = DataType();

		ContextPackageSaving package = ContextStyleSave();

		if (!m_FormatData.IsInit)		ParameterParseData();

		RunTypeAtIndex(formatIdx);

		ContextStyleRestore(package);

		m_FormatData = data;
	}

	template<typename CharFormat, typename ContextPackageSaving>
	bool BasicContext<CharFormat, ContextPackageSaving>::Parse() {
		m_Format.Forward();					// Skip {

		if (m_Format.IsUpperCase())
			ParseSpecial();
		else {
			Detail::FormatIndex formatIdx = GetFormatIndexThrow(formatIdx);
			ParseVariable(formatIdx);
		}

		m_Format.GoOutOfParameter();		// Skip}
		return true;
	}
}


