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
#include <QDebug>

#include "searchbar.h"
#include "globalvar.h"
#include "lineedit.h"

searchBar::searchBar(QWidget *parent) : QWidget(parent)
{
  createActions();
  createMenus();
  
  toolClose = new QToolButton(this);
  toolClose->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/dialog-close.png"));
  toolClose->setAutoRaise(true);
  connect(toolClose, SIGNAL(clicked()), this, SIGNAL(hideSearchBar()));
  connect(toolClose, SIGNAL(clicked()), this, SLOT(hide()));
  
  fndLabel = new QLabel(this);
  patternEdit = new lineEdit(this);
  patternEdit->setMinimumSize(QSize(150, 0));
  patternEdit->selectAll();
  //patternEdit->setFocus(Qt::ShortcutFocusReason);

  connect(patternEdit, SIGNAL(textChanged(const QString&)), this, SLOT(patternChanged(const QString &)));
  connect(patternEdit, SIGNAL(returnPressed()), this, SLOT(onReturnPressed()));
  fndLabel->setBuddy(patternEdit);
  
  toolNext = new QToolButton(this);
  toolNext->setAutoRaise(true);
  toolNext->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  toolNext->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/go-down.png"));
  toolNext->setEnabled(false);
  connect(toolNext, SIGNAL(clicked()), this, SLOT(findNext()));
  
  toolPrevious = new QToolButton(this);
  toolPrevious->setAutoRaise(true);
  toolPrevious->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  toolPrevious->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/go-up.png"));
  toolPrevious->setEnabled(false);
  connect(toolPrevious, SIGNAL(clicked()), this, SLOT(findPrevious()));
  
  optionsTool = new QToolButton(this);
  optionsTool->setAutoRaise(true);
  optionsTool->setPopupMode(QToolButton::MenuButtonPopup);
  optionsTool->setMenu(toolMenu);
  connect(optionsTool, SIGNAL(clicked()), optionsTool, SLOT(showMenu()));
  
  QSpacerItem *spacerItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  
  QHBoxLayout *hboxLayout = new QHBoxLayout(this);
  hboxLayout->setSpacing(0);
  hboxLayout->setMargin(0);
  hboxLayout->addWidget(toolClose);
  hboxLayout->addWidget(fndLabel);
  hboxLayout->addWidget(patternEdit);
  hboxLayout->addWidget(toolNext);
  hboxLayout->addWidget(toolPrevious);
  hboxLayout->addWidget(optionsTool);
  hboxLayout->addItem(spacerItem);
  setLayout(hboxLayout);
  
  retranslateUi();
  /*hidingTimer = new QTimer(this);
  hidingTimer->setSingleShot(true);
  hidingTimer->setInterval(40);
  connect(hidingTimer, SIGNAL(timeout()), this, SIGNAL(hideSearchBar()));*/
}

searchBar::~searchBar()
{
}

void searchBar::createActions()
{
  caseAction = new QAction(this);
  caseAction->setCheckable(true);
  wholeWordsAction = new QAction(this);
  wholeWordsAction->setCheckable(true);
}

void searchBar::createMenus()
{
  toolMenu = new QMenu(this);
  toolMenu->addAction(caseAction);
  toolMenu->addAction(wholeWordsAction);
}

void searchBar::retranslateUi()
{
  fndLabel->setText(tr("Find:"));
  toolNext->setText(tr("&Next"));
  toolPrevious->setText(tr("&Previous"));
  optionsTool->setText(tr("&Options"));
  
  caseAction->setText(tr("Case &Sensitive"));
  wholeWordsAction->setText(tr("Whole &Words"));
  
  toolClose->setToolTip("hide search bar");
  toolClose->setWhatsThis(tr("this object hide search bar."));
  //toolClose->setShortcut(tr("Esc"));
  
  patternEdit->setToolTip("text to search in");
  toolNext->setToolTip("jump to next match");
  toolNext->setWhatsThis(tr("find next"));
  toolPrevious->setToolTip("jump to previous match");
  toolNext->setWhatsThis(tr("find previous"));
}

void searchBar::patternChanged(const QString & text) {
  bool textIsNotEmpty = !text.isEmpty();
  toolNext->setEnabled(textIsNotEmpty);
  toolPrevious->setEnabled(textIsNotEmpty);
  if(textIsNotEmpty)
    findFirst(patternEdit->text(), false, false);
}

void searchBar::findFirst(QString ttf, bool forward, bool backward) {
  QString searchString = patternEdit->text();
  QTextDocument *document = browser->document();
  QTextCursor c = browser->textCursor();
  QTextDocument::FindFlags options;
  QPalette p = patternEdit->palette();
  p.setColor(QPalette::Active, QPalette::Base, Qt::white);
  
  if (c.hasSelection())
    c.setPosition(forward ? c.position() : c.anchor(), QTextCursor::MoveAnchor);
  
  QTextCursor newCursor = c;
  if (!ttf.isEmpty()) {
    if (backward)
      options |= QTextDocument::FindBackward;
    
    if (caseAction->isChecked())
      options |= QTextDocument::FindCaseSensitively;
    
    if (wholeWordsAction->isChecked())
      options |= QTextDocument::FindWholeWords;
    
    newCursor = document->find(searchString, c, options);
    p.setColor(QPalette::Active, QPalette::Base, QColor(187, 249, 207));
    if (newCursor.isNull()) {
      QTextCursor ac(document);
      ac.movePosition(options & QTextDocument::FindBackward ? QTextCursor::End : QTextCursor::Start);
      p.setColor(QPalette::Active, QPalette::Base, QColor(184, 255, 184));
      newCursor = document->find(ttf, ac, options);
      if (newCursor.isNull()) {
  p.setColor(QPalette::Active, QPalette::Base, QColor(247, 231, 231));
  //p.setColor(QPalette::Text, QColor(255, 102, 102));
  newCursor = c;
      } else {
  
      }
    }
  }
  browser->setTextCursor(newCursor);
  patternEdit->setPalette(p);
  /*FIXME*/
  /*if (!this->patternEdit->hasFocus())
  hidingTimer->start();*/
}

void searchBar::findNext()
{
  findFirst(patternEdit->text(), true, false);
}

void searchBar::findPrevious()
{
  findFirst(patternEdit->text(), false, true);
}

void searchBar::onReturnPressed() {
  const Qt::KeyboardModifiers modifiers = QApplication::keyboardModifiers();
  const bool shiftDown = (modifiers & Qt::ShiftModifier) != 0;
  const bool controlDown = (modifiers & Qt::ControlModifier) != 0;
  if (shiftDown) {
    findPrevious();
  } else {
    findNext();
  }
  
  if (controlDown) {
    emit hideSearchBar();
  }
}

void searchBar::setTextWidget(QTextBrowser *textBrowser) {
  browser = textBrowser;
}

void searchBar::showSearchBar()
{
  show();
  if (browser->textCursor().hasSelection())
    patternEdit->setText(browser->textCursor().selectedText());
  
  patternEdit->setFocus(Qt::ShortcutFocusReason);
}

void searchBar::showSearchBar(bool show)
{
  if (show == true || isHidden())
    showSearchBar();
  else
    hide();
}
