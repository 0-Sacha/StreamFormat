#include "text_properties_manager.hxx"

namespace stream::fmt::detail {
    void TextPropertiesapplyManager::reload_color_fg(const TextProperties::TextColor::ColorFG& target) {
        if (target.type != current_context_properties_.color.fg.type) {
            switch (target.type) {
                case TextProperties::TextColor::ColorType::BasicColor: {
                    apply_color(target.data.basic_color);
                    return;
                }
                case TextProperties::TextColor::ColorType::ColorCube: {
                    apply_color(target.data.color_cube);
                    return;
                }
                case TextProperties::TextColor::ColorType::Color24b: {
                    apply_color(target.data.color24b);
                    return;
                }
            }
        } else {
            switch (target.type) {
                case TextProperties::TextColor::ColorType::BasicColor:
                    if (current_context_properties_.color.fg.data.basic_color != target.data.basic_color) {
                        {
                            apply_color(target.data.basic_color);
                        }
                        return;
                    }
                    break;
                case TextProperties::TextColor::ColorType::ColorCube:
                    if (current_context_properties_.color.fg.data.color_cube != target.data.color_cube) {
                        {
                            apply_color(target.data.color_cube);
                        }
                        return;
                    }
                    break;
                case TextProperties::TextColor::ColorType::Color24b:
                    if (current_context_properties_.color.fg.data.color24b != target.data.color24b) {
                        {
                            apply_color(target.data.color24b);
                        }
                        return;
                    }
                    break;
            }
        }
    }

    void TextPropertiesapplyManager::reload_color_bg(const TextProperties::TextColor::ColorBG& target) {
        if (target.type != current_context_properties_.color.bg.type) {
            switch (target.type) {
                case TextProperties::TextColor::ColorType::BasicColor: {
                    apply_color(target.data.basic_color);
                    return;
                }
                case TextProperties::TextColor::ColorType::ColorCube: {
                    apply_color(target.data.color_cube);
                    return;
                }
                case TextProperties::TextColor::ColorType::Color24b: {
                    apply_color(target.data.color24b);
                    return;
                }
            }
        } else {
            switch (target.type) {
                case TextProperties::TextColor::ColorType::BasicColor:
                    if (current_context_properties_.color.bg.data.basic_color != target.data.basic_color) {
                        {
                            apply_color(target.data.basic_color);
                        }
                        return;
                    }
                    break;
                case TextProperties::TextColor::ColorType::ColorCube:
                    if (current_context_properties_.color.bg.data.color_cube != target.data.color_cube) {
                        {
                            apply_color(target.data.color_cube);
                        }
                        return;
                    }
                    break;
                case TextProperties::TextColor::ColorType::Color24b:
                    if (current_context_properties_.color.bg.data.color24b != target.data.color24b) {
                        {
                            apply_color(target.data.color24b);
                        }
                        return;
                    }
                    break;
            }
        }
    }

    // NOLINTBEGIN(readability-function-cognitive-complexity)
    void TextPropertiesapplyManager::reload_style(const TextProperties::TextStyle::Style& target) {
        if (target.intensity != current_context_properties_.style.intensity) {
            apply_style(target.intensity);
            current_context_properties_.style.intensity = target.intensity;
        }
        if (target.italic != current_context_properties_.style.italic) {
            apply_style(target.italic);
            current_context_properties_.style.italic = target.italic;
        }
        if (target.blink != current_context_properties_.style.blink) {
            apply_style(target.blink);
            current_context_properties_.style.blink = target.blink;
        }
        if (target.inverted != current_context_properties_.style.inverted) {
            apply_style(target.inverted);
            current_context_properties_.style.inverted = target.inverted;
        }
        if (target.ideogram != current_context_properties_.style.ideogram) {
            apply_style(target.ideogram);
            current_context_properties_.style.ideogram = target.ideogram;
        }
        if (target.script != current_context_properties_.style.script) {
            apply_style(target.script);
            current_context_properties_.style.script = target.script;
        }

        if (target.underline != current_context_properties_.style.underline) {
            apply_style(target.underline);
            current_context_properties_.style.underline = target.underline;
        }

        if (target.underline_color.type != current_context_properties_.style.underline_color.type) {
            switch (target.underline_color.type) {
                case TextProperties::TextStyle::UnderlineColor::ColorType::Default:
                    apply_style(TextProperties::TextStyle::UnderlineColor::ColorCube{TextProperties::TextStyle::UnderlineColor::ColorCube::Default});
                    break;
                case TextProperties::TextStyle::UnderlineColor::ColorType::ColorCube:
                    apply_style(target.underline_color.data.color_cube);
                    current_context_properties_.style.underline_color.data.color_cube = target.underline_color.data.color_cube;
                    break;
                case TextProperties::TextStyle::UnderlineColor::ColorType::Color24b:
                    apply_style(target.underline_color.data.color24b);
                    current_context_properties_.style.underline_color.data.color24b = target.underline_color.data.color24b;
                    break;
            }
            current_context_properties_.style.underline_color.type = target.underline_color.type;
        } else {
            switch (target.underline_color.type) {
                case TextProperties::TextStyle::UnderlineColor::ColorType::Default:
                    break;
                case TextProperties::TextStyle::UnderlineColor::ColorType::ColorCube:
                    if (current_context_properties_.style.underline_color.data.color_cube != target.underline_color.data.color_cube) {
                        apply_style(target.underline_color.data.color_cube);
                        current_context_properties_.style.underline_color.data.color_cube = target.underline_color.data.color_cube;
                    }
                    break;
                case TextProperties::TextStyle::UnderlineColor::ColorType::Color24b:
                    if (current_context_properties_.style.underline_color.data.color24b != target.underline_color.data.color24b) {
                        apply_style(target.underline_color.data.color24b);
                        current_context_properties_.style.underline_color.data.color24b = target.underline_color.data.color24b;
                    }
                    break;
            }
        }
    }
    // NOLINTEND(readability-function-cognitive-complexity)

    void TextPropertiesapplyManager::reload_front(const TextProperties::TextFront::Front& target) {
        if (current_context_properties_.front == target) {
            return;
        }

        apply_front(target.current_id);
        current_context_properties_.front = target;
    }
}  // namespace stream::fmt::detail
