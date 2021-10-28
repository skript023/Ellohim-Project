#include "common.hpp"
#include "persist_teleport.h"
#include "gui.hpp"
#include "fiber_pool.hpp"

namespace big
{
    void persist_teleport::save_location(Vector3 position, float rotation, std::string name)
    {
        model_attachment::model_attachment attachment;
        attachment.position = position;
        attachment.rotation.x = rotation;
        save(attachment, name);
    }

    void persist_teleport::save_location(Ped ped, std::string name)
    {
        model_attachment::model_attachment attachment;
        Entity player = ped;
        if (PED::IS_PED_IN_ANY_VEHICLE(ped, FALSE))
            player = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
        attachment.position = ENTITY::GET_ENTITY_COORDS(player, TRUE);
        attachment.rotation.x = ENTITY::GET_ENTITY_HEADING(player);
        attachment.rotation.y = CAM::GET_GAMEPLAY_CAM_RELATIVE_PITCH();
        attachment.rotation.z = CAM::GET_GAMEPLAY_CAM_RELATIVE_HEADING();
        save(attachment, name);
    }

    void persist_teleport::load_location(std::string name)
    {
        auto locations = get_locations_json();
        if (locations[name].is_null())
            return;
        auto model_attachment = locations[name].get<model_attachment::model_attachment>();
        Ped player_ped = PLAYER::PLAYER_PED_ID();
        Entity player = player_ped;
        if (PED::IS_PED_IN_ANY_VEHICLE(player_ped, FALSE))
            player = PED::GET_VEHICLE_PED_IS_IN(player_ped, FALSE);
        ENTITY::SET_ENTITY_COORDS_NO_OFFSET(player, model_attachment.position.x, model_attachment.position.y, model_attachment.position.z, TRUE, TRUE, TRUE);
        ENTITY::SET_ENTITY_HEADING(player, model_attachment.rotation.x);
        CAM::SET_GAMEPLAY_CAM_RELATIVE_PITCH(model_attachment.rotation.y, 1.f);
        CAM::SET_GAMEPLAY_CAM_RELATIVE_HEADING(model_attachment.rotation.z);
    }

    void persist_teleport::delete_location(std::string name)
    {
        auto locations = get_locations_json();
        if (locations[name].is_null())
            return;
        locations.erase(name);
        save_json(locations);
    }

    std::vector<std::string> persist_teleport::list_locations()
    {
        std::vector<std::string> return_value;
        auto json = get_locations_json();
        for (auto& item : json.items())
            return_value.push_back(item.key());
        return return_value;
    }

    void persist_teleport::save(model_attachment::model_attachment attachment, std::string name)
    {
        auto json = get_locations_json();
        json[name] = attachment;
        save_json(json);
    }

    void persist_teleport::save_json(nlohmann::json json)
    {
        auto file_path = get_locations_config();
        std::ofstream file(file_path, std::ios::out | std::ios::trunc);
        file << json.dump(4);
        file.close();
    }

    nlohmann::json persist_teleport::get_locations_json()
    {
        auto file_path = get_locations_config();
        nlohmann::json locations;
        std::ifstream file(file_path);

        if (!file.fail())
            file >> locations;

        return locations;
    }


    std::filesystem::path persist_teleport::get_locations_config()
    {
        auto file_path = std::filesystem::path(std::getenv("appdata"));
        file_path /= "Ellohim Menu";

        if (!std::filesystem::exists(file_path))
        {
            std::filesystem::create_directory(file_path);
        }
        else if (!std::filesystem::is_directory(file_path))
        {
            std::filesystem::remove(file_path);
            std::filesystem::create_directory(file_path);
        }

        file_path /= "Teleport.json";

        return file_path;
    }
}