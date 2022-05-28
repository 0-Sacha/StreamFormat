#pragma once

#include "BasicContext.h"
#include "BasicContextCoreImpl.h"

namespace EngineCore::Instrumentation::FMT::Context {

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	void BasicContext<CharFormat, ContextPackageSaving, Master>::ParseFormatDataBase() {

			 if (m_Format.IsEqualForward('C')) { ParseFormatDataColor(); }
		else if (m_Format.IsEqualForward('S')) { ParseFormatDataStyle(); }
		else if (m_Format.IsEqualForward('F')) { ParseFormatDataFront(); }

		else if (m_Format.IsEqualForward('B')) { m_FormatData.IntPrint = Detail::ValueIntPrint::Bin;	FormatReadParameterThrow(m_FormatData.DigitSize); }
		else if (m_Format.IsEqualForward('X')) { m_FormatData.IntPrint = Detail::ValueIntPrint::Hex;	FormatReadParameterThrow(m_FormatData.DigitSize); }
		else if (m_Format.IsEqualForward('O')) { m_FormatData.IntPrint = Detail::ValueIntPrint::Oct;	FormatReadParameterThrow(m_FormatData.DigitSize); }
		else if (m_Format.IsEqualForward('D')) { m_FormatData.IntPrint = Detail::ValueIntPrint::Int;	FormatReadParameterThrow(m_FormatData.DigitSize); }

		else if (m_Format.IsEqualForward('L')) { m_FormatData.PrintStyle = Detail::PrintStyle::LowerCase; }
		else if (m_Format.IsEqualForward('U')) { m_FormatData.PrintStyle = Detail::PrintStyle::UpperCase; }

		else if (m_Format.IsEqualForward('A')) { m_FormatData.Safe = true; }

	}

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	void BasicContext<CharFormat, ContextPackageSaving, Master>::ParseFormatDataSpecial() {
		if (m_Format.IsEqualForward('{'))
		{
			Detail::FormatIndex formatIndex = GetFormatIndexThrow();
			m_FormatData.ModifyThrow(GetTypeAtIndexThrow<FormatDataType>(formatIndex));
			m_Format.IsEqualForwardThrow('}');
		}
		else if (m_Format.IsEqualForward('=')) { m_FormatData.TrueValue = true; }

		else if (m_Format.IsEqualForward('.')) { FormatReadParameterThrow(m_FormatData.FloatPrecision); }

		else if (m_Format.IsEqualForward('>')) { m_FormatData.ShiftType = Detail::ShiftType::Right;		FormatReadParameterThrow(m_FormatData.ShiftValue); }
		else if (m_Format.IsEqualForward('<')) { m_FormatData.ShiftType = Detail::ShiftType::Left;		FormatReadParameterThrow(m_FormatData.ShiftValue); }
		else if (m_Format.IsEqualForward('^')) { m_FormatData.ShiftType = Detail::ShiftType::Center;	FormatReadParameterThrow(m_FormatData.ShiftValue); }
		else if (m_Format.IsEqualForward('0')) { m_FormatData.ShiftPrint = Detail::ShiftPrint::Zeros; }
	}

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	void BasicContext<CharFormat, ContextPackageSaving, Master>::ParseFormatDataCustom() {
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
			Detail::FormatIndex idx = GetFormatIndexThrow();
			// m_FormatData.AddSpecifier(name, GetTypeAtIndexAuto(idx));
			m_Format.IsEqualForward('}');
		}
	}

	/////---------- Impl ----------/////
	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	void BasicContext<CharFormat, ContextPackageSaving, Master>::ParseFormatData() {
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

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	Detail::FormatIndex BasicContext<CharFormat, ContextPackageSaving, Master>::GetFormatIndexThrow() {
		const CharFormat* mainSubFormat = m_Format.GetBufferCurrentPos();

		// I : if there is no number specified : ':' or '}'
		if (m_Format.IsEqualTo(':') || m_Format.IsEqualTo('}'))
			if(m_ValuesIndex.IsValid())
				return m_ValuesIndex.GetAndNext();

		// II: A number(idx)
		Detail::FormatIndex idxGet;
		idxGet.SetContext(m_ValuesIndex);
		if (m_Format.ReadUInt(idxGet.Index))
			if (m_Format.IsEqualTo(':') || m_Format.IsEqualTo('}'))
				if (idxGet.IsValid())
					return idxGet;

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

				Detail::FormatIndex recIndex = GetFormatIndexThrow();
				if(m_ValuesIndex.IsValid())
				{
					Detail::FormatIndex finalRecIndex = GetTypeAtIndexThrow<Detail::FormatIndex>(recIndex);
					m_Format.IsEqualForwardThrow('}');
					return finalRecIndex;
				}
				else
					throw Detail::FormatParseError();

			} catch (const Detail::FormatError&)
			{}
		}
		m_Format.SetBufferCurrentPos(mainSubFormat);

		throw FormatNotFoundException();
		return Detail::FormatIndex();
	}

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	void BasicContext<CharFormat, ContextPackageSaving, Master>::ParseSpecial() {
			 if (m_Format.IsEqualTo('C') && m_Format.NextIsEqualForward(':', '}'))		{ ParseColor(); 	}
		else if (m_Format.IsEqualTo('S') && m_Format.NextIsEqualForward(':', '}'))		{ ParseStyle(); 	}
		else if (m_Format.IsEqualTo('F') && m_Format.NextIsEqualForward(':', '}'))		{ ParseFront(); 	}
		else if (m_Format.IsEqualTo('T') && m_Format.NextIsEqualForward(':', '}'))		{ ParseTimer(); 	}
		else if (m_Format.IsEqualTo('D') && m_Format.NextIsEqualForward(':', '}'))		{ ParseDate(); 		}
		else if (m_Format.IsEqualTo('K') && m_Format.NextIsEqualForward(':'))			{ ParseSetter();	}
	}

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	void BasicContext<CharFormat, ContextPackageSaving, Master>::ParseVariable(Detail::FormatIndex formatIdx) {
		FormatDataType saveFormatData = m_FormatData;
		m_FormatData = FormatDataType{};
		ContextPackageSaving savePackage = ContextStyleSave();

		if (!m_FormatData.IsInit)
			ParseFormatData();

		RunTypeAtIndex(formatIdx);

		ContextStyleRestore(savePackage);
		m_FormatData = saveFormatData;
	}

	template<typename CharFormat, typename ContextPackageSaving, typename Master>
	bool BasicContext<CharFormat, ContextPackageSaving, Master>::Parse() {
		m_Format.Forward();					// Skip {

		if (m_Format.IsUpperCase())
			ParseSpecial();
		else {
			Detail::FormatIndex formatIdx = GetFormatIndexThrow();
			ParseVariable(formatIdx);
		}

		m_Format.GoOutOfParameter();		// Skip}
		return true;
	}
}


