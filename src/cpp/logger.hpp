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

#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <fstream>

class LFILE
{
private:
    static unsigned int note;

    char file_name[1024];
    std::fstream* fhdl;

public:
    LFILE();
    LFILE(const char* name_output);
    LFILE(const char* name_output, const char* text);
    ~LFILE();

    LFILE(const LFILE&);
    LFILE& operator =(const LFILE&);

    void addf(const char* text, ...);
    void add(const char* text);
    void deny();
};

extern LFILE DFLOG;

#endif  // __LOGGER_HPP__
