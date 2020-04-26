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

#include "aboutdialog.h"
#include "globalvar.h"
#include "langmanager.h"

aboutDialog::aboutDialog(QWidget *parent) : QDialog(parent)
{
  setModal(true);
  
  headerLayout = new QGridLayout;
  headerLayout->setColumnStretch(0, 0);
  headerLayout->setColumnStretch(1, 1);
  headerLayout->setMargin(6);
  
  textLabel = new QLabel(this);
  textLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
  imageLabel = new QLabel(this);
  commentLabel = new QLabel(this);
  commentLabel->setOpenExternalLinks(true);
  commentLabel->setWordWrap(true);
  commentLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
  headerLayout->addWidget(imageLabel, 0, 0, 2, 1);
  headerLayout->addWidget(textLabel, 0, 1);
  //headerLayout->addWidget(commentLabel, 1, 1);
  
  tabWidget = new QTabWidget;
  tabWidget->setUsesScrollButtons(false);
  /*about tab*/
  QString aboutPageText = globalVar::appName() + " - " + globalVar::shortDescription() + '\n';
  aboutPageText += QString(globalVar::appName() + ", is <a href = \"http://www.gnu.org/philosophy/free-sw.html\">free software</a>, distributed under  <a href = \"%1\">GPL licence.</a><br />").arg(globalVar::licenseFile());
  aboutPageText += '\n' + globalVar::copyrightStatement() + '\n';
  aboutPageText += '\n' + QString("<a href=\"%1\">%1</a>").arg(globalVar::homepage()) + '\n';
  QLabel *aboutLabel = new QLabel;
  aboutLabel->setWordWrap(true);
  aboutLabel->setOpenExternalLinks(true);
  aboutLabel->setText(aboutPageText.replace('\n', "<br />"));
  aboutLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
  
  QVBoxLayout *aboutLayout = new QVBoxLayout;
  aboutLayout->addStretch();
  aboutLayout->addWidget(aboutLabel);
  aboutLayout->addStretch();
  
  QWidget *aboutWidget = new QWidget(this);
  aboutWidget->setLayout(aboutLayout);
  tabWidget->addTab(aboutWidget, tr("&About"));
  /*author tab*/
  
  QLabel *authorLabel = new QLabel;
  authorLabel->setWordWrap(true);
  authorLabel->setOpenExternalLinks(true);
  authorLabel->setText(globalVar::author());
  
  QVBoxLayout *authorLayout = new QVBoxLayout;
  authorLayout->addWidget(authorLabel);
  authorLayout->addStretch();
  
  QWidget *authorWidget = new QWidget(this);
  authorWidget->setLayout(authorLayout);
  tabWidget->addTab(authorWidget, tr("A&uthor"));
  /*thanks tab*/
  
  QLabel *thanksLabel = new QLabel;
  thanksLabel->setWordWrap(true);
  thanksLabel->setOpenExternalLinks(true);
  thanksLabel->setText(globalVar::thanks());
  
  QVBoxLayout *thanksLayout = new QVBoxLayout;
  thanksLayout->addWidget(thanksLabel);
  thanksLayout->addStretch();
  
  QWidget *thanksWidget = new QWidget(this);
  thanksWidget->setLayout(thanksLayout);
  tabWidget->addTab(thanksWidget, tr("&Thanks To"));
  /*translation tab*/
  QString translationPageText;
  translationPageText += QString( tr("<table border=\"1\"><tr><th>Flag</th><th>Language</th><th>Author</th><th>Contact</th></tr>" ));

  foreach (QString lang, langManager::foundLangs()) {
    translationPageText += QString( "<tr><td><img src=\"%1\" height=\"20\" width=\"40\"></td><td  align=\"center\">%2</td><td align=\"center\">%3</td><td align=\"center\"><a href=\"mailto:%4\">%4</a></td></tr>" ).arg(globalVar::defaultIcons("22", "flags") + "/" + langManager::coun(lang) + ".png", langManager::lang(lang), langManager::auth(lang), langManager::cont(lang));
  }
  
  QLabel *translationLabel = new QLabel;
  translationLabel->setWordWrap(true);
  translationLabel->setOpenExternalLinks(true);
  translationLabel->setText(translationPageText.replace('\n', "<br />"));
  translationLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
  
  QVBoxLayout *translationLayout = new QVBoxLayout;
  translationLayout->addStretch();
  translationLayout->addWidget(translationLabel);
  translationLayout->addStretch();
  
  QWidget *translationWidget = new QWidget(this);
  translationWidget->setLayout(translationLayout);
  tabWidget->addTab(translationWidget, tr("T&ranslation"));
  /*license tab*/
  QString licenseText;
  
  QFile file(globalVar::licenseFile());
  if (file.open(QIODevice::ReadOnly)) {
    QTextStream str(&file);
    licenseText += str.readAll();
  }
  
  QTextBrowser *licenseBrowser = new QTextBrowser;
  licenseBrowser->setLineWrapMode(QTextEdit::NoWrap);
  licenseBrowser->setText(licenseText);
  
  QVBoxLayout *licenseLayout = new QVBoxLayout;
  licenseLayout->addStretch();
  licenseLayout->addWidget(licenseBrowser);
  licenseLayout->addStretch();
  
  QWidget *licenseWidget = new QWidget(this);
  licenseWidget->setLayout(licenseLayout);
  tabWidget->addTab(licenseWidget, tr("&License"));

  buttonBox = new QDialogButtonBox(Qt::Horizontal);
  closeButton = new QPushButton(this);
  closeButton->setDefault(true);
  buttonBox->addButton(closeButton, QDialogButtonBox::RejectRole);
  connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
  
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->setMargin(0);
  mainLayout->addLayout(headerLayout);
  mainLayout->addWidget(tabWidget);
  mainLayout->addWidget(buttonBox);
  setLayout(mainLayout);
  
  retranslateUi();
}

aboutDialog::~aboutDialog()
{
}

void aboutDialog::retranslateUi()
{
  setWindowIcon(QIcon(globalVar::defaultIcons("22", "apps") + "/" + globalVar::appName() + ".png"));
  
  setWindowTitle(tr("About - %1").arg(globalVar::appName()));
  imageLabel->setPixmap(globalVar::defaultIcons("64", "apps") + "/" + globalVar::appName() + ".png");
  textLabel->setText(tr("<html><font size=\"5\">%1</font><br /><b>Version %2</b><br />Using Qt version %3</html>").arg(globalVar::appName(), globalVar::appVersion(), QLatin1String(QT_VERSION_STR)));
  
  closeButton->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/dialog-close.png"));
  closeButton->setText(tr("&Close"));
}
