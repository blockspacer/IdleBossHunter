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

#include "join_clan_request.h"
#include <spdlog/spdlog.h>
#include <rapidjson/writer.h>

using namespace ibh;
using namespace rapidjson;

join_clan_request::join_clan_request(string clan_name) noexcept : clan_name(move(clan_name)) {

}

string join_clan_request::serialize() const {
    StringBuffer sb;
    Writer<StringBuffer> writer(sb);

    writer.StartObject();

    writer.String(KEY_STRING("type"));
    writer.Uint64(type);

    writer.String(KEY_STRING("clan_name"));
    writer.String(clan_name.c_str(), clan_name.length());

    writer.EndObject();
    return sb.GetString();
}

unique_ptr<join_clan_request> join_clan_request::deserialize(rapidjson::Document const &d) {
    if (!d.HasMember("type") || !d.HasMember("clan_name")) {
        spdlog::warn("[join_clan_request] deserialize failed");
        return nullptr;
    }

    if(d["type"].GetUint64() != type) {
        spdlog::warn("[join_clan_request] deserialize failed wrong type");
        return nullptr;
    }

    return make_unique<join_clan_request>(d["clan_name"].GetString());
}
