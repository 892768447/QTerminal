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


#ifndef __KGL_QTERMINALDESIGN_HPP__
#define __KGL_QTERMINALDESIGN_HPP__


//
//  Included headers
//
#include <KGL/KGLConfig.hpp>
#include <QColor>
#include <QFont>


namespace kgl {

    ///
    ///  @file      QTerminalDesign.hpp
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///  @class     QTerminalDesign
    ///  @brief     Designs the terminal window.
    ///
    class KGL_API QTerminalDesign {
    public:

        ///
        ///  @fn    Default constructor
        ///  @brief Initializes a new instance of QTerminalDesign.
        ///
        QTerminalDesign();

        ///
        ///  @fn    Copy constructor
        ///  @brief Copies one QTerminalDesign to another.
        ///  @param design Other design
        ///
        QTerminalDesign(const QTerminalDesign &design) = default;

        ///
        ///  @fn    Destructor
        ///  @brief Frees all resources allocated by QTerminalDesign.
        ///
        ~QTerminalDesign();


        ///
        ///  @fn      backColor : const
        ///  @brief   Retrieves the background color of the console.
        ///  @returns the background color of the console.
        ///
        const QColor &backColor() const;

        ///
        ///  @fn      textColor : const
        ///  @brief   Retrieves the text color of the console.
        ///  @returns the text color of the console.
        ///
        const QColor &textColor() const;

        ///
        ///  @fn      font : const
        ///  @brief   Retrieves the font of the console.
        ///  @returns the font of the console.
        ///
        const QFont &font() const;

        ///
        ///  @fn      errorColor : const
        ///  @brief   Retrieves the color of an error text.
        ///  @returns the error text color.
        ///
        const QColor &errorColor() const;

        ///
        ///  @fn      successColor : const
        ///  @brief   Retrieves the color of a 'success' text.
        ///  @returns the 'success' text color.
        ///
        const QColor &successColor() const;

        ///
        ///  @fn      warningColor : const
        ///  @brief   Retrieves the color of a warning text.
        ///  @returns the warning text color.
        ///
        const QColor &warningColor() const;

        ///
        ///  @fn      highlightColor : const
        ///  @brief   Retrieves the highlight background color.
        ///  @returns the highlight background color.
        ///
        const QColor &highlightColor() const;


        ///
        ///  @fn    setBackColor
        ///  @brief Specifies the terminal's background color.
        ///  @param color The terminal's background color
        ///
        void setBackColor(const QColor &color);

        ///
        ///  @fn    setTextColor
        ///  @brief Specifies the terminal's normal text color.
        ///  @param color The terminal's normal text color
        ///
        void setTextColor(const QColor &color);

        ///
        ///  @fn    setFont
        ///  @brief Specifies the terminal's font.
        ///  @param font The terminal's font
        ///
        void setFont(const QFont &font);

        ///
        ///  @fn    setErrorColor
        ///  @brief Specifies the terminal's error color.
        ///  @param color The terminal's error color
        ///
        void setErrorColor(const QColor &color);

        ///
        ///  @fn    setSuccessColor
        ///  @brief Specifies the terminal'success color.
        ///  @param color The terminal's success color
        ///
        void setSuccessColor(const QColor &color);

        ///
        ///  @fn    setWarningColor
        ///  @brief Specifies the terminal's warning color.
        ///  @param color The terminal's warning color
        ///
        void setWarningColor(const QColor &color);

        ///
        ///  @fn    setHighlightColor
        ///  @brief Specifies the terminal's highlight color.
        ///  @param color The terminal's highlight color
        ///
        void setHighlightColor(const QColor &color);


    private:

        //
        // Private class members
        //
        QColor m_BackColor;
        QColor m_TextColor;
        QFont m_Font;
        QColor m_ErrorColor;
        QColor m_SuccessColor;
        QColor m_WarningColor;
        QColor m_HighlightColor;

    };
}


#endif  // __KGL_QTERMINALDESIGN_HPP__
