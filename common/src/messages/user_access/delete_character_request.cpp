/*
    IdleBossHunter
    Copyright (C) 2019 Michael de Lang

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

#include "delete_character_request.h"
#include <spdlog/spdlog.h>
#include <rapidjson/writer.h>

using namespace ibh;
using namespace rapidjson;

delete_character_request::delete_character_request(uint32_t slot) noexcept
        : slot(slot) {

}

string delete_character_request::serialize() const {
    StringBuffer sb;
    Writer<StringBuffer> writer(sb);

    writer.StartObject();

    writer.String(KEY_STRING("type"));
    writer.Uint(type);

    writer.String(KEY_STRING("slot"));
    writer.Uint(slot);

    writer.EndObject();
    return sb.GetString();
}

unique_ptr<delete_character_request> delete_character_request::deserialize(rapidjson::Document const &d) {
    if (!d.HasMember("type") || !d.HasMember("slot")) {
        spdlog::warn("[delete_character_request] deserialize failed");
        return nullptr;
    }

    if(d["type"].GetUint() != type) {
        spdlog::warn("[delete_character_request] deserialize failed wrong type");
        return nullptr;
    }

    return make_unique<delete_character_request>(d["slot"].GetUint());
}