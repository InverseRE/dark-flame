/**
 * DarkFlame Copyright (C) 2014 Alexey Shumeiko
 *
 * This file is part of DarkFlame.
 *
 * DarkFlame is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DarkFlame is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DarkFlame.  If not, see <http://www.gnu.org/licenses/>.
 *
 * For more details see LICENSE file.
 */

#ifndef __HELP_WAVE_HPP__
#define __HELP_WAVE_HPP__

#include "function.hpp"
#include "solver.hpp"
#include "wave.hpp"
#include "particle.hpp"

namespace function
{

/** Helpful class to visualize the physic::WAVE's work. */
class HELP_WAVE : public FUNCTION, public physic::WAVE
{
private:
    physic::EMITTER source;

public:
    HELP_WAVE(const physic::WAVE&);
    HELP_WAVE(physic::SOLVER&);
    ~HELP_WAVE();

    HELP_WAVE(const HELP_WAVE&);
    HELP_WAVE& operator =(const HELP_WAVE&);

    void init(std::istream src);
    void render(float delta_time = 0) const;
    void update(float delta_time = 0);

    void update_random_rays(float delta_time = 0);
    void render_random_rays(float delta_time = 0) const;
};

} // namespace function

#endif // __HELP_WAVE_HPP__
