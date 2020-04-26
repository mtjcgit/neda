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

#ifndef SWITCHLANGUAGEDIALOG_H
#define SWITCHLANGUAGEDIALOG_H

#include <QDialog>

class QLabel;
class QComboBox;
class QDialogButtonBox;

/*!
 \class switchLanguageDialog
 \brief This class provides switch language dialog
*/

class switchLanguageDialog : public QDialog
{
Q_OBJECT

public:
  //! Constructor of switch language dialog.
  switchLanguageDialog(QWidget *parent = 0);
  //! Destructor of switch language dialog.
  ~switchLanguageDialog();

/*public:
  QStringList fileNames;
  QString locale;*/

private:
  void createLanguageList();
  void createButtons();
  void retranslateUi();

private slots:
  void enableApplyBtn(const QString &text);
  void applyBtnClicked();
  void okBtnClicked();

protected:
  void loadSettings();
  void saveSettings();

signals:
  void langChangHappened(const QString &str);

private:
  QLabel *label;
  QComboBox *langComboBox;
  QDialogButtonBox *buttonBox;
  QPushButton *closeButton;
  QPushButton *okButton;
  QPushButton *applyButton;
};

#endif
