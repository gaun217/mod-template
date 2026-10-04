#include "mods/service.hpp"
#include "mods/svc/log.h"
#include "mods/svc/overlay.h"
#include "mods/svc/config.h"
#include "mods/svc/texture.h"
#include "mods/svc/ui.h"

#include <string>
#include <vector>

DEFINE_MOD();

IMPORT_SERVICE(LogService, svc_log);
IMPORT_SERVICE(OverlayService, svc_overlay);
IMPORT_SERVICE(ConfigService, svc_config);
IMPORT_SERVICE(TextureService, svc_texture);
IMPORT_SERVICE(UiService, svc_ui);

// ------------------------------------------------------------
// Configuration variables
// ------------------------------------------------------------

ConfigVarHandle buttonLayout = 0;
ConfigVarHandle faceButtonTextureSet = 0;
ConfigVarHandle dpadTextureSet = 0;
ConfigVarHandle menuTextureSet = 0;
ConfigVarHandle shoulderTextureSet = 0;
ConfigVarHandle thumbsticksTextureSet = 0;
ConfigVarHandle miscTextureSet = 0;

std::vector<OverlayHandle> overlayHandles;
std::vector<TextureReplacementHandle> textureHandles;

// ------------------------------------------------------------
// Setting names
// ------------------------------------------------------------

const char* getLayoutName(int64_t value)
{
    switch (value)
    {
    case 0: return "xbox";
    case 1: return "nintendo";
    case 2: return "xbox_xb_swap";
    default: return "nintendo";
    }
}

const char* getFaceButtonTextureSetName(int64_t value)
{
    switch (value)
    {
    case 0: return "Xbox Classic Colored Buttons";
    case 1: return "Xbox Classic Colored Labels";
    case 2: return "Xbox Classic Uncolored";
    case 3: return "Xbox HD";
    case 4: return "Nintendo Classic Colored Buttons";
    case 5: return "Nintendo Classic Colored Labels";
    case 6: return "Nintendo Classic Uncolored";
    case 7: return "Nintendo HD";
    case 8: return "PlayStation Classic Colored Buttons";
    case 9: return "PlayStation Classic Colored Labels";
    case 10: return "PlayStation Classic Uncolored";
    case 11: return "PlayStation HD";
    default: return "Nintendo HD";
    }
}

const char* getDpadTextureSetName(int64_t value)
{
    switch (value)
    {
    case 0: return "PlayStation Classic";
    case 1: return "PlayStation HD";
    case 2: return "Steam Controller (2015) Classic";
    case 3: return "Steam Controller (2015) HD";
    case 4: return "Switch Joycon Classic";
    case 5: return "Switch Joycon HD";
    case 6: return "Switch Pro HD";
    case 7: return "Xbox 360 Classic";
    case 8: return "Xbox 360 HD";
    case 9: return "Xbox ONE & Steam Deck & Switch Pro Classic";
    case 10: return "Xbox ONE & Steam Deck HD";
    default: return "Switch Pro HD";
    }
}

const char* getMenuTextureSetName(int64_t value)
{
    switch (value)
    {
    case 0: return "PlayStation 3 Classic";
    case 1: return "PlayStation 3 HD";
    case 2: return "PlayStation 4 Classic";
    case 3: return "PlayStation 4 HD";
    case 4: return "PlayStation 5 Classic";
    case 5: return "PlayStation 5 HD";
    case 6: return "Steam Deck Classic";
    case 7: return "Steam Deck HD";
    case 8: return "Switch Joycon Classic";
    case 9: return "Switch Joycon HD";
    case 10: return "Switch Pro Classic";
    case 11: return "Switch Pro HD";
    case 12: return "Xbox 360 & Steam Controller (2015) Classic";
    case 13: return "Xbox 360 & Steam Controller (2015) HD";
    case 14: return "Xbox One Classic";
    case 15: return "Xbox One HD";
    default: return "Switch Pro HD";
    }
}

const char* getShoulderTextureSetName(int64_t value)
{
    switch (value)
    {
    case 0: return "PlayStation Classic";
    case 1: return "PlayStation 3 HD";
    case 2: return "PlayStation 4 HD";
    case 3: return "PlayStation 5 HD";
    case 4: return "Steam Controller (2015) Classic";
    case 5: return "Steam Controller (2015) HD";
    case 6: return "Steam Deck Classic";
    case 7: return "Steam Deck HD";
    case 8: return "Switch Classic";
    case 9: return "Switch HD";
    case 10: return "Xbox 360 HD";
    case 11: return "Xbox Classic";
    case 12: return "Xbox One HD";
    default: return "Switch HD";
    }
}

const char* getThumbsticksTextureSetName(int64_t value)
{
    switch (value)
    {
    case 0: return "Classic";
    case 1: return "HD";
    case 2: return "Steam Controller (2015) Classic";
    case 3: return "Steam Controller (2015) HD";
    default: return "HD";
    }
}

const char* getMiscTextureSetName(int64_t value)
{
    switch (value)
    {
    case 0: return "With Face Button Decorations";
    case 1: return "Without Face Button Decorations";
    default: return "With Face Button Decorations";
    }
}

// ------------------------------------------------------------
// BLO replacements
// ------------------------------------------------------------

struct BloReplacement
{
    const char* name;
    const char* original;
    const char* replacement;
};

const BloReplacement bloReplacements[] =
{
    {"zelda_game_image.blo", "/res/Layout/main2D/main2d/scrn/zelda_game_image.blo", "zelda_game_image.blo"},
    {"zelda_game_image_button_info.blo", "/res/Layout/button/button/scrn/zelda_game_image_button_info.blo", "zelda_game_image_button_info.blo"},
    {"zelda_file_select2.blo", "/res/Layout/saveres/saveres/scrn/zelda_file_select2.blo", "zelda_file_select2.blo"},
    {"zelda_collect_soubi_do_icon_parts.blo", "/res/Layout/clctres/clctres/scrn/zelda_collect_soubi_do_icon_parts.blo", "zelda_collect_soubi_do_icon_parts.blo"},
    {"zelda_collect_soubi_do_icon_parts.blo", "/res/Layout/fishres/fishres/scrn/zelda_collect_soubi_do_icon_parts.blo", "zelda_collect_soubi_do_icon_parts.blo"},
    {"zelda_collect_soubi_do_icon_parts.blo", "/res/Layout/insectRes/insectRes/scrn/zelda_collect_soubi_do_icon_parts.blo", "zelda_collect_soubi_do_icon_parts.blo"},
    {"zelda_collect_soubi_do_icon_parts.blo", "/res/Layout/letres/letres/scrn/zelda_collect_soubi_do_icon_parts.blo", "zelda_collect_soubi_do_icon_parts.blo"},
    {"zelda_collect_soubi_do_icon_parts.blo", "/res/Layout/optres/optres/scrn/zelda_collect_soubi_do_icon_parts.blo", "zelda_collect_soubi_do_icon_parts.blo"},
    {"zelda_collect_soubi_do_icon_parts.blo", "/res/Layout/skillres/skillres/scrn/zelda_collect_soubi_do_icon_parts.blo", "zelda_collect_soubi_do_icon_parts.blo"},
    {"zelda_letter_select_base.blo", "/res/Layout/letres/letres/scrn/zelda_letter_select_base.blo", "zelda_letter_select_base.blo"},
    {"tt_zelda_button_l_text.bti", "/res/Layout/letres/letres/scrn/tt_zelda_button_l_text.bti", "tt_zelda_button_l_text.bti"},
    {"zelda_wolf_howl.blo", "/res/Layout/msgres05/msgres05/scrn/zelda_wolf_howl.blo", "zelda_wolf_howl.blo"},
    {"zelda_dungeon_map_spot_button.blo", "/res/Layout/dmapres/dmapres/scrn/zelda_dungeon_map_spot_button.blo", "zelda_dungeon_map_spot_button.blo"},
    {"zelda_map_screen_title.blo", "/res/Layout/fmapres/fmapres/scrn/zelda_map_screen_title.blo", "zelda_map_screen_title.blo"},
    {"zelda_item_select_icon_message_ver2.blo", "/res/Layout/ringres/ringres/scrn/zelda_item_select_icon_message_ver2.blo", "zelda_item_select_icon_message_ver2.blo"},
    {"zelda_file_select.blo", "/res/object/fileSel/fileSel/scrn/zelda_file_select.blo", "zelda_file_select.blo"}
};

const size_t bloReplacementCount = sizeof(bloReplacements) / sizeof(bloReplacements[0]);

// ------------------------------------------------------------
// Texture filenames
// ------------------------------------------------------------

const char* const faceTextures[] =
{
    "tex1_24x24_8b8143aaa181b64a_970dc1662f193ee6_8.dds",
    "tex1_24x24_8f5b85ae836ad2aa_2.dds",
    "tex1_24x24_74c00c62624f1e67_5a4b9fd6e2d23f96_8.dds",
    "tex1_24x24_d693a49f64dd0597_2.dds",
    "tex1_24x40_b191153a917b3b50_0.dds",
    "tex1_32x32_1bb7a1cd57fff2ba_2.dds",
    "tex1_32x40_a57e14b2809290fc_0.dds",
    "tex1_32x45_3b03f19ac102dd38_0.dds",
    "tex1_32x46_683dc853245a0f36_0.dds"
};

const char* const dpadTextures[] =
{
    "tex1_16x16_9593036f62f0cdee_2.dds",
    "tex1_24x24_033376353afbcafd_2.dds",
    "tex1_24x24_6f054092adbc9f9f_26dee35da4c4a565_8.dds",
    "tex1_24x24_c2d0b709693c5c63_26dee35da4c4a565_8.dds"
};

const char* const menuTextures[] =
{
    "tex1_32x45_69b6dab00fd185c9_0.dds"
};

const char* const shoulderTextures[] =
{
    "tex1_24x24_0b05df21ef5718fa_2.dds",
    "tex1_24x24_2c8476ec0c54301b_532709965b890d24_8.dds",
    "tex1_24x24_dcda11193c4368a1_0773499c79b8de07_8.dds",
    "tex1_24x40_1868b6990a352fae_2.dds",
    "tex1_24x44_e76015069e30f42c_0.dds",
    "tex1_32x59_786e694236b0a0f2_0.dds",
    "tex1_32x59_d6db718161b7238c_0.dds"
};

const char* const thumbsticksTextures[] =
{
    "tex1_24x24_15fe54ec0f2bd478_2.dds",
    "tex1_24x24_535302a8d703095e_2cf100e32d072f3d_8.dds",
    "tex1_24x24_a5cfcf59d288b024_a8f82f64b78daf8c_8.dds",
    "tex1_24x24_f65d280c8b9a98bf_a17d69a1dafb1be4_8.dds",
    "tex1_24x24_fb460b6cfcecb726_b551f45795f3db64_8.dds",
    "tex1_32x32_18b050b57efa0865_2.dds",
    "tex1_56x56_b21b4aecb21fe068_3.dds"
};

const char* const miscTextures[] =
{
    "tex1_160x174_1548e5d0789bb2c7_2.dds",
    "tex1_24x24_be1cfaf3f0a58a21_0.dds",
    "tex1_32x32_9b2144b62e98b79c_3.dds",
    "tex1_32x48_3fb1822c7136e19f_2.dds",
    "tex1_32x48_eba23b636dc65b6a_2.dds",
    "tex1_40x40_0bcb924b474aa8a7_2.dds",
    "tex1_48x28_00e15bb6d0caba17_2.dds",
    "tex1_48x28_3288c9160fe71a61_2.dds",
    "tex1_48x32_6726b21e8ab9351d_2.dds",
    "tex1_48x32_d7739fede999427e_2.dds",
    "tex1_48x48_ac081c1868dcd0df_2.dds",
    "tex1_64x64_6c871a1cb3258c85_0.dds",
    "tex1_80x87_2edd4c8992418a7a_2.dds"
};

// ------------------------------------------------------------
// Overlay helpers
// ------------------------------------------------------------

void removeOverlays()
{
    for (OverlayHandle handle : overlayHandles)
    {
        if (handle != 0)
            svc_overlay->remove(mod_ctx, handle);
    }
    overlayHandles.clear();
}

ModResult fileReplace(const std::string& layout)
{
    removeOverlays();

    for (size_t i = 0; i < bloReplacementCount; ++i)
    {
        const BloReplacement& r = bloReplacements[i];
        OverlayHandle handle = 0;
        std::string replacementPath = "res/layouts/" + layout + "/" + r.replacement;

        ModResult result = svc_overlay->add_file(
            mod_ctx,
            r.original,
            replacementPath.c_str(),
            &handle
        );

        if (result != MOD_OK)
        {
            std::string message = "Failed to replace " + std::string(r.name);
            svc_log->error(mod_ctx, message.c_str());
            removeOverlays();
            return result;
        }

        overlayHandles.push_back(handle);
    }

    return MOD_OK;
}

// ------------------------------------------------------------
// Texture helpers
// ------------------------------------------------------------

void removeTextures()
{
    for (TextureReplacementHandle handle : textureHandles)
    {
        if (handle != 0)
            svc_texture->unregister(mod_ctx, handle);
    }
    textureHandles.clear();
}

ModResult registerTexture(const std::string& path)
{
    TextureReplacementHandle handle = 0;
    ModResult result = svc_texture->register_file(mod_ctx, path.c_str(), &handle);

    if (result != MOD_OK)
    {
        std::string message = "Failed to register texture: " + path;
        svc_log->error(mod_ctx, message.c_str());
        return result;
    }

    textureHandles.push_back(handle);
    return MOD_OK;
}

ModResult registerTextureSet(
    const std::string& category,
    const std::string& setName,
    const char* const* files,
    size_t fileCount,
    const std::string& layout = "")
{
    std::string directory = "res/textures/" + category + "/";

    if (category == "Face")
        directory += layout + "/";

    directory += setName + "/";

    for (size_t i = 0; i < fileCount; ++i)
    {
        ModResult result = registerTexture(directory + files[i]);
        if (result != MOD_OK)
            return result;
    }

    return MOD_OK;
}

// ------------------------------------------------------------
// Apply all texture categories
// ------------------------------------------------------------

ModResult applyTextures(
    const std::string& layout,
    const std::string& faceSet,
    const std::string& dpadSet,
    const std::string& menuSet,
    const std::string& shoulderSet,
    const std::string& thumbsticksSet,
    const std::string& miscSet)
{
    removeTextures();

    ModResult result = registerTextureSet("Face", faceSet, faceTextures,
        sizeof(faceTextures) / sizeof(faceTextures[0]), layout);
    if (result != MOD_OK) goto fail;

    result = registerTextureSet("Dpad", dpadSet, dpadTextures,
        sizeof(dpadTextures) / sizeof(dpadTextures[0]));
    if (result != MOD_OK) goto fail;

    result = registerTextureSet("Menu", menuSet, menuTextures,
        sizeof(menuTextures) / sizeof(menuTextures[0]));
    if (result != MOD_OK) goto fail;

    result = registerTextureSet("Shoulders", shoulderSet, shoulderTextures,
        sizeof(shoulderTextures) / sizeof(shoulderTextures[0]));
    if (result != MOD_OK) goto fail;

    result = registerTextureSet("Thumbsticks", thumbsticksSet, thumbsticksTextures,
        sizeof(thumbsticksTextures) / sizeof(thumbsticksTextures[0]));
    if (result != MOD_OK) goto fail;

    result = registerTextureSet("Misc", miscSet, miscTextures,
        sizeof(miscTextures) / sizeof(miscTextures[0]));
    if (result != MOD_OK) goto fail;

    return MOD_OK;

fail:
    removeTextures();
    return result;
}

// ------------------------------------------------------------
// Read current settings and apply everything
// ------------------------------------------------------------

ModResult applySettings()
{
    int64_t layoutValue = 1;
    int64_t faceValue = 7;
    int64_t dpadValue = 6;
    int64_t menuValue = 11;
    int64_t shoulderValue = 9;
    int64_t thumbsticksValue = 1;
    int64_t miscValue = 0;

    ModResult result = svc_config->get_int(mod_ctx, buttonLayout, &layoutValue);
    if (result != MOD_OK) return result;
    result = svc_config->get_int(mod_ctx, faceButtonTextureSet, &faceValue);
    if (result != MOD_OK) return result;
    result = svc_config->get_int(mod_ctx, dpadTextureSet, &dpadValue);
    if (result != MOD_OK) return result;
    result = svc_config->get_int(mod_ctx, menuTextureSet, &menuValue);
    if (result != MOD_OK) return result;
    result = svc_config->get_int(mod_ctx, shoulderTextureSet, &shoulderValue);
    if (result != MOD_OK) return result;
    result = svc_config->get_int(mod_ctx, thumbsticksTextureSet, &thumbsticksValue);
    if (result != MOD_OK) return result;
    result = svc_config->get_int(mod_ctx, miscTextureSet, &miscValue);
    if (result != MOD_OK) return result;

    result = fileReplace(getLayoutName(layoutValue));
    if (result != MOD_OK) return result;

    result = applyTextures(
        getLayoutName(layoutValue),
        getFaceButtonTextureSetName(faceValue),
        getDpadTextureSetName(dpadValue),
        getMenuTextureSetName(menuValue),
        getShoulderTextureSetName(shoulderValue),
        getThumbsticksTextureSetName(thumbsticksValue),
        getMiscTextureSetName(miscValue)
    );

    if (result != MOD_OK)
    {
        removeOverlays();
        return result;
    }

    return MOD_OK;
}

// ------------------------------------------------------------
// Configuration callback
// ------------------------------------------------------------

void onSettingChanged(
    ModContext*,
    ConfigVarHandle,
    const ConfigVarValue*,
    const ConfigVarValue*,
    void*)
{
    ModResult result = applySettings();

    if (result != MOD_OK)
        svc_log->error(mod_ctx, "Failed to apply changed settings");
}

// ------------------------------------------------------------
// UI helpers
// ------------------------------------------------------------

ModResult addDropdown(
    UiElementHandle pane,
    const char* label,
    const char* help,
    ConfigVarHandle configVar,
    const char* const* options,
    size_t optionCount)
{
    UiControlDesc control = UI_CONTROL_DESC_INIT;
    control.kind = UI_CONTROL_DROPDOWN;
    control.label = label;
    control.help_rml = help;
    control.binding = UI_BINDING_CONFIG_VAR;
    control.config_var = configVar;
    control.options = options;
    control.option_count = optionCount;

    return svc_ui->pane_add_control(mod_ctx, pane, &control, nullptr);
}

ModResult buildModOptions(
    ModContext*,
    UiElementHandle pane,
    void*,
    ModError*)
{
    const char* const layoutOptions[] =
    {
        "Xbox Layout",
        "Nintendo Layout",
        "Xbox Layout XB Swap"
    };

    const char* const faceOptions[] =
    {
        "Xbox Classic Colored Buttons",
        "Xbox Classic Colored Labels",
        "Xbox Classic Uncolored",
        "Xbox HD",
        "Nintendo Classic Colored Buttons",
        "Nintendo Classic Colored Labels",
        "Nintendo Classic Uncolored",
        "Nintendo HD",
        "PlayStation Classic Colored Buttons",
        "PlayStation Classic Colored Labels",
        "PlayStation Classic Uncolored",
        "PlayStation HD"
    };

    const char* const dpadOptions[] =
    {
        "PlayStation Classic",
        "PlayStation HD",
        "Steam Controller (2015) Classic",
        "Steam Controller (2015) HD",
        "Switch Joycon Classic",
        "Switch Joycon HD",
        "Switch Pro HD",
        "Xbox 360 Classic",
        "Xbox 360 HD",
        "Xbox ONE & Steam Deck & Switch Pro Classic",
        "Xbox ONE & Steam Deck HD"
    };

    const char* const menuOptions[] =
    {
        "PlayStation 3 Classic",
        "PlayStation 3 HD",
        "PlayStation 4 Classic",
        "PlayStation 4 HD",
        "PlayStation 5 Classic",
        "PlayStation 5 HD",
        "Steam Deck Classic",
        "Steam Deck HD",
        "Switch Joycon Classic",
        "Switch Joycon HD",
        "Switch Pro Classic",
        "Switch Pro HD",
        "Xbox 360 & Steam Controller (2015) Classic",
        "Xbox 360 & Steam Controller (2015) HD",
        "Xbox One Classic",
        "Xbox One HD"
    };

    const char* const shoulderOptions[] =
    {
        "PlayStation Classic",
        "PlayStation 3 HD",
        "PlayStation 4 HD",
        "PlayStation 5 HD",
        "Steam Controller (2015) Classic",
        "Steam Controller (2015) HD",
        "Steam Deck Classic",
        "Steam Deck HD",
        "Switch Classic",
        "Switch HD",
        "Xbox 360 HD",
        "Xbox Classic",
        "Xbox One HD"
    };

    const char* const thumbsticksOptions[] =
    {
        "Classic",
        "HD",
        "Steam Controller (2015) Classic",
        "Steam Controller (2015) HD"
    };

    const char* const miscOptions[] =
    {
        "With Face Button Decorations",
        "Without Face Button Decorations"
    };

    ModResult result = svc_ui->pane_add_section(mod_ctx, pane, "Button Layout");
    if (result != MOD_OK) return result;

    result = addDropdown(pane, "Button Layout",
        "Select the button layout used by Alternate Button Prompts.",
        buttonLayout, layoutOptions, 3);
    if (result != MOD_OK) return result;

    result = svc_ui->pane_add_section(mod_ctx, pane, "Face Button Textures");
    if (result != MOD_OK) return result;

    result = addDropdown(pane, "Face Button Textures",
        "Choose the face buttons that match your controller.\nClassic buttons are based on the GameCube textures while HD buttons are based on Wii U textures.",
        faceButtonTextureSet, faceOptions, 12);
    if (result != MOD_OK) return result;

    result = svc_ui->pane_add_section(mod_ctx, pane, "Dpad");
    if (result != MOD_OK) return result;
    result = addDropdown(pane, "Dpad", "Choose the Dpad texture set.", dpadTextureSet, dpadOptions, 11);
    if (result != MOD_OK) return result;

    result = svc_ui->pane_add_section(mod_ctx, pane, "Menu");
    if (result != MOD_OK) return result;
    result = addDropdown(pane, "Menu", "Choose the menu button texture set.", menuTextureSet, menuOptions, 16);
    if (result != MOD_OK) return result;

    result = svc_ui->pane_add_section(mod_ctx, pane, "Shoulder");
    if (result != MOD_OK) return result;
    result = addDropdown(pane, "Shoulder", "Choose the shoulder button texture set.", shoulderTextureSet, shoulderOptions, 13);
    if (result != MOD_OK) return result;

    result = svc_ui->pane_add_section(mod_ctx, pane, "Thumbsticks");
    if (result != MOD_OK) return result;
    result = addDropdown(pane, "Thumbsticks", "Choose the thumbstick texture set.", thumbsticksTextureSet, thumbsticksOptions, 4);
    if (result != MOD_OK) return result;

    result = svc_ui->pane_add_section(mod_ctx, pane, "Misc");
    if (result != MOD_OK) return result;
    return addDropdown(pane, "Misc", "Choose whether face button decorations are used.", miscTextureSet, miscOptions, 2);
}

// ------------------------------------------------------------
// Config registration helper
// ------------------------------------------------------------

ModResult registerIntConfig(
    const char* name,
    int64_t defaultValue,
    ConfigVarHandle* handle)
{
    ConfigVarDesc desc = CONFIG_VAR_DESC_INIT;
    desc.name = name;
    desc.type = CONFIG_VAR_INT;
    desc.default_int = defaultValue;

    return svc_config->register_var(mod_ctx, &desc, handle);
}

ModResult subscribeConfig(ConfigVarHandle handle)
{
    return svc_config->subscribe(
        mod_ctx,
        handle,
        onSettingChanged,
        nullptr,
        nullptr
    );
}

// ------------------------------------------------------------
// Mod lifecycle
// ------------------------------------------------------------

extern "C"
{

    MOD_EXPORT ModResult mod_initialize(ModError*)
    {
        // Defaults:
        // Layout     -> Nintendo       (1)
        // Face       -> Nintendo HD    (7)
        // Dpad       -> Switch Pro HD  (6)
        // Menu       -> Switch Pro HD  (11)
        // Shoulder   -> Switch HD      (9)
        // Thumbsticks-> HD              (1)
        // Misc       -> With Face Button Decorations (0)

        ModResult result = registerIntConfig("buttonLayout", 1, &buttonLayout);
        if (result != MOD_OK) return result;

        result = registerIntConfig("faceButtonTextureSet", 7, &faceButtonTextureSet);
        if (result != MOD_OK) return result;

        result = registerIntConfig("dpadTextureSet", 6, &dpadTextureSet);
        if (result != MOD_OK) return result;

        result = registerIntConfig("menuTextureSet", 11, &menuTextureSet);
        if (result != MOD_OK) return result;

        result = registerIntConfig("shoulderTextureSet", 9, &shoulderTextureSet);
        if (result != MOD_OK) return result;

        result = registerIntConfig("thumbsticksTextureSet", 1, &thumbsticksTextureSet);
        if (result != MOD_OK) return result;

        result = registerIntConfig("miscTextureSet", 0, &miscTextureSet);
        if (result != MOD_OK) return result;

        ConfigVarHandle configs[] =
        {
            buttonLayout,
            faceButtonTextureSet,
            dpadTextureSet,
            menuTextureSet,
            shoulderTextureSet,
            thumbsticksTextureSet,
            miscTextureSet
        };

        for (ConfigVarHandle handle : configs)
        {
            result = subscribeConfig(handle);
            if (result != MOD_OK) return result;
        }

        UiModsPanelDesc panel = UI_MODS_PANEL_DESC_INIT;
        panel.build = buildModOptions;

        result = svc_ui->register_mods_panel(mod_ctx, &panel);
        if (result != MOD_OK)
        {
            svc_log->error(mod_ctx, "Failed to register Mods panel");
            return result;
        }

        result = applySettings();
        if (result != MOD_OK)
        {
            svc_log->error(mod_ctx, "Failed to apply initial settings");
            return result;
        }

        svc_log->info(mod_ctx, "Alternate Button Prompts initialized");
        return MOD_OK;
    }

    MOD_EXPORT ModResult mod_update(ModError*)
    {
        return MOD_OK;
    }

    MOD_EXPORT ModResult mod_shutdown(ModError*)
    {
        removeOverlays();
        removeTextures();
        return MOD_OK;
    }

}
