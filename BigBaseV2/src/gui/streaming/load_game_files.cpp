#include "load_game_files.hpp"
#include "gta_util.hpp"
#include "script.hpp"

namespace big
{
    Hash load_files::load_model(const char* name)
    {
        Hash hash = rage::joaat(name) == RAGE_JOAAT("mobil") ? RAGE_JOAAT("Astron") : rage::joaat(name);
        STREAMING::REQUEST_MODEL(hash);
        while (!STREAMING::HAS_MODEL_LOADED(hash))
        {
            script::get_current()->yield();
        }
        return hash;
    }

    Hash load_files::load_model(Hash hash)
    {
        STREAMING::REQUEST_MODEL(hash);
        while (!STREAMING::HAS_MODEL_LOADED(hash))
        {
            script::get_current()->yield();
        }
        return hash;
    }

    void load_files::ptfx_asset_load(const char* name)
    {
        while (!STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(name))
        {
            STREAMING::REQUEST_NAMED_PTFX_ASSET(name);
            script::get_current()->yield();
        }
    }

    const char* load_files::load_anim(const char* anim)
    {
        while (!STREAMING::HAS_ANIM_DICT_LOADED(anim))
        {
            STREAMING::REQUEST_ANIM_DICT(anim);
            script::get_current()->yield();
        }
        return anim;
    }
}