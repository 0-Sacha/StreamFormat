#pragma once

#include "ProjectCore/FMT/Detail/Detail.h"
#include "ITextPropertiesExecutor.h"

namespace ProjectCore::FMT::Detail
{
    class TextPropertiesApplyManager
    {
    public:
        TextPropertiesApplyManager(ITextPropertiesExecutor& textPropertiesExecutor, const TextProperties::Properties* baseContextProperties)
            : m_TextPropertiesExecutor{textPropertiesExecutor}
            , m_BaseContextProperties{baseContextProperties}
            , m_CurrentContextProperties{baseContextProperties == nullptr ? TextProperties::Properties{} : *baseContextProperties}
        {}

        void Terminate()
        {
            ReloadDefault();
        }

    public:
        template <typename T>
        requires TextPropertiesColorCanApply<T>
        void ApplyColor(const T& modif)
        {
            m_CurrentContextProperties.Color.Apply(modif);
            m_TextPropertiesExecutor.ExecuteColor(modif);
        }
        template <typename T>
        requires TextPropertiesStyleCanApply<T>
        void ApplyStyle(const T& modif)
        {
            m_CurrentContextProperties.Style.Apply(modif);
            m_TextPropertiesExecutor.ExecuteStyle(modif);
        }
        template <typename T>
        requires TextPropertiesFrontCanApply<T>
        void ApplyFront(const T& modif)
        {
            m_CurrentContextProperties.Front.Apply(modif);
            m_TextPropertiesExecutor.ExecuteFront(modif);
        }

        void AllPropertiesReset()
        {
            ApplyColorReset();
            ApplyStyleReset();
            ApplyFrontReset();
        }
        void ApplyColorReset()
        {
            m_CurrentContextProperties.Color.ModifyReset();
            m_TextPropertiesExecutor.ResetColor();
        }
        void ApplyStyleReset()
        {
            m_CurrentContextProperties.Style.ModifyReset();
            m_TextPropertiesExecutor.ResetStyle();
        }
        void ApplyFrontReset()
        {
            m_CurrentContextProperties.Front.ModifyReset();
            m_TextPropertiesExecutor.ResetFront();
        }

    public:
        TextProperties::Properties Save() { return m_CurrentContextProperties; }

    public:
        void ReloadDefault()        { ReloadDefaultColor(); ReloadDefaultStyle(); ReloadDefaultFront(); }
        void ReloadDefaultColor()   { ReloadDefaultColorFG(); ReloadDefaultColorBG(); }
        void ReloadDefaultColorFG() { m_BaseContextProperties != nullptr ? ReloadColorFG(m_BaseContextProperties->Color.Fg) : ReloadColorFG(TextProperties::TextColor::ColorFG{}); }
        void ReloadDefaultColorBG() { m_BaseContextProperties != nullptr ? ReloadColorBG(m_BaseContextProperties->Color.Bg) : ReloadColorBG(TextProperties::TextColor::ColorBG{}); }
        void ReloadDefaultStyle()   { m_BaseContextProperties != nullptr ? ReloadStyle(m_BaseContextProperties->Style)      : ReloadStyle(TextProperties::TextStyle::Style{}); }
        void ReloadDefaultFront()   { m_BaseContextProperties != nullptr ? ReloadFront(m_BaseContextProperties->Front)      : ReloadFront(TextProperties::TextFront::Front{}); }

        void Reload(const TextProperties::Properties& target)               { ReloadColor(target.Color); ReloadStyle(target.Style); ReloadFront(target.Front); }
        void ReloadColor(const TextProperties::TextColor::Color& target)    { ReloadColorFG(target.Fg); ReloadColorBG(target.Bg); }

        void ReloadColorFG(const TextProperties::TextColor::ColorFG& target);
        void ReloadColorBG(const TextProperties::TextColor::ColorBG& target);
        void ReloadStyle(const TextProperties::TextStyle::Style& target);
        void ReloadFront(const TextProperties::TextFront::Front& target);

    public:
        ITextPropertiesExecutor&            GetTextPropertiesExecutor()     { return m_TextPropertiesExecutor; }
        const TextProperties::Properties*   GetBaseContextProperties()      { return m_BaseContextProperties; }
        TextProperties::Properties&         GetCurrentContextProperties()   { return m_CurrentContextProperties; }

    protected:
        ITextPropertiesExecutor&            m_TextPropertiesExecutor;
        const TextProperties::Properties*   m_BaseContextProperties;
        TextProperties::Properties          m_CurrentContextProperties;
    
    public:
        template <typename T>
        requires TextPropertiesColorCanApply<T>
        inline void AskApplyColor(const T& modif) { if (m_CurrentContextProperties.Color.NeedModif(modif)) ApplyColor(modif); }
        template <typename T>
        requires TextPropertiesStyleCanApply<T>
        inline void AskApplyStyle(const T& modif) { if (m_CurrentContextProperties.Style.NeedModif(modif)) ApplyStyle(modif); }
        template <typename T>
        requires TextPropertiesFrontCanApply<T>
        inline void AskApplyFront(const T& modif) { if (m_CurrentContextProperties.Front.NeedModif(modif)) ApplyFront(modif); }

        void AskApplyColor(const TextProperties::TextColor::BasicColor& modif)
        {
            if (m_CurrentContextProperties.Color.NeedModif(modif.Fg))
            {
                if (m_CurrentContextProperties.Color.NeedModif(modif.Bg))
                    ApplyColor(modif);
                return ApplyColor(modif.Fg);
            }
            if (m_CurrentContextProperties.Color.NeedModif(modif.Fg))
                return ApplyColor(modif.Bg);
        }

        void AskApplyColor(const TextProperties::TextColor::ColorCube& modif)
        {
            if (m_CurrentContextProperties.Color.NeedModif(modif.Fg))
            {
                if (m_CurrentContextProperties.Color.NeedModif(modif))
                    return ApplyColor(modif);
                return ApplyColor(modif.Fg);
            }
            if (m_CurrentContextProperties.Color.NeedModif(modif.Fg))
                return ApplyColor(modif.Bg);
        }

        void AskApplyColor(const TextProperties::TextColor::Color24b& modif)
        {
            if (m_CurrentContextProperties.Color.NeedModif(modif.Fg))
            {
                if (m_CurrentContextProperties.Color.NeedModif(modif))
                    return ApplyColor(modif);
                return ApplyColor(modif.Fg);
            }
            if (m_CurrentContextProperties.Color.NeedModif(modif.Fg))
                return ApplyColor(modif.Bg);
        }

        void AskApplyColor(const TextProperties::TextColor::ColorFG& modif)
        {
            ReloadColorFG(modif);
        }
        void AskApplyColor(const TextProperties::TextColor::ColorBG& modif)
        {
            ReloadColorBG(modif);
        }
        void AskApplyColor(const TextProperties::TextColor::Color& modif)
        {
            ReloadColor(modif);
        }
    };

    template <typename Context>
    class TextPropertiesManager : public TextPropertiesApplyManager
    {
    public:
        TextPropertiesManager(Context& context, ITextPropertiesExecutor& textPropertiesExecutor, const TextProperties::Properties* baseContextProperties)
            : m_Context{context}
            , TextPropertiesApplyManager(textPropertiesExecutor, baseContextProperties)
        {}

    public:
        void ApplyColorOnIndex(const FormatIndex& index);
        void ApplyStyleOnIndex(const FormatIndex& index);
        void ApplyFrontOnIndex(const FormatIndex& index);

    public:
        void ParseColor();
        template <typename T>
        bool GetColorCode(T& t);

        void ParseStyle();
        void ParseStyleNamed();
        TextProperties::TextStyle::UnderlineColor::ColorCube SelectUnderlinedColorStyle();

        void ParseFront();

    private:
        Context& m_Context;
    };
}
