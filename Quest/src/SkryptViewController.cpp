#include "SkryptViewController.hpp"
#include "main.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"

#include "UnityEngine/Color.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"
#include "UnityEngine/UI/Toggle.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/SpriteRenderer.hpp"
#include "UnityEngine/MeshRenderer.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Random.hpp"
#include "UnityEngine/RectOffset.hpp"

#include "TMPro/FontStyles.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

#include <vector>

DEFINE_TYPE(Skrypt::SkryptViewController);

UnityEngine::UI::VerticalLayoutGroup* layout;
UnityEngine::UI::VerticalLayoutGroup* previewLayout;

UnityEngine::UI::HorizontalLayoutGroup* preview_titleLayout;

UnityEngine::UI::HorizontalLayoutGroup* mainStyles;
UnityEngine::UI::HorizontalLayoutGroup* caseStyles;

TMPro::TextMeshProUGUI* info;
 
TMPro::TextMeshProUGUI* preview_title;
TMPro::TextMeshProUGUI* preview;

TMPro::TextMeshProUGUI* styleTitle;
TMPro::TextMeshProUGUI* caseTitle;

UnityEngine::UI::Button* isBold;
UnityEngine::UI::Button* isStrikethrough;
UnityEngine::UI::Button* isUnderline;
UnityEngine::UI::Button* defaultCase;
UnityEngine::UI::Button* upperCase;
UnityEngine::UI::Button* lowerCase;

UnityEngine::UI::Button* apply;

bool bold = getConfig().config["isBold"].GetBool();
bool strikethrough = getConfig().config["isStrikethrough"].GetBool();
bool underline = getConfig().config["isUnderline"].GetBool();

int _case = getConfig().config["case"].GetInt(); // 0 = Normal, 1 = LowerCase, 2 = UpperCase

void Skrypt::SkryptViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if (firstActivation) {

    //   ========================== PREVIEW BELOW =============================

        previewLayout = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(get_transform());
        previewLayout->set_spacing(-100.0f);
        previewLayout->get_transform()->set_localPosition(UnityEngine::Vector3(75, 0, 0));
        previewLayout->set_padding(UnityEngine::RectOffset::New_ctor(10, 10, -20, -20));

        preview_title = QuestUI::BeatSaberUI::CreateText(previewLayout->get_transform(), "Preview");
        preview_title->set_fontSize(6);
        preview_title->set_fontStyle(TMPro::FontStyles::Underline);
        preview_title->set_alignment(TMPro::TextAlignmentOptions::Midline);

        preview_titleLayout = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(previewLayout->get_transform());
        preview_titleLayout->get_gameObject()->AddComponent<QuestUI::Backgroundable*>()->ApplyBackground(il2cpp_utils::createcsstr("round-rect-panel"));
        preview_titleLayout->set_padding(UnityEngine::RectOffset::New_ctor(5, 5, 0, 0));

        preview = QuestUI::BeatSaberUI::CreateText(preview_titleLayout->get_transform(), "The Quick Brown Fox\nJumps Over The Lazy Dog");
        preview->set_alignment(TMPro::TextAlignmentOptions::Midline);

    //   ========================== PREVIEW ABOVE =============================

        layout = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(get_transform());
        layout->get_gameObject()->AddComponent<QuestUI::Backgroundable*>()->ApplyBackground(il2cpp_utils::createcsstr("round-rect-panel"));
        layout->set_spacing(-0.0f);

        info = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "NOTE: All changes require a restart");
        info->set_fontSize(4.0f);
        info->set_color(UnityEngine::Color::get_gray());
        info->set_alignment(TMPro::TextAlignmentOptions::Midline);

        styleTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "Font Styles");
        styleTitle->set_fontSize(5.0f);
        styleTitle->set_alignment(TMPro::TextAlignmentOptions::Midline);

        mainStyles = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(layout->get_transform());
        mainStyles->set_padding(UnityEngine::RectOffset::New_ctor(5, 5, 0, 0));

        isBold = QuestUI::BeatSaberUI::CreateUIButton(mainStyles->get_transform(), "Bold", 
            []() {
                bold = !bold;
                getConfig().config["isBold"].SetBool(bold);
                if (!bold) {
                    preview->set_fontStyle(preview->get_fontStyle() &~ TMPro::FontStyles::Bold);
                }
                else { 
                    preview->set_fontStyle(preview->get_fontStyle() | TMPro::FontStyles::Bold);
                }
            }
        );
        isBold->GetComponentInChildren<TMPro::TextMeshProUGUI*>()->set_fontStyle(TMPro::FontStyles::Bold);

        isStrikethrough = QuestUI::BeatSaberUI::CreateUIButton(mainStyles->get_transform(), "Strikethrough",
            []() {
                strikethrough = !strikethrough;
                getConfig().config["isStrikethrough"].SetBool(strikethrough);
                if (!strikethrough) {
                    preview->set_fontStyle(preview->get_fontStyle() &~ TMPro::FontStyles::Strikethrough);
                }
                else { 
                    preview->set_fontStyle(preview->get_fontStyle() | TMPro::FontStyles::Strikethrough);
                }
            }
        );
        isStrikethrough->GetComponentInChildren<TMPro::TextMeshProUGUI*>()->set_fontStyle(TMPro::FontStyles::Strikethrough);

        isUnderline = QuestUI::BeatSaberUI::CreateUIButton(mainStyles->get_transform(), "Underline",
            []() {
                underline = !underline;
                getConfig().config["isUnderline"].SetBool(underline);
                if (!underline) {
                    preview->set_fontStyle(preview->get_fontStyle() &~ TMPro::FontStyles::Underline);
                }
                else { 
                    preview->set_fontStyle(preview->get_fontStyle() | TMPro::FontStyles::Underline);
                }
            }
        );
        isUnderline->GetComponentInChildren<TMPro::TextMeshProUGUI*>()->set_fontStyle(TMPro::FontStyles::Underline);

        
        caseTitle = QuestUI::BeatSaberUI::CreateText(layout->get_transform(), "Font Case");
        caseTitle->set_fontSize(5.0f);
        caseTitle->set_alignment(TMPro::TextAlignmentOptions::Midline);

        caseStyles = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(layout->get_transform());
        caseStyles->set_padding(UnityEngine::RectOffset::New_ctor(5, 5, 0, 0));

        defaultCase = QuestUI::BeatSaberUI::CreateUIButton(caseStyles->get_transform(), "Default",
            []() {
                _case = 0;
                getConfig().config["case"].SetInt(_case);

                preview->set_fontStyle(preview->get_fontStyle() &~ TMPro::FontStyles::UpperCase);
                preview->set_fontStyle(preview->get_fontStyle() &~ TMPro::FontStyles::LowerCase);
            }
        );

        lowerCase = QuestUI::BeatSaberUI::CreateUIButton(caseStyles->get_transform(), "Lower",
            []() {
                _case = 1;
                getConfig().config["case"].SetInt(_case);

                preview->set_fontStyle(preview->get_fontStyle() &~ TMPro::FontStyles::UpperCase);
                preview->set_fontStyle(preview->get_fontStyle() | TMPro::FontStyles::LowerCase);
            }
        );

        upperCase = QuestUI::BeatSaberUI::CreateUIButton(caseStyles->get_transform(), "Upper",
            []() {
                _case = 2;
                getConfig().config["case"].SetInt(_case);

                preview->set_fontStyle(preview->get_fontStyle() &~ TMPro::FontStyles::LowerCase);
                preview->set_fontStyle(preview->get_fontStyle() | TMPro::FontStyles::UpperCase);
            }
        );        
    }
}

void Skrypt::SkryptViewController::DidDeactivate(bool removedFromHierarchy, bool systemScreenDisabling) {
    getConfig().Write();
}