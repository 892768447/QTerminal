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


#ifndef __KGL_QFORMATEDITOR_HPP__
#define __KGL_QFORMATEDITOR_HPP__


//
//  Included headers
//
#include <KGL/KGLConfig.hpp>
#include <KGL/Design/QTerminalDesign.hpp>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QDialog>


namespace kgl {

    class QTerminal;

    ///
    ///  @file      QFormatEditor.hpp
    ///  @author    Nicolas Kogler
    ///  @date      October 6th, 2016
    ///  @class     QFormatEditor
    ///  @brief     Shows a dialog to specify the terminal formatting.
    ///
    class KGL_API QFormatEditor : public QDialog {
    Q_OBJECT
    public:

        ///
        ///  @fn    Default constructor
        ///  @brief Initializes a new instance of QFormatEditor.
        ///
        QFormatEditor(QTerminal *parent);

        ///
        ///  @fn    Destructor
        ///  @brief Frees all resources allocated by QFormatEditor.
        ///
        ~QFormatEditor();


        ///
        ///  @fn    setDesign
        ///  @brief Specifies the initial terminal design.
        ///  @param design Current terminal design
        ///
        void setDesign(const QTerminalDesign &design);

        ///
        ///  @fn      design
        ///  @brief   Retrieves the new terminal design.
        ///  @returns the new design.
        ///
        const QTerminalDesign &design() const;


    private slots:

        void openDialog(QString sender);


    private:

        //
        // Private class members
        //
        QTerminalDesign m_Design;
        QVBoxLayout *m_Layout;
        QSignalMapper *m_Mapper;
        QList<QPushButton *> m_Buttons;
    };
}


#endif  // __KGL_QFORMATEDITOR_HPP__
