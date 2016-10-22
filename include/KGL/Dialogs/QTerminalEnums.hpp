//
//  QTerminal - Cross platform terminal with extended functionality.
//  Copyright (C) 2016 Nicolas Kogler (kogler.cml@hotmail.com)
//
//  This file is part of QTerminal.
//
//  QTerminal is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with QTerminal.  If not, see <http://www.gnu.org/licenses/>.
//
//


#ifndef __KGL_QTERMINALENUMS_HPP__
#define __KGL_QTERMINALENUMS_HPP__


namespace kgl {

    ///
    ///  @file      QTerminalEnums.hpp
    ///  @author    Nicolas Kogler
    ///  @date      October 6th, 2016
    ///  @brief     Defines enums to use along with QTerminal.
    ///

    enum class NumberFormat {
        Decimal,
        Hexadecimal,
        Octal,
        Binary
    };

    enum class TextState {
        Normal,
        Error,
        Success,
        Warning
    };
}


#endif  // __KGL_QTERMINALENUMS_HPP__
