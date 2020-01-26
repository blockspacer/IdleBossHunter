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

#include "player_enter_handler.h"

#include <spdlog/spdlog.h>
#include <ecs/components.h>
#include <range/v3/algorithm/any_of.hpp>
#include <messages/generic_error_response.h>
#include <messages/battle/new_battle_response.h>

using namespace std;

namespace ibh {
    void handle_player_enter_message(queue_message* msg, entt::registry& registry, outward_queues& outward_queue) {
        auto *enter_msg = dynamic_cast<player_enter_message*>(msg);

        if(enter_msg == nullptr) {
            spdlog::error("[{}] player_enter_message nullptr", __FUNCTION__);
            return;
        }

        bool player_found = false;
        auto pc_view = registry.view<pc_component>();
        for(auto entity : pc_view) {
            auto &pc = pc_view.get(entity);

            if(pc.id != enter_msg->character_id) {
                continue;
            }

            pc.connection_id = enter_msg->connection_id;
            spdlog::trace("[{}] found pc {} for connection id {}", __FUNCTION__, pc.name, pc.connection_id);
            player_found = true;

            if(pc.battle) {
                auto mob_hp = pc.battle->monster_stats.find(stat_hp_id);
                auto mob_max_hp = pc.battle->monster_stats.find(stat_max_hp_id);
                auto player_hp = pc.battle->total_player_stats.find(stat_hp_id);
                auto player_max_hp = pc.battle->total_player_stats.find(stat_max_hp_id);
                auto new_battle_msg = make_unique<new_battle_response>(pc.battle->monster_name, pc.battle->monster_level, mob_hp->second, mob_max_hp->second, player_hp->second, player_max_hp->second);
                outward_queue.enqueue({pc.connection_id, move(new_battle_msg)});
            }

            break;
        }

        if(!player_found) {
            throw std::runtime_error("Could not find player");
        }
    }
}
