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

#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <istream>
#include "model.hpp"
#include "solver.hpp"

namespace entity
{

/**
 * Basic 'smart' object interface.
 */
class ENTITY
{

    /* Some interface to controls entities: AI or UI. */

public:
    virtual ~ENTITY() {}

    virtual void init(std::istream src) = 0;
    virtual void render(float delta_time = 0) const;
    virtual void update(float delta_time = 0);
};

} // namespace entity

#endif // __ENTITY_HPP__
