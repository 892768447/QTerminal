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


#ifndef __KGL_QTERMINAL_HPP__
#define __KGL_QTERMINAL_HPP__


//
//  Included headers
//
#include <KGL/KGLConfig.hpp>
#include <KGL/Dialogs/QTerminalEnums.hpp>
#include <KGL/Design/QTerminalDesign.hpp>
#include <QDialog>
#include <QMainWindow>
#include <QMenuBar>
#include <QTextEdit>
#include <QVBoxLayout>


namespace kgl {

    ///
    ///  @file      QTerminal.hpp
    ///  @author    Nicolas Kogler
    ///  @date      October 19th, 2016
    ///  @class     QTerminal
    ///  @brief     Consists of a menu and of a modified QTextEdit.
    ///
    class KGL_API QTerminal : public QDialog {
    Q_OBJECT
    public:

        ///
        ///  @fn    Default constructor
        ///  @brief Initializes a new instance of QTerminal.
        ///
        QTerminal(QMainWindow *parent);

        ///
        ///  @fn    Destructor
        ///  @brief Frees all resources allocated by QTerminal.
        ///
        ~QTerminal();


        ///
        ///  @fn      flag
        ///  @brief   Retrieves the current state of the terminal.
        ///  @returns TextState::Success or TextState::Error or TextState::Warning
        ///
        TextState flag() const;


        ///
        ///  @fn    setCurrentState
        ///  @brief Specifies the current terminal state.
        ///  @param state Error, success, warning, ...
        ///  @param highlight True if highlighted text
        ///  @note  Will generate a format that will be used
        ///         for all 'write' operations.
        ///
        void setCurrentState(TextState state, bool highlight = false);

        ///
        ///  @fn      menuAt : const
        ///  @brief   Retrieves the menu at 'index' in order to modify it.
        ///  @param   index Sub-menu index of menu-bar
        ///  @returns the sub-menu at 'index'.
        ///
        QAction *menuAt(int index) const;

        ///
        ///  @fn    clear
        ///  @brief Clears the console.
        ///
        void clear();


        ///
        ///  @fn      readLine : const
        ///  @brief   Blocks until return was pressed, then returns line.
        ///  @returns the line written until press of return.
        ///
        QString readLine();

        ///
        ///  @fn      readChar : const
        ///  @brief   Blocks until one single character was typed.
        ///  @returns the pressed character.
        ///
        QChar readChar();

        ///
        ///  @fn      readString : const
        ///  @brief   Blocks until return was pressed, then return string of specified size.
        ///  @returns a string that has the specified size.
        ///
        QString readString(quint32 size);

        ///
        ///  @fn      readByte : const
        ///  @brief   Blocks until one byte was typed.
        ///  @returns the byte typed into the console.
        ///  @note    Displays an error message if parsing was invalid.
        ///
        quint8 readByte();

        ///
        ///  @fn      readUInt16 : const
        ///  @brief   Blocks until one short was typed.
        ///  @returns the short typed into the console.
        ///  @note    Displays an error message if parsing was invalid.
        ///
        quint16 readUInt16();

        ///
        ///  @fn      readUInt32 : const
        ///  @brief   Blocks until one integer was typed.
        ///  @returns the integer typed into the console.
        ///  @note    Displays an error message if parsing was invalid.
        ///
        quint32 readUInt32();

        ///
        ///  @fn      readUInt64 : const
        ///  @brief   Blocks until one long was typed.
        ///  @returns the long typed into the console.
        ///  @note    Displays an error message if parsing was invalid.
        ///
        quint64 readUInt64();

        ///
        ///  @fn      readFloat : const
        ///  @brief   Blocks until one float was typed.
        ///  @returns the float typed into the console.
        ///  @note    Displays an error message if parsing was invalid.
        ///
        float readFloat();

        ///
        ///  @fn      readDouble : const
        ///  @brief   Blocks until one double was typed.
        ///  @returns the double typed into the console.
        ///  @note    Displays an error message if parsing was invalid.
        ///
        double readDouble();

        ///
        ///  @fn      readHex : const
        ///  @brief   Blocks until one hexadecimal number was typed.
        ///  @returns the hexadecimal number typed into the console.
        ///  @note    Displays an error message if parsing was invalid.
        ///           Supported prefixes: $, &h, 0x
        ///
        quint64 readHex();


        ///
        ///  @fn    writeChar : const
        ///  @brief Writes one character to the console.
        ///  @param c Character to write
        ///
        void writeChar(const QChar &c);

        ///
        ///  @fn    writeLine : const
        ///  @brief Writes one line and appends a newline character afterwards.
        ///  @param l Line to write
        ///
        void writeLine(const QString &l);

        ///
        ///  @fn    writeString : const
        ///  @brief Writes a vanilla string to the console.
        ///  @param s String to write
        ///
        void writeString(const QString &s);

        ///
        ///  @fn    writeByte : const
        ///  @brief Writes a byte to the console.
        ///  @param b Byte to write
        ///  @param f Format to use
        ///
        void writeByte(quint8 b, NumberFormat f = NumberFormat::Decimal);

        ///
        ///  @fn    writeUInt16 : const
        ///  @brief Writes a short to the console.
        ///  @param b UInt16 to write
        ///  @param f Format to use
        ///
        void writeUInt16(quint16 b, NumberFormat f = NumberFormat::Decimal);

        ///
        ///  @fn    writeUInt32 : const
        ///  @brief Writes an integer to the console.
        ///  @param b UInt32 to write
        ///  @param f Format to use
        ///
        void writeUInt32(quint32 b, NumberFormat f = NumberFormat::Decimal);

        ///
        ///  @fn    writeUInt64 : const
        ///  @brief Writes a long to the console.
        ///  @param b UInt64 to write
        ///  @param f Format to use
        ///
        void writeUInt64(quint64 b, NumberFormat f = NumberFormat::Decimal);

        ///
        ///  @fn    writeFloat : const
        ///  @brief Writes a float to the console.
        ///  @param b Float to write
        ///  @param f Format to use
        ///
        void writeFloat(float b);

        ///
        ///  @fn    writeDouble : const
        ///  @brief Writes a double to the console.
        ///  @param b Double to write
        ///  @param f Format to use
        ///
        void writeDouble(double b);


    protected:

        QString menuStyleSheet();
        QString readPrivate();
        void updateDesign();
        bool eventFilter(QObject *o, QEvent *e);


    private slots:

        ///
        ///  @fn    exitTerminal
        ///  @brief Closes the terminal window.
        ///
        void exitTerminal();

        ///
        ///  @fn    showPaletteEditor
        ///  @brief Shows the palette editor to edit the design.
        ///
        void showPaletteEditor();

        ///
        ///  @fn    showFontEditor
        ///  @brief Shows the font editor to edit the design.
        ///
        void showFontEditor();


    private:

        //
        // Private class members
        //
        QTerminalDesign m_Design;
        QVBoxLayout *m_Layout;
        QTextEdit *m_Input;
        QMenuBar *m_Menu;
        TextState m_Flag;
        qint32 m_CaretPos;
        qint32 m_InitialPos;
        bool m_IsReturnPressed;
        bool m_IsReading;

        // Stylesheet for the menu-bar
        const QString m_MenuSheet =
                "QMenuBar {"
                "   background-color: #%bc;"
                "   border-bottom: 1px solid #%fc;"
                "} QMenuBar::item {"
                "   background: transparent;"
                "   spacing: 8px;"
                "   padding: 4px 4px;"
                "   color: #%fc;"
                "} QMenuBar::item:selected {"
                "   background-color: #%sc;"
                "} QMenuBar::item:pressed {"
                "   background-color: #%pc;"
                "}";
    };
}


#endif  // __KGL_QTERMINAL_HPP__
