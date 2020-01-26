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

#pragma once

#include <string>
#include <optional>
#include <rapidjson/document.h>
#include "messages/message.h"

using namespace std;

namespace ibh {
    enum bonus_type {
        XP = 1,
        GOLD = 2,
        STR = 3,
        AGI = 4,
        VIT = 5,
        PSI = 6,
        SPD = 7,
    };

    struct increase_bonus_request : message {
        explicit increase_bonus_request(uint32_t bonus_type) noexcept;

        ~increase_bonus_request() noexcept override = default;

        [[nodiscard]]
        string serialize() const override;

        [[nodiscard]]
        static unique_ptr<increase_bonus_request> deserialize(rapidjson::Document const &d);

        uint32_t bonus_type;

        inline static constexpr uint64_t type = generate_type<increase_bonus_request>();
    };
}