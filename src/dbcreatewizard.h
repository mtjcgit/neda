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

#ifndef DBCREATEWIZARD_H
#define DBCREATEWIZARD_H

#include <QWizard>

class QLabel;
class QComboBox;
class QToolButton;
class lineEdit;
class fileChooser;

/*!
 \class dbcreateWizard
 \brief This class provides database creator wizard.
*/

class dbcreateWizard : public QWizard
{
Q_OBJECT

public:
  //! Constructor of database tool dialog.
  dbcreateWizard(QWidget *parent = 0);
  //! Destructor of database tool dialog.
  ~dbcreateWizard();

public:
  void accept();
  
private:
  //! translations of user interface for database tool dialog.
  void retranslateUi();
};

/*!
 \class introPage
 \brief This class provides introduction page for database creator wizard.
*/

class introPage : public QWizardPage
{
Q_OBJECT

public:
  //! Constructor of introduction page.
  introPage(QWidget *parent = 0);
  
private:
  //! translations of user interface for database tool dialog.
  void retranslateUi();
  
private:
    QLabel *label;
};

/*!
 \class generalInfo
 \brief This class provides general information page for database creator wizard.
*/

class generalInfo : public QWizardPage
{
Q_OBJECT

public:
  //! Constructor of introduction page.
  generalInfo(QWidget *parent = 0);
  
private:
  //! translations of user interface for database tool dialog.
  void retranslateUi();
  //! Return Validation state of inserted informations.
  virtual bool validatePage();
  
private:
  lineEdit *nameLineEdit;
  lineEdit *verLineEdit;
  lineEdit *dscLineEdit;
  lineEdit *authorLineEdit;
  lineEdit *emailLineEdit;
  fileChooser *iconFile;
};

/*!
 \class databaseInfo
 \brief This class provides database information page for database creator wizard.
*/

class databaseInfo : public QWizardPage
{
Q_OBJECT

public:
  //! Constructor of introduction page.
  databaseInfo(QWidget *parent = 0);
  
private:
  //! translations of user interface for database tool dialog.
  void retranslateUi();
  
private:
  QComboBox *typeCombo;
};

/*!
 \class permissionInfo
 \brief This class provides permissions information page for database creator wizard.
*/

class permissionInfo : public QWizardPage
{
Q_OBJECT

public:
  //! Constructor of introduction page.
  permissionInfo(QWidget *parent = 0);
  
private:
  //! translations of user interface for database tool dialog.
  void retranslateUi();
};

/*!
 \class outputFilesPage
 \brief This class provides output files information page for database creator wizard.
*/

class outputFilesPage : public QWizardPage
{
Q_OBJECT

public:
  //! Constructor of introduction page.
  outputFilesPage(QWidget *parent = 0);
  
private:
  //! translations of user interface for database tool dialog.
  void retranslateUi();
  //! Return Validation state of inserted informations.
  virtual bool validatePage();
  
protected slots:
  void on_button_clicked();
  
private:
  //lineEdit *infoLineEdit;
  //lineEdit *dbLineEdit;
  //fileChooser *outputDir;
  QComboBox *pathCombo;
  QToolButton *dirBtn;
};

/*!
 \class conclusionPage
 \brief This class provides conclusion page for database creator wizard.
*/

class conclusionPage : public QWizardPage
{
Q_OBJECT

public:
  //! Constructor of introduction page.
  conclusionPage(QWidget *parent = 0);
  
private:
  //! translations of user interface for database tool dialog.
  void retranslateUi();
  
protected:
  void initializePage();
  
private:
  QLabel *label;
};

#endif
