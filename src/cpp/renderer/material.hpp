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

#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__

#include "texture.hpp"

namespace renderer
{

/** Optical properties of the surface. */
class MATERIAL
{
public:
    float ambient[4];                       // ambient RGBA intensity
    float diffuse[4];                       // diffuse RGBA intensity
    float specular[4];                      // specular RGBA intensity
    float shine;                            // shininess
    renderer::TEXTURE texture;              // base texture

    void bind() const;
};

} // namespace renderer

#endif // __MATERIAL_HPP__
