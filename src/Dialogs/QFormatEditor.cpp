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
#include <KGL/Dialogs/QFormatEditor.hpp>
#include <KGL/Dialogs/QTerminal.hpp>
#include <QtUiTools/QUiLoader>
#include <QAbstractButton>
#include <QPushButton>
#include <QColorDialog>
#include <QDialogButtonBox>


namespace kgl {

    ///
    ///  @fn        Default constructor
    ///  @author    Nicolas Kogler
    ///  @date      October 22nd, 2016
    ///
    QFormatEditor::QFormatEditor(QTerminal *parent)
        : QDialog(parent) {
        QUiLoader ui;
        QFile file(":/QFormatEditor.ui");
        file.open(QFile::ReadOnly);
        setWindowTitle("Format editor");

        // Loads the ui into this dialog
        QWidget *w = ui.load(&file, this);
        file.close();

        // Creates a new layout and places the new widget in it
        m_Layout = new QVBoxLayout;
        m_Layout->addWidget(w);
        setLayout(m_Layout);
        setWindowFlags(windowFlags() &= ~Qt::WindowContextHelpButtonHint);

        // Finds all buttons
        m_Buttons = w->findChildren<QPushButton *>(QRegularExpression("btn.*"));

        // Connects all the buttons with slots
        m_Mapper = new QSignalMapper(this);
        for (int i = 0; i < 6; ++i) {
            QPushButton *button = m_Buttons[i];
            m_Mapper->setMapping(button, button->objectName());
            connect(button, SIGNAL(clicked()), m_Mapper, SLOT(map()));
        }

        connect(m_Mapper, SIGNAL(mapped(QString)), this, SLOT(openDialog(QString)));

        QDialogButtonBox *bg = w->findChild<QDialogButtonBox *>();
        connect(bg->buttons()[0], SIGNAL(clicked()), this, SLOT(accept()));
        connect(bg->buttons()[1], SIGNAL(clicked()), this, SLOT(reject()));
    }

    ///
    ///  @fn        Destructor
    ///  @author    Nicolas Kogler
    ///  @date      October 22nd, 2016
    ///
    QFormatEditor::~QFormatEditor() {
        delete m_Layout;
        delete m_Mapper;
    }


    ///
    ///  @fn        setDesign
    ///  @author    Nicolas Kogler
    ///  @date      October 22nd, 2016
    ///
    void QFormatEditor::setDesign(const QTerminalDesign &design) {
        m_Design = design;
    }

    ///
    ///  @fn        design
    ///  @author    Nicolas Kogler
    ///  @date      October 22nd, 2016
    ///
    const QTerminalDesign &QFormatEditor::design() const {
        return m_Design;
    }


    ///
    ///  @fn        openDialog
    ///  @author    Nicolas Kogler
    ///  @date      October 22nd, 2016
    ///
    void QFormatEditor::openDialog(QString sender) {
        QColor initial;
        if (sender == "btnBack") {
            initial = m_Design.backColor();
        } else if (sender == "btnText") {
            initial = m_Design.textColor();
        } else if (sender == "btnSucc") {
            initial = m_Design.successColor();
        } else if (sender == "btnErro") {
            initial = m_Design.errorColor();
        } else if (sender == "btnWarn") {
            initial = m_Design.warningColor();
        } else if (sender == "btnHigh") {
            initial = m_Design.highlightColor();
        }

        QColorDialog dialog(this);
        dialog.setCurrentColor(initial);
        if (dialog.exec() == QDialog::Accepted) {
            if (sender == "btnBack") {
                m_Design.setBackColor(dialog.currentColor());
            } else if (sender == "btnText") {
                m_Design.setTextColor(dialog.currentColor());
            } else if (sender == "btnSucc") {
                m_Design.setSuccessColor(dialog.currentColor());
            } else if (sender == "btnErro") {
                m_Design.setErrorColor(dialog.currentColor());
            } else if (sender == "btnWarn") {
                m_Design.setWarningColor(dialog.currentColor());
            } else if (sender == "btnHigh") {
                m_Design.setHighlightColor(dialog.currentColor());
            }
        }
    }
}
