#pragma once

#include "ProjectCore/FMT/Detail/Detail.h"
#include "ITextPropertiesExecutor.h"

namespace ProjectCore::FMT::Detail
{
	template <typename BasicContext>
	class BasicTextPropertiesParser
	{
	public:
		BasicTextPropertiesParser(BasicContext& context, ITextPropertiesExecutor& textPropertiesExecutor, const TextProperties::Properties* baseContextProperties)
			: m_Context{context}
			, m_TextPropertiesExecutor{textPropertiesExecutor}
			, m_BaseContextProperties{baseContextProperties}
			, m_CurrentContextProperties{baseContextProperties == nullptr ? TextProperties::Properties{} : *baseContextProperties}
		{}

		void Terminate()
		{
			ReloadDefault();
		}

	public:
		template <typename T>
		void ColorModif(const T& modif)
		{
			m_CurrentContextProperties.Color.ModifyThrow(modif);
			m_TextPropertiesExecutor.ExecuteColor(modif);
		}
		template <typename T>
		void StyleModif(const T& modif)
		{
			m_CurrentContextProperties.Style.ModifyThrow(modif);
			m_TextPropertiesExecutor.ExecuteStyle(modif);
		}
		template <typename T>
		void FrontModif(const T& modif)
		{
			m_CurrentContextProperties.Front.ModifyThrow(modif);
			m_TextPropertiesExecutor.ExecuteFront(modif);
		}

		void AllPropertiesReset()
		{
			ColorModifReset();
			StyleModifReset();
			FrontModifReset();
		}
		void ColorModifReset()
		{
			m_CurrentContextProperties.Color.ModifyReset();
			m_TextPropertiesExecutor.ResetColor();
		}
		void StyleModifReset()
		{
			m_CurrentContextProperties.Style.ModifyReset();
			m_TextPropertiesExecutor.ResetStyle();
		}
		void FrontModifReset()
		{
			m_CurrentContextProperties.Front.ModifyReset();
			m_TextPropertiesExecutor.ResetFront();
		}

	public:
		void ColorExecuteOnIndex(const FormatIndex& index);
		void StyleExecuteOnIndex(const FormatIndex& index);
		void FrontExecuteOnIndex(const FormatIndex& index);

	public:
		void ParseColor();
		template <typename T>
		bool GetColorCode(T& t);

		void ParseStyle();
		TextProperties::TextStyle::BasicStyle GetStyleCode();
		TextProperties::TextStyle::UnderlineColor::ColorCube SelectUnderlinedColorStyle();

		void ParseFront();

	public:
		TextProperties::Properties Save() 									{ return m_CurrentContextProperties; }

	public:
		void ReloadDefault() 												{ ReloadDefaultColor(); ReloadDefaultStyle(); ReloadDefaultFront(); }
		void ReloadDefaultColor() 											{ ReloadDefaultColorFG(); ReloadDefaultColorBG(); }
		void ReloadDefaultColorFG() 										{ if (m_BaseContextProperties != nullptr) return ReloadColorFG(m_BaseContextProperties->Color.Fg); 	return ReloadColorFG(TextProperties::TextColor::ColorFG{}); }
		void ReloadDefaultColorBG() 										{ if (m_BaseContextProperties != nullptr) return ReloadColorBG(m_BaseContextProperties->Color.Bg); 	return ReloadColorBG(TextProperties::TextColor::ColorBG{}); }
		void ReloadDefaultStyle() 											{ if (m_BaseContextProperties != nullptr) return ReloadStyle(m_BaseContextProperties->Style); 		return ReloadStyle(TextProperties::TextStyle::Style{}); }
		void ReloadDefaultFront() 											{ if (m_BaseContextProperties != nullptr) return ReloadFront(m_BaseContextProperties->Front); 		return ReloadFront(TextProperties::TextFront::Front{}); }

		void Reload(const TextProperties::Properties& target) 				{ ReloadColor(target.Color); ReloadStyle(target.Style); ReloadFront(target.Front); }
		void ReloadColor(const TextProperties::TextColor::Color& target) 	{ ReloadColorFG(target.Fg); ReloadColorBG(target.Bg); }
		void ReloadColorFG(const TextProperties::TextColor::ColorFG& target);
		void ReloadColorBG(const TextProperties::TextColor::ColorBG& target);
		void ReloadStyle(const TextProperties::TextStyle::Style& target);
		void ReloadFront(const TextProperties::TextFront::Front& target);

	public:
		ITextPropertiesExecutor& 			GetTextPropertiesExecutor() { return m_TextPropertiesExecutor; }
		const TextProperties::Properties* 	GetBaseContextProperties() { return m_BaseContextProperties; }
		TextProperties::Properties& 		GetCurrentContextProperties() { return m_CurrentContextProperties; }

	private:
		BasicContext& 						m_Context;
		ITextPropertiesExecutor& 			m_TextPropertiesExecutor;
		const TextProperties::Properties* 	m_BaseContextProperties;
		TextProperties::Properties 			m_CurrentContextProperties;
	};
}
