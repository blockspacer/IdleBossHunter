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

#define CATCH_CONFIG_RUNNER

#include <catch2/catch.hpp>
#include <spdlog/spdlog.h>
#include <working_directory_manipulation.h>

using namespace std;
using namespace ibh;

int main(int argc, char **argv) {
    set_cwd(get_selfpath());
    locale::global(locale("en_US.UTF-8"));
    spdlog::set_level(spdlog::level::trace);

    int result = Catch::Session().run( argc, argv );
    // global clean-up...

    return ( result < 0xff ? result : 0xff );
}
