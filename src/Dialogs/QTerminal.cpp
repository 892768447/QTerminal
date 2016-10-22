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
#include <KGL/Dialogs/QTerminal.hpp>
#include <KGL/Dialogs/QFormatEditor.hpp>
#include <QFontDialog>
#include <QKeyEvent>
#include <QBrush>
#ifdef Q_OS_WIN
#include <windows.h>
#endif


namespace kgl {

    ///
    ///  @fn        Constructor
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///
    QTerminal::QTerminal(QMainWindow *parent)
        : QDialog(parent),
          m_Layout(NULL),
          m_Input(NULL),
          m_Menu(NULL),
          m_Flag(TextState::Success),
          m_CaretPos(0),
          m_InitialPos(0),
          m_IsReturnPressed(false),
          m_IsReading(false) {

        QMenu *file = new QMenu, *format = new QMenu, *help = new QMenu;
        file->addAction("Close", this, SLOT(exitTerminal()), QKeySequence(Qt::Key_Alt, Qt::Key_F4));
        format->addAction("Palette ...", this, SLOT(showPaletteEditor()));
        format->addAction("Font ...", this, SLOT(showFontEditor()));
        file->setTitle("File");
        format->setTitle("Format");
        help->setTitle("Help");

        // Creates the menu and the input box
        m_Menu = new QMenuBar;
        m_Input = new QTextEdit;
        m_Input->setObjectName("input");
        m_Input->setFrameShape(QFrame::NoFrame);
        m_Input->installEventFilter(this);
        m_Menu->addMenu(file);
        m_Menu->addMenu(format);
        m_Menu->addMenu(help);


        // Builds the UI (menu + text edit)
        m_Layout = new QVBoxLayout;
        m_Layout->setMenuBar(m_Menu);
        m_Layout->addWidget(m_Input);
        m_Layout->setGeometry(QRect(0, 0, width(), height()));
        m_Layout->setMargin(0);
        m_Layout->setContentsMargins(0, 0, 0, 0);
        setLayout(m_Layout);
        updateDesign();

        // Remove help button
        setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    }

    ///
    ///  @fn        Destructor
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///
    QTerminal::~QTerminal() {
        delete m_Layout;
        delete m_Menu;
        delete m_Input;
    }


    ///
    ///  @fn        menuStyleSheet
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    QString QTerminal::menuStyleSheet() {
        QString sheet = m_MenuSheet;
        sheet.replace("%bc", QString::number(m_Design.backColor().rgba(), 16));
        sheet.replace("%fc", QString::number(m_Design.textColor().rgba(), 16));
        sheet.replace("%sc", QString::number(m_Design.backColor().darker().rgba(), 16));
        sheet.replace("%pc", QString::number(m_Design.backColor().darker(400).rgba(), 16));
        return sheet;
    }

    ///
    ///  @fn        exitTerminal
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    void QTerminal::exitTerminal() {
        close();
    }

    ///
    ///  @fn        showPaletteEditor
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    void QTerminal::showPaletteEditor() {
        QFormatEditor editor(this);
        editor.setDesign(m_Design);
        if (editor.exec() == QDialog::Accepted) {
            m_Design = editor.design();
            updateDesign();
        }
    }

    ///
    ///  @fn        showFontEditor
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    void QTerminal::showFontEditor() {
        QFontDialog dialog(m_Design.font(), this);
        if (dialog.exec() == QDialog::Accepted) {
            m_Design.setFont(dialog.font());
            m_Input->setFont(m_Design.font());

            // Change the font family of all input text
            QTextCursor cursor = m_Input->textCursor();
            m_Input->selectAll();
            m_Input->setFontFamily(m_Design.font().family());
            m_Input->setFontPointSize(m_Design.font().pointSize());
            m_Input->setTextCursor(cursor);
        }
    }

    ///
    ///  @fn        readPrivate
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    QString QTerminal::readPrivate() {
        QTextCursor cursor = m_Input->textCursor();
        m_InitialPos = m_CaretPos = cursor.position();
        m_IsReading = true;

        // Waits until return is pressed
        while (!m_IsReturnPressed) {
            QCoreApplication::processEvents();
        }

        m_IsReading = false;
        m_IsReturnPressed = false;

        // Get string that was typed in that time
        QTextCursor tc = m_Input->textCursor();
        tc.setPosition(tc.position()-1);
        tc.setPosition(m_InitialPos, QTextCursor::KeepAnchor);
        return tc.selectedText();
    }

    ///
    ///  @fn    	eventFilter
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    bool QTerminal::eventFilter(QObject *o, QEvent *e) {
        if (o->objectName() == "input" && m_IsReading) {
            if (e->type() != QEvent::KeyPress)
                return QDialog::eventFilter(o, e);

            QKeyEvent *ke = static_cast<QKeyEvent *>(e);

            // Suppress backspace if position is at start position or lower
            if (ke->key() == Qt::Key_Backspace &&
                m_Input->textCursor().position() <= m_InitialPos) {
                return true;
            }

            // Suppress editing if caret is at other position
            if (m_Input->textCursor().position() < m_CaretPos) {
                QTextCursor tc = m_Input->textCursor();
                tc.movePosition(QTextCursor::End);
                m_Input->setTextCursor(tc);
            }

            // If enter was pressed, returns from the reading process
            if (ke->key() == Qt::Key_Return) {
                m_IsReturnPressed = true;
            }

            bool result = QDialog::eventFilter(o, e);
            m_CaretPos = m_Input->textCursor().position();
            return result;
        } else {
            return QDialog::eventFilter(o, e);
        }
    }


    ///
    ///  @fn        updateDesign
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///
    void QTerminal::updateDesign() {
        QPalette pal = m_Input->palette();
        pal.setColor(QPalette::Base, m_Design.backColor());
        pal.setColor(QPalette::Text, m_Design.textColor());
        pal.setColor(QPalette::Highlight, m_Design.textColor());
        pal.setColor(QPalette::HighlightedText, m_Design.backColor());

        m_Input->setPalette(pal);
        m_Input->setFont(m_Design.font());
        m_Menu->setStyleSheet(menuStyleSheet());
    }


    ///
    ///  @fn        flag
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    TextState QTerminal::flag() const {
        return m_Flag;
    }

    ///
    ///  @fn        setCurrentState
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///
    void QTerminal::setCurrentState(TextState state, bool highlight) {
        QTextCharFormat format;
        format.setFont(m_Design.font());

        if (highlight) {
            format.setBackground(QBrush(m_Design.highlightColor()));
        }

        switch(state) {
        case TextState::Normal:  format.setForeground(QBrush(m_Design.textColor()));    break;
        case TextState::Error:   format.setForeground(QBrush(m_Design.errorColor()));   break;
        case TextState::Success: format.setForeground(QBrush(m_Design.successColor())); break;
        case TextState::Warning: format.setForeground(QBrush(m_Design.warningColor())); break;
        }

        m_Input->setCurrentCharFormat(format);
    }

    ///
    ///  @fn        menuAt
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    QAction *QTerminal::menuAt(int index) const {
        return m_Menu->actions().at(index);
    }

    ///
    ///  @fn        clear
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    void QTerminal::clear() {
        m_Input->clear();
    }

    ///
    ///  @fn        readChar
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    QChar QTerminal::readChar() {
        QString s = readPrivate();

        // Returns only the first character
        return s[0];
    }

    ///
    ///  @fn        readLine
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    QString QTerminal::readLine() {
        QString s = readPrivate();

        // Returns the entire line
        return s;
    }

    ///
    ///  @fn        readString
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    QString QTerminal::readString(quint32 size) {
        QString s = readPrivate();

        // Trims the string by size
        return s.left(size);
    }

    ///
    ///  @fn        readByte
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    quint8 QTerminal::readByte() {
        QString s = readPrivate();
        m_Flag = TextState::Success;

        // Attempts to parse the string
        bool result;
        uint b = s.toUInt(&result);
        if (!result) {
            setCurrentState(TextState::Error);
            writeLine("Entered text is not a number.");
            setCurrentState(TextState::Normal);
            m_Flag = TextState::Error;
            return b;
        }

        // Checks whether number is in byte range
        if (b > 0xFF) {
            setCurrentState(TextState::Warning);
            writeLine("Entered number exceeds byte range.");
            setCurrentState(TextState::Normal);
            m_Flag = TextState::Warning;
        }

        return static_cast<quint8>(b & 0xFF);
    }

    ///
    ///  @fn        readUInt16
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    quint16 QTerminal::readUInt16() {
        QString s = readPrivate();
        m_Flag = TextState::Success;

        // Attempts to parse the string
        bool result;
        uint b = s.toUInt(&result);
        if (!result) {
            setCurrentState(TextState::Error);
            writeLine("Entered text is not a number.");
            setCurrentState(TextState::Normal);
            m_Flag = TextState::Error;
            return b;
        }

        // Checks whether number is in short range
        if (b > 0xFFFF) {
            setCurrentState(TextState::Warning);
            writeLine("Entered number exceeds short range.");
            setCurrentState(TextState::Normal);
            m_Flag = TextState::Warning;
        }

        return static_cast<quint16>(b & 0xFFFF);
    }

    ///
    ///  @fn        readUInt32
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    quint32 QTerminal::readUInt32() {
        QString s = readPrivate();
        m_Flag = TextState::Success;

        // Attempts to parse the string
        bool result;
        quint64 b = s.toULongLong(&result);
        if (!result) {
            setCurrentState(TextState::Error);
            writeLine("Entered text is not a number.");
            setCurrentState(TextState::Normal);
            m_Flag = TextState::Error;
            return b;
        }

        // Checks whether number is in short range
        if (b > 0xFFFFFFFF) {
            setCurrentState(TextState::Warning);
            writeLine("Entered number exceeds integer range.");
            setCurrentState(TextState::Normal);
            m_Flag = TextState::Warning;
        }

        return static_cast<quint32>(b & 0xFFFFFFFF);
    }

    ///
    ///  @fn        readUInt64
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    quint64 QTerminal::readUInt64() {
        QString s = readPrivate();
        m_Flag = TextState::Success;

        // Attempts to parse the string
        bool result;
        quint64 b = s.toULongLong(&result);
        if (!result) {
            setCurrentState(TextState::Error);
            writeLine("Entered text is not a number.");
            setCurrentState(TextState::Normal);
            m_Flag = TextState::Error;
        }

        return b;
    }

    ///
    ///  @fn        readFloat
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    float QTerminal::readFloat() {
        QString s = readPrivate();
        m_Flag = TextState::Success;

        // Attempts to parse the string
        bool result;
        float f = s.toFloat(&result);
        if (!result) {
            setCurrentState(TextState::Error);
            writeLine("Entered text is not a floating-point number.");
            setCurrentState(TextState::Normal);
            m_Flag = TextState::Error;
        }

        return f;
    }

    ///
    ///  @fn        readDouble
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    double QTerminal::readDouble() {
        QString s = readPrivate();
        m_Flag = TextState::Success;

        // Attempts to parse the string
        bool result;
        double f = s.toDouble(&result);
        if (!result) {
            setCurrentState(TextState::Error);
            writeLine("Entered text is not a floating-point number.");
            setCurrentState(TextState::Normal);
            m_Flag = TextState::Error;
        }

        return f;
    }

    ///
    ///  @fn        readHex
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    quint64 QTerminal::readHex() {
        QString s = readPrivate();
        m_Flag = TextState::Success;
        s.remove("$").remove("&h", Qt::CaseInsensitive).remove("0x");

        // Attempts to parse the string
        bool result;
        quint64 h = s.toULongLong(&result, 16);
        if (!result) {
            setCurrentState(TextState::Error);
            writeLine("Entered text is not a hex number.");
            setCurrentState(TextState::Normal);
            m_Flag = TextState::Error;
        }

        return h;
    }


    ///
    ///  @fn        writeChar
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    void QTerminal::writeChar(const QChar &c) {
        QTextCursor tc = m_Input->textCursor();
        tc.insertText(QString(c), m_Input->currentCharFormat());
        tc.movePosition(QTextCursor::End);
        m_Input->setTextCursor(tc);
    }

    ///
    ///  @fn        writeLine
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    void QTerminal::writeLine(const QString &l) {
        QTextCursor tc = m_Input->textCursor();
        tc.insertText(l, m_Input->currentCharFormat());
        tc.insertText("\n");
        tc.movePosition(QTextCursor::End);
        m_Input->setTextCursor(tc);
    }

    ///
    ///  @fn        writeString
    ///  @author    Nicolas Kogler
    ///  @date      October 20th, 2016
    ///
    void QTerminal::writeString(const QString &s) {
        QTextCursor tc = m_Input->textCursor();
        tc.insertText(s, m_Input->currentCharFormat());
        tc.movePosition(QTextCursor::End);
        m_Input->setTextCursor(tc);
    }

    ///
    ///  @fn        writeByte
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    void QTerminal::writeByte(quint8 b, NumberFormat f) {
        writeUInt64(static_cast<quint64>(b), f);
    }

    ///
    ///  @fn        writeUInt16
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    void QTerminal::writeUInt16(quint16 b, NumberFormat f) {
        writeUInt64(static_cast<quint64>(b), f);
    }

    ///
    ///  @fn        writeUInt32
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    void QTerminal::writeUInt32(quint32 b, NumberFormat f) {
        writeUInt64(static_cast<quint64>(b), f);
    }

    ///
    ///  @fn        writeUInt64
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    void QTerminal::writeUInt64(quint64 b, NumberFormat f) {
        // Determines the number base
        qint32 base;
        switch (f) {
        case NumberFormat::Binary:      base = 1;  break;
        case NumberFormat::Octal:       base = 8;  break;
        case NumberFormat::Decimal:     base = 10; break;
        case NumberFormat::Hexadecimal: base = 16; break;
        default:                        base = 10; break;
        }

        // Converts the number
        QString s = QString::number(b, base);
        writeString(s);
    }

    ///
    ///  @fn        writeFloat
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    void QTerminal::writeFloat(float b) {
        QString s = QString::number(b, 'f', 6);
        writeString(s);
    }

    ///
    ///  @fn        writeDouble
    ///  @author    Nicolas Kogler
    ///  @date      October 21th, 2016
    ///
    void QTerminal::writeDouble(double b) {
        QString s = QString::number(b, 'f', 12);
        writeString(s);
    }
}
