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

#include "spdlog/spdlog.h"
#include <SDL.h>

using namespace std;
namespace ibh {
    void enqueue_sdl_event(uint32_t type, uint32_t code, void *data1 = nullptr, void *data2 = nullptr) {
        SDL_Event event{0};
        event.type = type;
        event.user.code = code;
        event.user.data1 = data1;
        event.user.data2 = data2;
        auto ret = SDL_PushEvent(&event);
        if (ret != 1) {
            spdlog::error("error pushing event {}", ret);
        }
    }
}