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

#include "switchlanguagedialog.h"
#include "globalvar.h"
#include "langmanager.h"

switchLanguageDialog::switchLanguageDialog(QWidget *parent) : QDialog(parent)
{
  setWindowIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/change-language.png"));

  label = new QLabel(this);

  langComboBox = new QComboBox;
  langComboBox->setIconSize(QSize(40, 20));
  createLanguageList();
  connect(langComboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(enableApplyBtn(const QString &)));

  createButtons();
  buttonBox = new QDialogButtonBox(Qt::Horizontal);
  buttonBox->addButton(okButton, QDialogButtonBox::AcceptRole);
  buttonBox->addButton(applyButton, QDialogButtonBox::AcceptRole);
  buttonBox->addButton(closeButton, QDialogButtonBox::RejectRole);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(label);
  mainLayout->addWidget(langComboBox);
  mainLayout->addWidget(buttonBox);
  //mainLayout->addLayout(buttonsLayout);
  setLayout(mainLayout);

  retranslateUi();
  loadSettings();
}

switchLanguageDialog::~switchLanguageDialog()
{
}

void switchLanguageDialog::createLanguageList()
{
  langComboBox->clear();
  foreach (QString lang, langManager::foundLangs()) {
    langComboBox->addItem( QIcon(globalVar::defaultIcons("22", "flags") + "/" + langManager::coun(lang) + ".png"), langManager::lang(lang) );
  }
}

void switchLanguageDialog::createButtons()
{
  closeButton = new QPushButton(this);
  closeButton->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/dialog-cancel.png"));
  okButton = new QPushButton(this);
  okButton->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/dialog-ok.png"));
  applyButton = new QPushButton(this);
  applyButton->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/dialog-ok-apply.png"));
  applyButton->setEnabled(false);

  connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
  connect(applyButton, SIGNAL(clicked()), this, SLOT(applyBtnClicked()));
  connect(okButton, SIGNAL(clicked()), this, SLOT(okBtnClicked()));
}

void switchLanguageDialog::retranslateUi()
{
  setWindowTitle(tr("Switch Application Language - %1").arg(globalVar::appName()));
  //setToolTip(globalVar::appName() + " Switch Language.");
  
  label->setText(tr("Please choose the language which should be used for this application:"));
  closeButton->setText(tr("&Cancel"));
  okButton->setText(tr("&Ok"));
  applyButton->setText(tr("&Apply"));
}

void switchLanguageDialog::enableApplyBtn(const QString &text)
{
  applyButton->setEnabled(!text.isEmpty());
}

void switchLanguageDialog::applyBtnClicked()
{
  emit langChangHappened(langManager::foundLangs()[langComboBox->currentIndex()]);
  retranslateUi();
  applyButton->setEnabled(false);
}

void switchLanguageDialog::okBtnClicked()
{
  if (applyButton->isEnabled()) {
  emit langChangHappened(langManager::foundLangs()[langComboBox->currentIndex()]);
  }
  saveSettings();
  close();
}

void switchLanguageDialog::loadSettings()
{
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  
  //langComboBox->setCurrentIndex(settings.value("generals/LanguageIndex").toInt());
  
  if (settings.value("generals/Language").toBool()) {
    langComboBox->setCurrentIndex(langManager::index(settings.value("generals/Language").toString()));
  } else {
    langComboBox->setCurrentIndex(langManager::index(globalVar::defaultLanguage()));
  }
  applyButton->setEnabled(false);
}

void switchLanguageDialog::saveSettings()
{
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  //settings.setValue("generals/LanguageIndex", langComboBox->currentIndex());
  settings.setValue("generals/Language", langManager::foundLangs()[langComboBox->currentIndex()]);
  //settings.setValue("generals/LanguageFile", langManager::file(langManager::foundLangs()[langComboBox->currentIndex()]));
}
