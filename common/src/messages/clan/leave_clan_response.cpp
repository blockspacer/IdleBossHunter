/*
    IdleBossHunter
    Copyright (C) 2020 Michael de Lang

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "leave_clan_response.h"
#include <spdlog/spdlog.h>
#include <rapidjson/writer.h>

using namespace ibh;
using namespace rapidjson;

leave_clan_response::leave_clan_response(string error) noexcept : error(move(error)) {

}

string leave_clan_response::serialize() const {
    StringBuffer sb;
    Writer<StringBuffer> writer(sb);

    writer.StartObject();

    writer.String(KEY_STRING("type"));
    writer.Uint64(type);

    writer.String(KEY_STRING("error"));
    writer.String(error.c_str(), error.size());

    writer.EndObject();
    return sb.GetString();
}

unique_ptr<leave_clan_response> leave_clan_response::deserialize(rapidjson::Document const &d) {
    if (!d.HasMember("type") || !d.HasMember("error")) {
        spdlog::warn("[leave_clan_response] deserialize failed");
        return nullptr;
    }

    if(d["type"].GetUint64() != type) {
        spdlog::warn("[leave_clan_response] deserialize failed wrong type");
        return nullptr;
    }

    return make_unique<leave_clan_response>(d["error"].GetString());
}
