#pragma once

#include "StreamFormat/FMT/Detail/Prelude.h"
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

        std::expected<void, FMTResult> Terminate() { return ReloadDefault(); }

    public:
        template <typename T>
        requires Detail::TextPropertiesColorCanApply<T>
        std::expected<void, FMTResult> ApplyColor(const T& modif)
        {
            m_CurrentContextProperties.Color.Apply(modif);
            return m_TextPropertiesExecutor.ExecuteColor(modif);
        }
        template <typename T>
        requires Detail::TextPropertiesStyleCanApply<T>
        std::expected<void, FMTResult> ApplyStyle(const T& modif)
        {
            m_CurrentContextProperties.Style.Apply(modif);
            return m_TextPropertiesExecutor.ExecuteStyle(modif);
        }
        template <typename T>
        requires Detail::TextPropertiesFrontCanApply<T>
        std::expected<void, FMTResult> ApplyFront(const T& modif)
        {
            m_CurrentContextProperties.Front.Apply(modif);
            return m_TextPropertiesExecutor.ExecuteFront(modif);
        }

        std::expected<void, FMTResult> AllPropertiesReset()
        {
            SF_TRY(ApplyColorReset());
            SF_TRY(ApplyStyleReset());
            return ApplyFrontReset();
        }
        std::expected<void, FMTResult> ApplyColorReset()
        {
            m_CurrentContextProperties.Color.ModifyReset();
            return m_TextPropertiesExecutor.ResetColor();
        }
        std::expected<void, FMTResult> ApplyStyleReset()
        {
            m_CurrentContextProperties.Style.ModifyReset();
            return m_TextPropertiesExecutor.ResetStyle();
        }
        std::expected<void, FMTResult> ApplyFrontReset()
        {
            m_CurrentContextProperties.Front.ModifyReset();
            return m_TextPropertiesExecutor.ResetFront();
        }

    public:
        Detail::TextProperties::Properties Save() { return m_CurrentContextProperties; }

    public:
        std::expected<void, FMTResult> ReloadDefault()
        {
            ReloadDefaultColor();
            ReloadDefaultStyle();
            ReloadDefaultFront();
        }
        std::expected<void, FMTResult> ReloadDefaultColor()
        {
            ReloadDefaultColorFG();
            ReloadDefaultColorBG();
        }
        std::expected<void, FMTResult> ReloadDefaultColorFG() { ReloadColorFG(Detail::TextProperties::TextColor::ColorFG{}); }
        std::expected<void, FMTResult> ReloadDefaultColorBG() { ReloadColorBG(Detail::TextProperties::TextColor::ColorBG{}); }
        std::expected<void, FMTResult> ReloadDefaultStyle() { ReloadStyle(Detail::TextProperties::TextStyle::Style{}); }
        std::expected<void, FMTResult> ReloadDefaultFront() { ReloadFront(Detail::TextProperties::TextFront::Front{}); }

        std::expected<void, FMTResult> Reload(const Detail::TextProperties::Properties& target)
        {
            ReloadColor(target.Color);
            ReloadStyle(target.Style);
            ReloadFront(target.Front);
        }
        std::expected<void, FMTResult> ReloadColor(const Detail::TextProperties::TextColor::Color& target)
        {
            ReloadColorFG(target.Fg);
            ReloadColorBG(target.Bg);
        }

        std::expected<void, FMTResult> ReloadColorFG(const Detail::TextProperties::TextColor::ColorFG& target);
        std::expected<void, FMTResult> ReloadColorBG(const Detail::TextProperties::TextColor::ColorBG& target);
        std::expected<void, FMTResult> ReloadStyle(const Detail::TextProperties::TextStyle::Style& target);
        std::expected<void, FMTResult> ReloadFront(const Detail::TextProperties::TextFront::Front& target);

    public:
        ITextPropertiesExecutor&                    GetTextPropertiesExecutor() { return m_TextPropertiesExecutor; }
        Detail::TextProperties::Properties&         GetCurrentContextProperties() { return m_CurrentContextProperties; }

    protected:
        ITextPropertiesExecutor&                    m_TextPropertiesExecutor;
        Detail::TextProperties::Properties          m_CurrentContextProperties;

    public:
        template <typename T>
        requires Detail::TextPropertiesColorCanApply<T>
        inline std::expected<void, FMTResult> AskApplyColor(const T& modif)
        {
            if (m_CurrentContextProperties.Color.NeedModif(modif)) ApplyColor(modif);
        }
        template <typename T>
        requires Detail::TextPropertiesStyleCanApply<T>
        inline std::expected<void, FMTResult> AskApplyStyle(const T& modif)
        {
            if (m_CurrentContextProperties.Style.NeedModif(modif)) ApplyStyle(modif);
        }
        template <typename T>
        requires Detail::TextPropertiesFrontCanApply<T>
        inline std::expected<void, FMTResult> AskApplyFront(const T& modif)
        {
            if (m_CurrentContextProperties.Front.NeedModif(modif)) ApplyFront(modif);
        }

        std::expected<void, FMTResult> AskApplyColor(const Detail::TextProperties::TextColor::BasicColor& modif)
        {
            if (m_CurrentContextProperties.Color.NeedModif(modif.Fg))
            {
                if (m_CurrentContextProperties.Color.NeedModif(modif.Bg)) ApplyColor(modif);
                return ApplyColor(modif.Fg);
            }
            if (m_CurrentContextProperties.Color.NeedModif(modif.Fg)) return ApplyColor(modif.Bg);
        }

        std::expected<void, FMTResult> AskApplyColor(const Detail::TextProperties::TextColor::ColorCube& modif)
        {
            if (m_CurrentContextProperties.Color.NeedModif(modif.Fg))
            {
                if (m_CurrentContextProperties.Color.NeedModif(modif)) return ApplyColor(modif);
                return ApplyColor(modif.Fg);
            }
            if (m_CurrentContextProperties.Color.NeedModif(modif.Fg)) return ApplyColor(modif.Bg);
        }

        std::expected<void, FMTResult> AskApplyColor(const Detail::TextProperties::TextColor::Color24b& modif)
        {
            if (m_CurrentContextProperties.Color.NeedModif(modif.Fg))
            {
                if (m_CurrentContextProperties.Color.NeedModif(modif)) return ApplyColor(modif);
                return ApplyColor(modif.Fg);
            }
            if (m_CurrentContextProperties.Color.NeedModif(modif.Fg)) return ApplyColor(modif.Bg);
        }

        std::expected<void, FMTResult> AskApplyColor(const Detail::TextProperties::TextColor::ColorFG& modif) { ReloadColorFG(modif); }
        std::expected<void, FMTResult> AskApplyColor(const Detail::TextProperties::TextColor::ColorBG& modif) { ReloadColorBG(modif); }
        std::expected<void, FMTResult> AskApplyColor(const Detail::TextProperties::TextColor::Color& modif) { ReloadColor(modif); }
    };

    template <typename TChar>
    class TextPropertiesManager : public TextPropertiesApplyManager
    {
    public:
        TextPropertiesManager(ITextPropertiesExecutor& textPropertiesExecutor)
            : TextPropertiesApplyManager(textPropertiesExecutor)
        {}

    public:
        std::expected<void, FMTResult> ApplyColorOnIndex(Context::BasicContext<TChar>& context, std::int32_t index);
        std::expected<void, FMTResult> ApplyStyleOnIndex(Context::BasicContext<TChar>& context, std::int32_t index);
        std::expected<void, FMTResult> ApplyFrontOnIndex(Context::BasicContext<TChar>& context, std::int32_t index);

    public:
        std::expected<void, FMTResult> ParseColor(Context::BasicContext<TChar>& context);
        std::expected<void, FMTResult> ParseStyle(Context::BasicContext<TChar>& context);
        std::expected<void, FMTResult> ParseFront(Context::BasicContext<TChar>& context);

    private:
        template <typename T>
        std::expected<bool, FMTResult> GetColorCode(BufferInfoView<TChar>& format, T& t);
        std::expected<void, FMTResult> ParseStyleNamed(BufferInfoView<TChar>& format);
        std::expected<TextProperties::TextStyle::UnderlineColor::ColorCube, FMTResult> SelectUnderlinedColorStyle(BufferInfoView<TChar>& format);
    };
}

namespace StreamFormat::FMT::Detail
{
    template <typename TChar>
    template <typename T>
    std::expected<T, FMTResult> Detail::TextPropertiesManager<TChar>::GetColorCode(BufferInfoView<TChar>& format)
    {
        static constexpr std::string_view colorCode[] = {"black", "red", "green", "yellow", "blue", "magenta", "cyan", "white", "      ", "default"};

        bool bright = SF_TRY(BufferTestManip(format).IsEqualToForward('+'));
        std::uint8_t step = static_cast<std::uint8_t>(bright ? T::BaseBStep : T::BaseStep);
        std::uint8_t code = (std::uint8_t)SF_TRY(BufferUtilsManip(format).GetWordFromList(colorCode));;
        t = static_cast<T>(code + step);
        return true;
    }
}

#include "TextPropertiesManager-impl.h"
