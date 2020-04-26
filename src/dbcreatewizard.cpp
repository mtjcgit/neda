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

#include "globalvar.h"
#include "dbmanager.h"
#include "pluginmanager.h"
#include "filechooser.h"
#include "dbcreatewizard.h"
#include "lineedit.h"

dbcreateWizard::dbcreateWizard(QWidget *parent) : QWizard(parent)
{
  setDefaultProperty("fileChooser", "text", SIGNAL(textChanged()));
  setDefaultProperty("QComboBox", "currentText", SIGNAL(currentIndexChanged()));
  
  addPage(new introPage);
  addPage(new generalInfo);
  addPage(new databaseInfo);
  addPage(new outputFilesPage);
  addPage(new conclusionPage);
  
  /*setOption(HaveHelpButton, true);
  connect(this, SIGNAL(helpRequested()), this, SLOT(showHelp()));*/
  
  retranslateUi();
}

dbcreateWizard::~dbcreateWizard()
{}

void dbcreateWizard::retranslateUi()
{
  setWindowTitle(tr("Create New Database"));
  setPixmap(QWizard::WatermarkPixmap, QPixmap(globalVar::defaultIcons("22", "actions") + "/tools-wizard.png"));
}

void dbcreateWizard::accept()
{ 
  dbManager *newdb = new dbManager();
  newdb->setName(field("general.name").toString());
  newdb->setVersion(field("general.version").toString());
  newdb->setDescription(field("general.dsc").toString());
  newdb->setAuthor(field("general.author").toString());
  newdb->setEmail(field("general.email").toString());
  newdb->setIcon(field("general.icon").toString());
  newdb->setType(field("database.type").toString());
  newdb->setInfoPath(field("output.path").toString());
  QString name = field("general.name").toString().trimmed().toLower().replace(QRegExp("\\s"), "-");
  newdb->setDbName(name);
  newdb->setInfoName(name);
  newdb->setOutDir(field("output.path").toString() + "/" + name);
  //QString aa = field("output.path").toString() + "/" + field("output.info").toString() + "/" + field("output.db").toString();
  QString aa = field("output.path").toString() + "/" + name + "/" + name;
  if (newdb->createNew() && pluginManager::createNew(aa , field("database.type").toString()))
    QDialog::accept();
}

introPage::introPage(QWidget *parent) : QWizardPage(parent)
{
  label = new QLabel(this);
  label->setWordWrap(true);
  
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(label);
  setLayout(layout);
  retranslateUi();
}

void introPage::retranslateUi()
{
  setTitle(tr("Introduction"));
  label->setText(tr("This wizard will help you generate a new database."));
}

generalInfo::generalInfo(QWidget *parent) : QWizardPage(parent)
{
  nameLineEdit = new lineEdit(this);
  registerField("general.name*", nameLineEdit);
  verLineEdit = new lineEdit(this);
  registerField("general.version", verLineEdit);
  dscLineEdit = new lineEdit(this);
  registerField("general.dsc", dscLineEdit);
  authorLineEdit = new lineEdit(this);
  registerField("general.author", authorLineEdit);
  emailLineEdit = new lineEdit(this);
  emailLineEdit->setValidator(new QRegExpValidator(QRegExp(".*@.*"), this));
  registerField("general.email", emailLineEdit);
  // FIXME fix absolute and relative paths
  iconFile = new fileChooser(this);
  iconFile->setDialogType(fileChooser::GetFileName);
  registerField("general.icon", iconFile);
  
  QFormLayout *formLayout = new QFormLayout;
  formLayout->addRow(tr("&Name:"), nameLineEdit);
  formLayout->addRow(tr("&Version:"), verLineEdit);
  formLayout->addRow(tr("&Description:"), dscLineEdit);
  formLayout->addRow(tr("&Author:"), authorLineEdit);
  formLayout->addRow(tr("&E-mail address:"), emailLineEdit);
  formLayout->addRow(tr("&Icon:"), iconFile);
  setLayout(formLayout);
  
  retranslateUi();
}

void generalInfo::retranslateUi()
{
  setTitle(tr("General"));
}

bool generalInfo::validatePage()
{
  if (dbManager::foundDBs().contains(nameLineEdit->text())) {
    QMessageBox::warning ( this, tr("Warning..."), tr("a database already exists with name: '%1'.").arg(nameLineEdit->text()));
    return false;
  }
  return true;
}

databaseInfo::databaseInfo(QWidget *parent) : QWizardPage(parent)
{
  typeCombo = new QComboBox(this);
  registerField("database.type", typeCombo);
  
  foreach (QString plugin, pluginManager::foundPlugins()) {
    if ((pluginManager::group(plugin) == "database") && pluginManager::isEditable(plugin))
      typeCombo->addItem(pluginManager::type(plugin));
  }
  // FIXME add compressional condition
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(typeCombo);
  setLayout(layout);
  retranslateUi();
}

void databaseInfo::retranslateUi()
{
  setTitle(tr("Database"));
  setPixmap(QWizard::WatermarkPixmap, QPixmap(globalVar::defaultIcons("22", "places") + "/database.png"));
}

permissionInfo::permissionInfo(QWidget *parent) : QWizardPage(parent)
{
  retranslateUi();
}

void permissionInfo::retranslateUi()
{
  setTitle(tr("Permissions"));
}

outputFilesPage::outputFilesPage(QWidget *parent) : QWizardPage(parent)
{
  /*infoLineEdit = new lineEdit(this);
  registerField("output.info*", infoLineEdit);*/
  // FIXME check if database exists already
  /*dbLineEdit = new lineEdit(this);
  registerField("output.db*", dbLineEdit);*/
  /*outputDir = new fileChooser(this);
  outputDir->setDialogType(fileChooser::GetDirectory);
  // FIXME *
  registerField("output.dir*", outputDir);*/
  QCompleter *completer = new QCompleter(this);
  QDirModel *dirModel = new QDirModel(completer);
  completer->setModel(dirModel);
  
  pathCombo = new QComboBox(this);
  pathCombo->setEditable(true);
  //pathCombo->setLineEdit(lineEdit);
  pathCombo->setCompleter(completer);
  registerField("output.path", pathCombo);
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  QStringList dbdirs = settings.value("directories/dbDires").toString().split(", ", QString::SkipEmptyParts);
  dirBtn = new QToolButton(this);
  dirBtn->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/document-open-folder.png"));
  connect(dirBtn, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
  
  foreach (QString path, dbdirs) {
    pathCombo->addItem(path);
  }
  
  //QFormLayout *formLayout = new QFormLayout;
  //formLayout->addRow(tr("&Info File Name:"), infoLineEdit);
  //formLayout->addRow(tr("&Database File Name:"), dbLineEdit);
  //formLayout->addRow(tr("&Database Output Directory:"), outputDir);
  QLabel *label = new QLabel(tr("&Info File Path:"));
  QHBoxLayout *margin = new QHBoxLayout(this);
  margin->addWidget(label);
  margin->addWidget(pathCombo);
  margin->setSpacing(0);
  margin->addWidget(dirBtn);
  margin->setSpacing(0);
  //formLayout->addRow(tr("&Info File Path:"), margin);
  //setLayout(formLayout);
  setLayout(margin);

  retranslateUi();
}

void outputFilesPage::retranslateUi()
{
  setTitle(tr("Output Files"));
  setPixmap(QWizard::WatermarkPixmap, QPixmap(globalVar::defaultIcons("22", "actions") + "/folder-new.png"));
}

bool outputFilesPage::validatePage()
{
 /*  if () {
    QMessageBox::fatal ( this, tr("Error..."), tr("a database already exists with name: '%1'.").arg(nameLineEdit->text()));
    return false;
  }*/
  return true;
}

void outputFilesPage::on_button_clicked() {
  QString result;
  result = QFileDialog::getExistingDirectory( this, "Select Database Path...", pathCombo->currentText(), QFileDialog::ShowDirsOnly );
  if (!result.isEmpty()) {
    //pathCombo->addItem(result);
    pathCombo->insertItem(0, result);
    pathCombo->setCurrentIndex(0);
  }
}

conclusionPage::conclusionPage(QWidget *parent) : QWizardPage(parent)
{
  label = new QLabel(this);
  label->setWordWrap(true);
  
  // FIXME add check box if the "Info File Path" is not in "dbdirs" settings.
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(label);
  setLayout(layout);
  
  retranslateUi();
}

void conclusionPage::retranslateUi()
{
  setTitle(tr("Conclusions..."));
}

void conclusionPage::initializePage()
{
  QString finishText = wizard()->buttonText(QWizard::FinishButton);
  finishText.remove('&');
  label->setText(tr("Click %1 to generate the information file and database file.").arg(finishText));
}