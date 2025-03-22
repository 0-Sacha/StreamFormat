#pragma once

#include "stream/fmt/detail/prelude.h"
#include "text_properties_executor.h"
#include "basic_args_interface.h"
#include "stream/fmt/buffer/buffer_info.h"
#include "stream/fmt/buffer/buffer_test_manip.h"
#include "stream/fmt/buffer/utils/buffer_utils.h"

namespace stream::fmt::detail
{
    class TextPropertiesApplyManager
    {
    public:
        TextPropertiesApplyManager(ITextPropertiesExecutor& textPropertiesExecutor)
            : m_TextPropertiesExecutor{textPropertiesExecutor}
            , m_CurrentContextProperties{}
        {}

        [[nodiscard]] std::expected<void, FMTResult> Terminate() { return ReloadDefault(); }

    public:
        template <typename T>
        requires detail::TextPropertiesColorCanApply<T>
        [[nodiscard]] std::expected<void, FMTResult> ApplyColor(const T& modif)
        {
            m_CurrentContextProperties.color.Apply(modif);
            return m_TextPropertiesExecutor.execute_color(modif);
        }
        template <typename T>
        requires detail::TextPropertiesStyleCanApply<T>
        [[nodiscard]] std::expected<void, FMTResult> ApplyStyle(const T& modif)
        {
            m_CurrentContextProperties.style.Apply(modif);
            return m_TextPropertiesExecutor.execute_style(modif);
        }
        template <typename T>
        requires detail::TextPropertiesFrontCanApply<T>
        [[nodiscard]] std::expected<void, FMTResult> ApplyFront(const T& modif)
        {
            m_CurrentContextProperties.front.Apply(modif);
            return m_TextPropertiesExecutor.ExecuteFront(modif);
        }

        [[nodiscard]] std::expected<void, FMTResult> all_properties_reset()
        {
            SF_TRY(ApplyColorReset());
            SF_TRY(ApplyStyleReset());
            return ApplyFrontReset();
        }
        [[nodiscard]] std::expected<void, FMTResult> ApplyColorReset()
        {
            m_CurrentContextProperties.color.ModifyReset();
            return m_TextPropertiesExecutor.reset_color();
        }
        [[nodiscard]] std::expected<void, FMTResult> ApplyStyleReset()
        {
            m_CurrentContextProperties.style.ModifyReset();
            return m_TextPropertiesExecutor.ResetStyle();
        }
        [[nodiscard]] std::expected<void, FMTResult> ApplyFrontReset()
        {
            m_CurrentContextProperties.front.ModifyReset();
            return m_TextPropertiesExecutor.reset_front();
        }

    public:
        detail::TextProperties::Properties Save() { return m_CurrentContextProperties; }

    public:
        [[nodiscard]] std::expected<void, FMTResult> ReloadDefault()
        {
            SF_TRY(ReloadDefaultColor());
            SF_TRY(ReloadDefaultStyle());
            return ReloadDefaultFront();
        }
        [[nodiscard]] std::expected<void, FMTResult> ReloadDefaultColor()
        {
            SF_TRY(ReloadDefaultColorFG());
            return ReloadDefaultColorBG();
        }
        [[nodiscard]] std::expected<void, FMTResult> ReloadDefaultColorFG() { return ReloadColorFG(detail::TextProperties::TextColor::ColorFG{}); }
        [[nodiscard]] std::expected<void, FMTResult> ReloadDefaultColorBG() { return ReloadColorBG(detail::TextProperties::TextColor::ColorBG{}); }
        [[nodiscard]] std::expected<void, FMTResult> ReloadDefaultStyle() { return ReloadStyle(detail::TextProperties::TextStyle::Style{}); }
        [[nodiscard]] std::expected<void, FMTResult> ReloadDefaultFront() { return ReloadFront(detail::TextProperties::TextFront::Front{}); }

        [[nodiscard]] std::expected<void, FMTResult> Reload(const detail::TextProperties::Properties& target)
        {
            SF_TRY(ReloadColor(target.color));
            SF_TRY(ReloadStyle(target.style));
            return ReloadFront(target.front);
        }
        [[nodiscard]] std::expected<void, FMTResult> ReloadColor(const detail::TextProperties::TextColor::Color& target)
        {
            SF_TRY(ReloadColorFG(target.Fg));
            return ReloadColorBG(target.Bg);
        }

        [[nodiscard]] std::expected<void, FMTResult> ReloadColorFG(const detail::TextProperties::TextColor::ColorFG& target);
        [[nodiscard]] std::expected<void, FMTResult> ReloadColorBG(const detail::TextProperties::TextColor::ColorBG& target);
        [[nodiscard]] std::expected<void, FMTResult> ReloadStyle(const detail::TextProperties::TextStyle::Style& target);
        [[nodiscard]] std::expected<void, FMTResult> ReloadFront(const detail::TextProperties::TextFront::Front& target);

    public:
        ITextPropertiesExecutor&                    GetTextPropertiesExecutor() { return m_TextPropertiesExecutor; }
        detail::TextProperties::Properties&         GetCurrentContextProperties() { return m_CurrentContextProperties; }

    protected:
        ITextPropertiesExecutor&                    m_TextPropertiesExecutor;
        detail::TextProperties::Properties          m_CurrentContextProperties;

    public:
        template <typename T>
        requires detail::TextPropertiesColorCanApply<T>
        [[nodiscard]] inline std::expected<void, FMTResult> AskApplyColor(const T& modif)
        {
            if (m_CurrentContextProperties.color.NeedModif(modif))
                return ApplyColor(modif);
            return {};
        }
        template <typename T>
        requires detail::TextPropertiesStyleCanApply<T>
        [[nodiscard]] inline std::expected<void, FMTResult> AskApplyStyle(const T& modif)
        {
            if (m_CurrentContextProperties.style.NeedModif(modif))
                return ApplyStyle(modif);
            return {};
        }
        template <typename T>
        requires detail::TextPropertiesFrontCanApply<T>
        [[nodiscard]] inline std::expected<void, FMTResult> AskApplyFront(const T& modif)
        {
            if (m_CurrentContextProperties.front.NeedModif(modif))
                return ApplyFront(modif);
            return {};
        }

        [[nodiscard]] std::expected<void, FMTResult> AskApplyColor(const detail::TextProperties::TextColor::BasicColor& modif)
        {
            if (m_CurrentContextProperties.color.NeedModif(modif.Fg))
            {
                if (m_CurrentContextProperties.color.NeedModif(modif.Bg))
                    return ApplyColor(modif);
                return ApplyColor(modif.Fg);
            }
            if (m_CurrentContextProperties.color.NeedModif(modif.Fg))
                return ApplyColor(modif.Bg);

            return {};
        }

        [[nodiscard]] std::expected<void, FMTResult> AskApplyColor(const detail::TextProperties::TextColor::ColorCube& modif)
        {
            if (m_CurrentContextProperties.color.NeedModif(modif.Fg))
            {
                if (m_CurrentContextProperties.color.NeedModif(modif))
                    return ApplyColor(modif);
                return ApplyColor(modif.Fg);
            }
            if (m_CurrentContextProperties.color.NeedModif(modif.Fg))
                return ApplyColor(modif.Bg);

            return {};
        }

        [[nodiscard]] std::expected<void, FMTResult> AskApplyColor(const detail::TextProperties::TextColor::Color24b& modif)
        {
            if (m_CurrentContextProperties.color.NeedModif(modif.Fg))
            {
                if (m_CurrentContextProperties.color.NeedModif(modif))
                    return ApplyColor(modif);
                return ApplyColor(modif.Fg);
            }
            if (m_CurrentContextProperties.color.NeedModif(modif.Fg))
                return ApplyColor(modif.Bg);

            return {};
        }

        [[nodiscard]] std::expected<void, FMTResult> AskApplyColor(const detail::TextProperties::TextColor::ColorFG& modif) { return ReloadColorFG(modif); }
        [[nodiscard]] std::expected<void, FMTResult> AskApplyColor(const detail::TextProperties::TextColor::ColorBG& modif) { return ReloadColorBG(modif); }
        [[nodiscard]] std::expected<void, FMTResult> AskApplyColor(const detail::TextProperties::TextColor::Color& modif) { return ReloadColor(modif); }
    };

    template <typename TChar>
    class TextPropertiesManager : public TextPropertiesApplyManager
    {
    public:
        TextPropertiesManager(ITextPropertiesExecutor& textPropertiesExecutor)
            : TextPropertiesApplyManager(textPropertiesExecutor)
        {}

    public:
        [[nodiscard]] std::expected<void, FMTResult> ApplyColorOnIndex(Context::BasicContext<TChar>& context, std::int32_t index);
        [[nodiscard]] std::expected<void, FMTResult> ApplyStyleOnIndex(Context::BasicContext<TChar>& context, std::int32_t index);
        [[nodiscard]] std::expected<void, FMTResult> ApplyFrontOnIndex(Context::BasicContext<TChar>& context, std::int32_t index);

    public:
        [[nodiscard]] std::expected<void, FMTResult> ParseColor(Context::BasicContext<TChar>& context);
        [[nodiscard]] std::expected<void, FMTResult> ParseStyle(Context::BasicContext<TChar>& context);
        [[nodiscard]] std::expected<void, FMTResult> ParseFront(Context::BasicContext<TChar>& context);

    private:
        template <typename T>
        [[nodiscard]] std::expected<T, FMTResult> GetColorCode(BufferInfoView<TChar>& format);
        [[nodiscard]] std::expected<void, FMTResult> ParseStyleNamed(BufferInfoView<TChar>& format);
        [[nodiscard]] std::expected<TextProperties::TextStyle::UnderlineColor::ColorCube, FMTResult> SelectUnderlinedColorStyle(BufferInfoView<TChar>& format);
    };
}

namespace stream::fmt::detail
{
    template <typename TChar>
    template <typename T>
    [[nodiscard]] std::expected<T, FMTResult> detail::TextPropertiesManager<TChar>::GetColorCode(BufferInfoView<TChar>& format)
    {
        static constexpr std::string_view colorCode[] = {"black", "red", "green", "yellow", "blue", "magenta", "cyan", "white", "      ", "default"};

        bool bright = SF_TRY(BufferTestManip(format).IsEqualToForward('+'));
        std::uint8_t step = static_cast<std::uint8_t>(bright ? T::BaseBStep : T::BaseStep);
        std::uint8_t code = (std::uint8_t)SF_TRY(BufferUtilsManip(format).get_word_from_list(colorCode));;
        return static_cast<T>(code + step);
    }
}

#include "TextPropertiesManager-impl.h"
