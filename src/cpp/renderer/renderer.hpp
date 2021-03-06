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

#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

namespace renderer
{

/* Later will be replaced with abstract class for several renderers. */
class RENDERER
{
public:
    static void init();
    static void push_matrix();
    static void pop_matrix();
    static void translate(float, float, float);
    static void rotate(float, float, float, float);
    static void scale(float, float, float);
};

}

#endif // __RENDERER_HPP__
