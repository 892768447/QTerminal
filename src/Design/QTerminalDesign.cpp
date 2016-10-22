//
//  QTerminal - Widget to highlight and auto-complete code.
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


//
//  Included headers
//
#include <KGL/Design/QTerminalDesign.hpp>


namespace kgl {

    ///
    ///  @fn        Default constructor
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///
    QTerminalDesign::QTerminalDesign()
        : m_BackColor(0xff333333),
          m_TextColor(0xffdddddd),
          m_Font("Monospace"),
          m_ErrorColor(0xffff3000),
          m_SuccessColor(0xff30ff00),
          m_WarningColor(0xffff8000),
          m_HighlightColor(0xff3030ff) {
        m_Font.setStyleHint(QFont::TypeWriter);
        m_Font.setPointSize(10);
    }

    ///
    ///  @fn        Destructor
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///
    QTerminalDesign::~QTerminalDesign() {
    }


    ///
    ///  @fn        backColor
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///
    const QColor &QTerminalDesign::backColor() const {
        return m_BackColor;
    }

    ///
    ///  @fn        textColor
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///
    const QColor &QTerminalDesign::textColor() const {
        return m_TextColor;
    }

    ///
    ///  @fn        font
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///
    const QFont &QTerminalDesign::font() const {
        return m_Font;
    }

    ///
    ///  @fn        errorColor
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///
    const QColor &QTerminalDesign::errorColor() const {
        return m_ErrorColor;
    }

    ///
    ///  @fn        successColor
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///
    const QColor &QTerminalDesign::successColor() const {
        return m_SuccessColor;
    }

    ///
    ///  @fn        warningColor
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///
    const QColor &QTerminalDesign::warningColor() const {
        return m_WarningColor;
    }

    ///
    ///  @fn        highlight
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///
    const QColor &QTerminalDesign::highlightColor() const {
        return m_HighlightColor;
    }


    ///
    ///  @fn        setBackColor
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///
    void QTerminalDesign::setBackColor(const QColor &color) {
        m_BackColor = color;
    }

    ///
    ///  @fn        setTextColor
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///
    void QTerminalDesign::setTextColor(const QColor &color) {
        m_TextColor = color;
    }

    ///
    ///  @fn        setFont
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///
    void QTerminalDesign::setFont(const QFont &font) {
        m_Font = font;
    }

    ///
    ///  @fn        setErrorColor
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///
    void QTerminalDesign::setErrorColor(const QColor &color) {
        m_ErrorColor = color;
    }

    ///
    ///  @fn        setSuccessColor
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///
    void QTerminalDesign::setSuccessColor(const QColor &color) {
        m_SuccessColor = color;
    }

    ///
    ///  @fn        setWarningColor
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///
    void QTerminalDesign::setWarningColor(const QColor &color) {
        m_WarningColor = color;
    }

    ///
    ///  @fn        setHighlightColor
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///
    void QTerminalDesign::setHighlightColor(const QColor &color) {
        m_HighlightColor = color;
    }
}
