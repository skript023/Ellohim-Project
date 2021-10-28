#pragma once

namespace event_json
{
	struct event_json
	{
		int size_of_args_array = 2;
		std::vector<int64_t> args{};
		std::vector<bool> arg_is_hex{};
	};
	static void to_json(nlohmann::json& j, const event_json& attachment) {
		j = nlohmann::json{ {"size_of_args_array", attachment.size_of_args_array},
							{"args", attachment.args}, {"arg_is_hex", attachment.arg_is_hex} };
	}

	static void from_json(const nlohmann::json& j, event_json& attachment) {
		j.at("size_of_args_array").get_to(attachment.size_of_args_array);
		j.at("args").get_to(attachment.args); j.at("arg_is_hex").get_to(attachment.arg_is_hex);
	}
};