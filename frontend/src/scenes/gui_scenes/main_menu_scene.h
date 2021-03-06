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

#include "../scene.h"

namespace ibh {
    class main_menu_scene : public scene  {
    public:
        main_menu_scene() : scene(4) {}
        ~main_menu_scene() override = default;

        void update(iscene_manager *manager, TimeDelta dt) override;
        void handle_message(iscene_manager *manager, uint64_t type, message* msg) override;
    };
}
