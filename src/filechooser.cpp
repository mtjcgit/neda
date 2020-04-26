/***************************************************************************
 *   Copyright (C) 2011 by Mohammad Taqi Jafari <mchemtux@users.sf.net>    *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

#include <QtGui>

#include "filechooser.h"
//#include "filedialog.h"
#include "globalvar.h"
#include "lineedit.h"

fileChooser::fileChooser(QWidget *parent) : QWidget(parent)
{
  line_edit = new lineEdit(this);
  
  button = new QToolButton(this);
  button->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/document-open-folder.png"));
  connect(button, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
  connect(line_edit, SIGNAL(editingFinished()), this, SLOT(lineditState()));
  connect(line_edit, SIGNAL(textChanged(const QString&)), this, SIGNAL(textChanged(const QString&)));
  connect(line_edit, SIGNAL(textEdited(const QString&)), this, SIGNAL(textEdited(const QString&)));
  
  QHBoxLayout *margin = new QHBoxLayout();
  margin->addWidget(line_edit);
  margin->addWidget(button);
  margin->setSpacing(0);
  setLayout(margin);
  
  setDialogType(GetFileName);
  setOptions(0);
  line_edit->setFocus();
  
  completer = new QCompleter(this);
  QDirModel *dirModel = new QDirModel(completer);
  completer->setModel(dirModel);
  line_edit->setCompleter(completer);
}

fileChooser::~fileChooser()
{
}

QString fileChooser::text() const
{
  return line_edit->text();
}

bool fileChooser::modification() const
{
  return line_edit->isModified();
}

void fileChooser::setText(const QString & text) {
  line_edit->setText(text);
}

void fileChooser::on_button_clicked() {
  QString result;
  QString f;

  if (dialogType() == GetFileName) {
    QFileDialog::Options opts = options();
    if (opts == 0) opts = QFileDialog::DontResolveSymlinks;

    //result = fileDialog::getOpenFileName( this, caption(), line_edit->text(), filter(), &f, opts );
    result = QFileDialog::getOpenFileName( this, caption(), line_edit->text(), filter(), &f, opts );
  } else if (dialogType() == GetDirectory) {
    QFileDialog::Options opts = options();
    if (opts == 0) opts = QFileDialog::ShowDirsOnly;

    //result = fileDialog::getExistingDirectory(this, caption(), line_edit->text(), opts );
    result = QFileDialog::getExistingDirectory( this, caption(), line_edit->text(), opts );
  }

  if (!result.isEmpty()) {
    line_edit->setText(result);
    line_edit->setModified(1);
    emit lineditChanged(modification());
  }
}

void fileChooser::lineditState()
{
  emit lineditChanged(modification());
}
