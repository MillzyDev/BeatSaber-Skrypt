#include "main.hpp"
#include "FontStyle.hpp"
#include "TMPro/FontStyles.hpp"

TMPro::FontStyles getFontStyle() {
    TMPro::FontStyles fontStyle = TMPro::FontStyles::Normal;

    if (getConfig().config["isBold"].GetBool()) {
        fontStyle = fontStyle | TMPro::FontStyles::Bold;
    }
    if (getConfig().config["isStrikethrough"].GetBool()) {
        fontStyle = fontStyle | TMPro::FontStyles::Strikethrough;
    }
    if (getConfig().config["isUnderline"].GetBool()) {
        fontStyle = fontStyle | TMPro::FontStyles::Underline;
    }

    switch (getConfig().config["case"].GetInt()) {
        case 1: 
            fontStyle = fontStyle | TMPro::FontStyles::LowerCase;
        break;
        case 2: 
            fontStyle = fontStyle | TMPro::FontStyles::UpperCase;
        break;
        default:
            fontStyle = fontStyle &~ TMPro::FontStyles::LowerCase;
            fontStyle = fontStyle &~ TMPro::FontStyles::UpperCase;
    }

    return fontStyle;
}