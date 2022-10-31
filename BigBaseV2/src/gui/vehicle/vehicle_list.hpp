#pragma once
#include "common.hpp"
#include "script.hpp"
#include "natives.hpp"
#include "gui/controller/xostr.h"

namespace big
{
    struct vehicle_list_struct
    {
        const char* hash_key{};
        rage::joaat_t hash{};
    };

    class vehicles_hash
    {
    private:
        static inline const char* const the_contract_update[15]{ "Buffalo4", "Granger2", "Iwagen", "Patriot3", xorstr("mobil"), "Baller7", "Champion", "Cinquemila", "Comet7", "Deity", "Ignus", "Jubilee", "Reever", "Shinobi", "Zeno"};
        static inline const char* const boat[20]{ "DINGHY","DINGHY2","DINGHY3","DINGHY4","JETMAX","MARQUIS","SEASHARK","SEASHARK2","SEASHARK3","SPEEDER","SPEEDER2","SQUALO","SUBMERSIBLE","SUBMERSIBLE2","SUNTRAP","TORO","TORO2","TROPIC","TROPIC2","TUG" };
        static inline const char* const commericals[17]{ "BENSON","BIFF","HAULER", "HAULER2","MULE","MULE2","MULE3","MULE4","PACKER","PHANTOM","PHANTOM2", "PHANTOM3","POUNDER","POUNDER2","STOCKADE","STOCKADE3","TERBYTE" };
        static inline const char* const compact[9]{ "BLISTA","BRIOSO","DILETTANTE","DILETTANTE2","ISSI2","ISSI3","PANTO","PRAIRIE","RHAPSODY" };
        static inline const char* const coupes[14]{ "COGCABRIO","EXEMPLAR","F620","FELON","FELON2","JACKAL","ORACLE","ORACLE2","SENTINEL","SENTINEL2", "WINDSOR","WINDSOR2","ZION","ZION2" };
        static inline const char* const bikes[7]{ "BMX","CRUISER","FIXTER","SCORCHER","TRIBIKE","TRIBIKE2","TRIBIKE3" };
        static inline const char* const emergency[21]{ "AMBULANCE","FBI","FBI2","FIRETRUK","LGUARD","PBUS","POLICE","POLICE2","POLICE3","POLICE4", "POLICEB","POLMAV","POLICEOLD1","POLICEOLD2","POLICET","PRANGER","PREDATOR","RIOT","RIOT2","SHERIFF","SHERIFF2" };
        static inline const char* const helicopter[22]{ "AKULA", "ANNIHILATOR", "BUZZARD","BUZZARD2", "CARGOBOB", "CARGOBOB2", "CARGOBOB3", "CARGOBOB4", "FROGGER","FROGGER2", "HAVOK","HUNTER", "MAVERICK","SAVAGE","SKYLIFT","SUPERVOLITO","SUPERVOLITO2","SWIFT","SWIFT2", "VALKYRIE","VALKYRIE2","VOLATUS" };
        static inline const char* const industrial[11]{ "BULLDOZER","CUTTER","DUMP","FLATBED","GUARDIAN","HANDLER","MIXER", "MIXER2","RUBBLE","TIPTRUCK", "TIPTRUCK2" };
        static inline const char* const military[12]{ "APC","BARRACKS","BARRACKS2","BARRACKS3","BARRAGE","CHERNOBOG","CRUSADER","HALFTRACK","KHANJALI", "RHINO", "THRUSTER","TRAILERSMALL2" };
        static inline const char* const motorcycle[47]{ "AKUMA","AVARUS","BAGGER","BATI","BATI2", "BF400","CARBONRS", "CHIMERA","CLIFFHANGER","DAEMON", "DAEMON2","DEFILER","DIABLOUS","DIABLOUS2","DOUBLE","ENDURO","ESSKEY","FAGGIO","FAGGIO2","FAGGIO3","FCR","FCR2","GARGOYLE", "HAKUCHOU","HAKUCHOU2","HEXER", "INNOVATION","LECTRO","MANCHEZ","NEMESIS","NIGHTBLADE","OPPRESSOR","OPPRESSOR2","PCJ","RATBIKE", "RUFFIAN","SANCHEZ2","SANCTUS","SHOTARO","SOVEREIGN","THRUST","VADER","VINDICATOR","VORTEX","WOLFSBANE","ZOMBIEA","ZOMBIEB" };
        static inline const char* const muscle[46]{ "BLADE","BUCCANEER","BUCCANEER2","CHINO","CHINO2","COQUETTE3","DOMINATOR", "DOMINATOR2", "DOMINATOR3", "DUKES","DUKES2","ELLIE","FACTION","FACTION2","FACTION3","GAUNTLET","GAUNTLET2","HERMES","HOTKNIFE","LURCHER","MOONBEAM", "MOONBEAM2","NIGHTSHADE","PHOENIX","PICADOR","RATLOADER","RATLOADER2","RUINER","RUINER2","RUINER3","SABREGT","SABREGT2","SLAMVAN","SLAMVAN2","SLAMVAN3","STALION","STALION2","TAMPA","TAMPA3","VIGERO","VIRGO","VIRGO2","VIRGO3","VOODOO","VOODOO2","YOSEMITE" };
        static inline const char* const offRoad[39]{ "BFINJECTION","BIFTA","BLAZER","BLAZER2","BLAZER3","BLAZER4","BLAZER5","BODHI2","BRAWLER","DLOADER","DUBSTA3", "DUNE","DUNE2","DUNE3","DUNE4","DUNE5", "FREECRAWLER","INSURGENT","INSURGENT2","INSURGENT3","KALAHARI","KAMACHO","MARSHALL", "MESA3","MONSTER","MENACER","NIGHTSHARK","RANCHERXL","RANCHERXL2","REBEL","REBEL2","RIATA","SANDKING","SANDKING2","TECHNICAL","TECHNICAL2","TECHNICAL3","TROPHYTRUCK","TROPHYTRUCK2" };
        static inline const char* const plane[37]{ "ALPHAZ1","AVENGER","BESRA","BLIMP","BLIMP2","BLIMP3","BOMBUSHKA","CARGOPLANE","CUBAN800","DODO", "DUSTER","HOWARD","HYDRA","JET","LAZER","LUXOR","LUXOR2","MAMMATUS","MICROLIGHT","MILJET","MOGUL","MOLOTOK","NIMBUS","NOKOTA","PYRO","ROGUE","SEABREEZE","SHAMAL","STARLING","STRIKEFORCE","STUNT","TITAN","TULA","VELUM","VELUM2","VESTRA","VOLATOL" };
        static inline const char* const SUV[28]{ "BALLER","BALLER2","BALLER3","BALLER4","BALLER5","BALLER6","BJXL","CAVALCADE","CAVALCADE2","CONTENDER", "DUBSTA","DUBSTA2","FQ2","GRANGER","GRESLEY","HABANERO","HUNTLEY","LANDSTALKER","MESA","MESA2","PATRIOT","PATRIOT2","RADI","ROCOTO", "SEMINOLE","SERRANO","XLS","XLS2" };
        static inline const char* const sedan[33]{ "ASEA","ASEA2","ASTEROPE","CHEBUREK","COG55","COG552","COGNOSCENTI","COGNOSCENTI2","EMPEROR","EMPEROR2", "EMPEROR3","FUGITIVE","GLENDALE","INGOT","INTRUDER","LIMO2","PREMIER","PRIMO","PRIMO2","REGINA","ROMERO","SCHAFTER2","SCHAFTER5", "SCHAFTER6","STAFFORD","STANIER","STRATUM","STRETCH","SUPERD","SURGE","TAILGATER","WARRENER","WASHINGTON" };
        static inline const char* const service[12]{ "AIRBUS","BRICKADE","BUS","COACH","PBUS2","RALLYTRUCK","RENTALBUS","TAXI","TOURBUS","TRASH","TRASH2","WASTELANDER" };
        static inline const char* const sport[57]{ "ALPHA","BANSHEE","BESTIAGTS","BLISTA2","BLISTA3","BUFFALO","BUFFALO2","BUFFALO3","CARBONIZZARE", "COMET2","COMET3","COMET4","COMET5","COQUETTE","ELEGY","ELEGY2","FELTZER2","FLASHGT","FUROREGT","FUSILADE","FUTO","GB200","HOTRING", "JESTER","JESTER2","JESTER3","KHAMELION","KURUMA","KURUMA2","LYNX2","MASSACRO","MASSACRO2","NEON","NINEF","NINEF2","OMNIS","PARIAH", "PENUMBRA","RAIDEN","RAPIDGT","RAPIDGT2","RAPTOR","REVOLTER","RUSTON","SCHAFTER3","SCHAFTER4","SCHWARZER","SENTINEL3","SEVEN70","SPECTER", "SPECTER2","STREITER","SULTAN","SURANO","TAMPA2","TROPOS","VERLIERER2" };
        static inline const char* const sport_classic[38]{ "ARDENT","BTYPE","BTYPE2","BTYPE3","CASCO","CHEETAH2","COQUETTE2","DELUXO","FAGALOA","FELTZER3", "GT500","HUSTLER","INFERNUS2","JB700","MAMBA","MANANA","MICHELLI","MONROE","PEYOTE","PIGALLE","RAPIDGT3","RETINUE","SAVESTRA", "STINGER","STINGERGT","STROMBERG","SWINGER","TORERO","TORNADO","TORNADO2","TORNADO3","TORNADO4","TORNADO5","TORNADO6","TURISMO2", "VISERIS","Z190","ZTYPE" };
        static inline const char* const super[40]{ "ADDER","AUTARCH","BANSHEE2","BULLET","CHEETAH","CYCLONE","ENTITYXF","ENTITY2","FMJ","GP1","INFERNUS", "ITALIGTB","ITALIGTB2","LE7B","NERO","NERO2","OSIRIS","PENETRATOR","PFISTER811","PROTOTIPO","REAPER","SC1","SCRAMJET","SHEAVA","SULTANRS", "T20","TAIPAN","TEMPESTA","TEZERACT","TURISMOR","TYRANT","TYRUS","VACCA","VAGNER","VIGILANTE","VISIONE","VOLTIC","VOLTIC2","XA21", "ZENTORNO" };
        static inline const char* const trailer[21]{ "ARMYTANKER","ARMYTRAILER2","BALETRAILER","BOATTRAILER","CABLECAR","DOCKTRAILER","GRAINTRAILER", "PROPTRAILER","RAKETRAILER","TR2","TR3","TR4","TRFLAT","TVTRAILER","TANKER","TANKER2","TRAILERLOGS","TRAILERSMALL","TRAILERS","TRAILERS2","TRAILERS3" };
        static inline const char* const train[6]{ "FREIGHT","FREIGHTCAR","FREIGHTCONT1","FREIGHTCONT2","FREIGHTGRAIN", "TANKERCAR" };
        static inline const char* const utility[20]{ "AIRTUG","CADDY","CADDY2","CADDY3","CARACARA","DOCKTUG","FORKLIFT","MOWER","RIPLEY","SADLER","SADLER2","SCRAP","TOWTRUCK","TOWTRUCK2","TRACTOR","TRACTOR2","TRACTOR3","UTILLITRUCK","UTILLITRUCK2","UTILLITRUCK3" };
        static inline const char* const van[34]{ "BISON","BISON2","BISON3","BOBCATXL","BOXVILLE","BOXVILLE2","BOXVILLE3","BOXVILLE4","BOXVILLE5","BURRITO","BURRITO2","BURRITO3","BURRITO4","BURRITO5","CAMPER","GBURRITO","GBURRITO2","JOURNEY","MINIVAN","MINIVAN2","PARADISE","PONY","PONY2","RUMPO","RUMPO2","RUMPO3","SPEEDO","SPEEDO2","SPEEDO4","SURFER","SURFER2","TACO","YOUGA","YOUGA2" };
        static inline const char* const arena_war[45]{ "BRUISER","BRUISER2","BRUISER3","BRUTUS","BRUTUS2","BRUTUS3","CERBERUS","CERBERUS2","CERBERUS3","CLIQUE","DEATHBIKE","DEATHBIKE2","DEATHBIKE3","DEVESTE","DEVIANT","DOMINATOR4","DOMINATOR5","DOMINATOR6","IMPALER","IMPALER2","IMPALER3","IMPALER4","IMPERATOR","IMPERATOR2","IMPERATOR3","ISSI4","ISSI5","ISSI6","ITALIGTO","MONSTER3","MONSTER4","MONSTER5","RCBANDITO","SCARAB2","SCARAB3","SCHLAGEN","SLAMVAN4","SLAMVAN5","SLAMVAN6","TOROS","TULIP","VAMOS","ZR380","ZR3802","ZR3803" };
        static inline const char* const casino_update[22]{ "CARACARA2","DRAFTER","DYNASTY","EMERUS","GAUNTLET3","GAUNTLET4","HELLION","ISSI7","JUGULAR","KRIEGER","LOCUST","NEBULA","NEO","NOVAK","PARAGON","PARAGON2","PEYOTE2","RROCKET","S80","THRAX","ZION3","ZORRUSSO" };
        static inline const char* const casino_heist_update[20]{ "ABSO","EVERON","FORMULA","FORMULA2","FURIA","IMORGON","JB7002","KANJO","KOMODA","MINITANK","OUTLAW","REBLA","RETINUE2","STRYDER","SUGOI","SULTAN2","VAGRANT","VSTR","YOSEMITE2","ZHABA" };
        static inline const char* const summer_update[15]{ "CLUB","COQUETTE4","DUKES3","GAUNTLET5","GLENDALE2","LANDSTALKER2","MANANA2","OPENWHEEL1","OPENWHEEL2","PENUMBRA2","PEYOTE3","SEMINOLE2","TIGON","YOSEMITE3","YOUGA3" };
        static inline const char* const cayo_perico_update[21]{ "ALKONOST","WINKY","Annihilator2","TOREADOR","LONGFIN","VETIR","ITALIRSX","WEEVIL","VETO","VETO2","VERUS","SLAMTRUCK","MANCHEZ2","BRIOSO2","DINGHY5","SQUADDIE","PATROLBOAT","AVISA","SEASPARROW2","SEASPARROW3","KOSATKA" };
        static inline const char* const tuner_update[19]{ "Comet6", "Cypher", "Euros", "Growler", "Jester4", "Tailgater2", "Vectre", "Zr350", "Calico", "Dominator7", "Dominator8", "Futo2", "Previon", "Remus", "Rt3000", "Sultan3", "Warrener2", "Freightcar2", "Warrener" };
        static inline const char* const criminal_enterprise[17]{ "brioso3", "kanjosj", "tenf", "weevil2", "torero2", "sentinel4", "postlude", "draugur", "rhinehart", "vigero2", "greenwood", "omnisegt", "ruiner4", "corsita", "lm87", "sm722", "conada" };
    public:
        static inline const char* const vehicle_category_list[31]{ "Super","Sport","Sport Classic","Summer Update","Sedans","Service","SUVs","Planes", "Helicopters","Off Road","Muscles","Motorcycles","Military","Trailers","Trains","Utility","Vans","Arena Wars","Casino Updates", "Casino Heist","Emergency","Industrial","Coupes","Compacts","Boats","Bikes","Commericals","Cayo Perico","Tuner Update", "The Contract Update", "The Criminal Enterprise"};
        static inline std::map<std::string, vehicle_list_struct> get_vehicle_data{};
        static inline void fill_vehicle(int type)
        {
            switch (type)
            {
            case 0:
                if (get_vehicle_data.size() != (_ARRAYSIZE(super)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : super)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 1:
                if (get_vehicle_data.size() != (_ARRAYSIZE(sport)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : sport)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 2:
                if (get_vehicle_data.size() != (_ARRAYSIZE(sport_classic)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : sport_classic)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 3:
                if (get_vehicle_data.size() != (_ARRAYSIZE(summer_update)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : summer_update)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 4:
                if (get_vehicle_data.size() != (_ARRAYSIZE(sedan)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : sedan)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 5:
                if (get_vehicle_data.size() != (_ARRAYSIZE(service)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : service)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 6:
                if (get_vehicle_data.size() != (_ARRAYSIZE(SUV)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : SUV)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 7:
                if (get_vehicle_data.size() != (_ARRAYSIZE(plane)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : plane)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 8:
                if (get_vehicle_data.size() != (_ARRAYSIZE(helicopter)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : helicopter)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 9:
                if (get_vehicle_data.size() != (_ARRAYSIZE(offRoad)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : offRoad)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 10:
                if (get_vehicle_data.size() != (_ARRAYSIZE(muscle)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : muscle)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 11:
                if (get_vehicle_data.size() != (_ARRAYSIZE(motorcycle)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : motorcycle)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 12:
                if (get_vehicle_data.size() != (_ARRAYSIZE(military)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : military)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 13:
                if (get_vehicle_data.size() != (_ARRAYSIZE(trailer)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : trailer)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 14:
                if (get_vehicle_data.size() != (_ARRAYSIZE(train)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : train)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 15:
                if (get_vehicle_data.size() != (_ARRAYSIZE(utility)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : utility)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 16:
                if (get_vehicle_data.size() != (_ARRAYSIZE(van)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : van)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 17:
                if (get_vehicle_data.size() != (_ARRAYSIZE(arena_war)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : arena_war)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 18:
                if (get_vehicle_data.size() != (_ARRAYSIZE(casino_update)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : casino_update)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 19:
                if (get_vehicle_data.size() != (_ARRAYSIZE(casino_heist_update)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : casino_heist_update)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 20:
                if (get_vehicle_data.size() != (_ARRAYSIZE(emergency)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : emergency)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 21:
                if (get_vehicle_data.size() != (_ARRAYSIZE(industrial)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : industrial)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 22:
                if (get_vehicle_data.size() != (_ARRAYSIZE(coupes)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : coupes)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 23:
                if (get_vehicle_data.size() != (_ARRAYSIZE(compact)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : compact)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 24:
                if (get_vehicle_data.size() != (_ARRAYSIZE(boat)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : boat)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 25:
                if (get_vehicle_data.size() != (_ARRAYSIZE(bikes)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : bikes)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 26:
                if (get_vehicle_data.size() != (_ARRAYSIZE(commericals)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : commericals)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 27:
                if (get_vehicle_data.size() != (_ARRAYSIZE(cayo_perico_update)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : cayo_perico_update)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 28:
                if (get_vehicle_data.size() != (_ARRAYSIZE(tuner_update)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : tuner_update)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 29:
                if (get_vehicle_data.size() != (_ARRAYSIZE(the_contract_update)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : the_contract_update)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;
                        
                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            case 30:
                if (get_vehicle_data.size() != (ARRAYSIZE(criminal_enterprise)))
                {
                    get_vehicle_data.clear();
                    for (auto hash_key : criminal_enterprise)
                    {
                        auto cstr_name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(rage::joaat(hash_key)));
                        std::string name = cstr_name;

                        get_vehicle_data[name] = { hash_key, rage::joaat(hash_key) };
                    }
                }
                break;
            }
        }
    };

    inline vehicles_hash *g_get_vehicle;
}