#include "main.hpp"
#include "FontStyle.hpp"
#include "SkryptConfig.hpp"
#include "SkryptViewController.hpp"

#include "questui/shared/QuestUI.hpp"
#include "custom-types/shared/register.hpp"

#include "TMPro/TextMeshPro.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");

    createConfig();
}

MAKE_HOOK_OFFSETLESS(TextMeshPro_Awake, void,
    TMPro::TextMeshPro* self
) {
    TextMeshPro_Awake(self);
    self->set_fontStyle(getFontStyle());
}

MAKE_HOOK_OFFSETLESS(TextMeshProUGUI_Awake, void,
 TMPro::TextMeshProUGUI* self
) {
    TextMeshProUGUI_Awake(self);
    self->set_fontStyle(getFontStyle());
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    getLogger().info("Installing hooks...");
    // Install our hooks (none defined yet)
    INSTALL_HOOK_OFFSETLESS(getLogger(), TextMeshPro_Awake, il2cpp_utils::FindMethodUnsafe("TMPro", "TextMeshPro", "Awake", 0));
    INSTALL_HOOK_OFFSETLESS(getLogger(), TextMeshProUGUI_Awake, il2cpp_utils::FindMethodUnsafe("TMPro", "TextMeshProUGUI", "Awake", 0));

    custom_types::Register::RegisterType<Skrypt::SkryptViewController>();
    QuestUI::Register::RegisterModSettingsViewController<Skrypt::SkryptViewController*>(modInfo);
    getLogger().info("Installed all hooks!");
}