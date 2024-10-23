#pragma once

#include "StreamFormat/FMT/Detail/Detail.h"
#include "ITextPropertiesExecutor.h"
#include "BasicArgsInterface.h"
#include "StreamFormat/FMT/Buffer/BufferInfo.h"
#include "StreamFormat/FMT/Buffer/BufferTestManip.h"
#include "StreamFormat/FMT/Buffer/Utils/BufferUtils.h"

namespace StreamFormat::FMT::Detail
{
    class TextPropertiesApplyManager
    {
    public:
        TextPropertiesApplyManager(ITextPropertiesExecutor& textPropertiesExecutor)
            : m_TextPropertiesExecutor{textPropertiesExecutor}
            , m_CurrentContextProperties{}
        {}

        void Terminate() { ReloadDefault(); }

    public:
        template <typename T>
        requires Detail::TextPropertiesColorCanApply<T>
        void ApplyColor(const T& modif)
        {
            m_CurrentContextProperties.Color.Apply(modif);
            m_TextPropertiesExecutor.ExecuteColor(modif);
        }
        template <typename T>
        requires Detail::TextPropertiesStyleCanApply<T>
        void ApplyStyle(const T& modif)
        {
            m_CurrentContextProperties.Style.Apply(modif);
            m_TextPropertiesExecutor.ExecuteStyle(modif);
        }
        template <typename T>
        requires Detail::TextPropertiesFrontCanApply<T>
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
        Detail::TextProperties::Properties Save() { return m_CurrentContextProperties; }

    public:
        void ReloadDefault()
        {
            ReloadDefaultColor();
            ReloadDefaultStyle();
            ReloadDefaultFront();
        }
        void ReloadDefaultColor()
        {
            ReloadDefaultColorFG();
            ReloadDefaultColorBG();
        }
        void ReloadDefaultColorFG() { ReloadColorFG(Detail::TextProperties::TextColor::ColorFG{}); }
        void ReloadDefaultColorBG() { ReloadColorBG(Detail::TextProperties::TextColor::ColorBG{}); }
        void ReloadDefaultStyle() { ReloadStyle(Detail::TextProperties::TextStyle::Style{}); }
        void ReloadDefaultFront() { ReloadFront(Detail::TextProperties::TextFront::Front{}); }

        void Reload(const Detail::TextProperties::Properties& target)
        {
            ReloadColor(target.Color);
            ReloadStyle(target.Style);
            ReloadFront(target.Front);
        }
        void ReloadColor(const Detail::TextProperties::TextColor::Color& target)
        {
            ReloadColorFG(target.Fg);
            ReloadColorBG(target.Bg);
        }

        void ReloadColorFG(const Detail::TextProperties::TextColor::ColorFG& target);
        void ReloadColorBG(const Detail::TextProperties::TextColor::ColorBG& target);
        void ReloadStyle(const Detail::TextProperties::TextStyle::Style& target);
        void ReloadFront(const Detail::TextProperties::TextFront::Front& target);

    public:
        ITextPropertiesExecutor&                    GetTextPropertiesExecutor() { return m_TextPropertiesExecutor; }
        Detail::TextProperties::Properties&         GetCurrentContextProperties() { return m_CurrentContextProperties; }

    protected:
        ITextPropertiesExecutor&                    m_TextPropertiesExecutor;
        Detail::TextProperties::Properties          m_CurrentContextProperties;

    public:
        template <typename T>
        requires Detail::TextPropertiesColorCanApply<T>
        inline void AskApplyColor(const T& modif)
        {
            if (m_CurrentContextProperties.Color.NeedModif(modif)) ApplyColor(modif);
        }
        template <typename T>
        requires Detail::TextPropertiesStyleCanApply<T>
        inline void AskApplyStyle(const T& modif)
        {
            if (m_CurrentContextProperties.Style.NeedModif(modif)) ApplyStyle(modif);
        }
        template <typename T>
        requires Detail::TextPropertiesFrontCanApply<T>
        inline void AskApplyFront(const T& modif)
        {
            if (m_CurrentContextProperties.Front.NeedModif(modif)) ApplyFront(modif);
        }

        void AskApplyColor(const Detail::TextProperties::TextColor::BasicColor& modif)
        {
            if (m_CurrentContextProperties.Color.NeedModif(modif.Fg))
            {
                if (m_CurrentContextProperties.Color.NeedModif(modif.Bg)) ApplyColor(modif);
                return ApplyColor(modif.Fg);
            }
            if (m_CurrentContextProperties.Color.NeedModif(modif.Fg)) return ApplyColor(modif.Bg);
        }

        void AskApplyColor(const Detail::TextProperties::TextColor::ColorCube& modif)
        {
            if (m_CurrentContextProperties.Color.NeedModif(modif.Fg))
            {
                if (m_CurrentContextProperties.Color.NeedModif(modif)) return ApplyColor(modif);
                return ApplyColor(modif.Fg);
            }
            if (m_CurrentContextProperties.Color.NeedModif(modif.Fg)) return ApplyColor(modif.Bg);
        }

        void AskApplyColor(const Detail::TextProperties::TextColor::Color24b& modif)
        {
            if (m_CurrentContextProperties.Color.NeedModif(modif.Fg))
            {
                if (m_CurrentContextProperties.Color.NeedModif(modif)) return ApplyColor(modif);
                return ApplyColor(modif.Fg);
            }
            if (m_CurrentContextProperties.Color.NeedModif(modif.Fg)) return ApplyColor(modif.Bg);
        }

        void AskApplyColor(const Detail::TextProperties::TextColor::ColorFG& modif) { ReloadColorFG(modif); }
        void AskApplyColor(const Detail::TextProperties::TextColor::ColorBG& modif) { ReloadColorBG(modif); }
        void AskApplyColor(const Detail::TextProperties::TextColor::Color& modif) { ReloadColor(modif); }
    };

    template <typename TChar>
    class TextPropertiesManager : public TextPropertiesApplyManager
    {
    public:
        TextPropertiesManager(ITextPropertiesExecutor& textPropertiesExecutor)
            : TextPropertiesApplyManager(textPropertiesExecutor)
        {}

    public:
        void ApplyColorOnIndex(Context::BasicContext<TChar>& context, std::int32_t index);
        void ApplyStyleOnIndex(Context::BasicContext<TChar>& context, std::int32_t index);
        void ApplyFrontOnIndex(Context::BasicContext<TChar>& context, std::int32_t index);

    public:
        void ParseColor(Context::BasicContext<TChar>& context);
        void ParseStyle(Context::BasicContext<TChar>& context);
        void ParseFront(Context::BasicContext<TChar>& context);

    private:
        template <typename T>
        bool GetColorCode(BufferInfoView<TChar>& format, T& t);
        void ParseStyleNamed(BufferInfoView<TChar>& format);
        Detail::TextProperties::TextStyle::UnderlineColor::ColorCube SelectUnderlinedColorStyle(BufferInfoView<TChar>& format);
    };
}

namespace StreamFormat::FMT::Detail
{
    template <typename TChar>
    template <typename T>
    bool Detail::TextPropertiesManager<TChar>::GetColorCode(BufferInfoView<TChar>& format, T& t)
    {
        static constexpr std::string_view colorCode[] = {"black", "red", "green", "yellow", "blue", "magenta", "cyan", "white", "      ", "default"};

        std::uint8_t step = static_cast<std::uint8_t>(BufferTestManip(format).IsEqualToForward('+') ? T::BaseBStep : T::BaseStep);
        std::uint8_t code = static_cast<std::uint8_t>(BufferUtilsManip(format).GetWordFromList(colorCode));
        if (code == BufferUtilsManip<TChar>::GET_WORD_FROM_LIST_NOT_FOUND) return false;
        t = static_cast<T>(code + step);
        return true;
    }
}

#include "TextPropertiesManager-impl.h"
