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

#include <QToolButton>
#include <QStyle>
#include <QtGui/QContextMenuEvent>

#include "lineedit.h"
#include "globalvar.h"

lineEdit::lineEdit(QWidget *parent) : QLineEdit(parent)
{
  clearButton = new QToolButton(this);
  //clearButton->setIcon(QIcon(pixmap));
  //clearButton->setIconSize(pixmap.size());
  clearButton->setCursor(Qt::ArrowCursor);
  clearButton->setStyleSheet("QToolButton { border: none; padding: 0px; }");
  clearButton->hide();
  connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
  connect(this, SIGNAL(textChanged(const QString&)), this, SLOT(updateCloseButton(const QString&)));
  int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
  setStyleSheet(QString("QLineEdit { padding-right: %1px; } ").arg(clearButton->sizeHint().width() + frameWidth + 1));
  QSize msz = minimumSizeHint();
  setMinimumSize(qMax(msz.width(), clearButton->sizeHint().height() + frameWidth * 2 + 2), qMax(msz.height(), clearButton->sizeHint().height() + frameWidth * 2 + 2));
  
  createActions();
  retranslateUi();
}

void lineEdit::resizeEvent(QResizeEvent *)
{
  QSize sz = clearButton->sizeHint();
  int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
  
  if (layoutDirection() == Qt::LeftToRight ) {
    clearButton->move(rect().right() - frameWidth - sz.width(), (rect().bottom() + 1 - sz.height())/2);
  } else {
    clearButton->move(frameWidth, (rect().bottom() + 1 - sz.height())/2);
  }
  
  caseAction->setText(tr("Case &Sensitive"));
}

void lineEdit::contextMenuEvent(QContextMenuEvent *event) {
  menu = createStandardContextMenu();
  menu->addAction(caseAction);
  menu->exec(event->globalPos());
  delete menu;
}

void lineEdit::createActions()
{
  caseAction = new QAction(this);
  caseAction->setCheckable(true);
}

void lineEdit::updateCloseButton(const QString& text)
{
  clearButton->setVisible(!text.isEmpty());
}

void lineEdit::retranslateUi()
{
  if (layoutDirection() == Qt::RightToLeft) {
    clearButton->setIcon(QIcon(globalVar::defaultIcons("16", "actions") + "/edit-clear-locationbar-ltr.png"));
  } else {
    clearButton->setIcon(QIcon(globalVar::defaultIcons("16", "actions") + "/edit-clear-locationbar-rtl.png"));
  }
  clearButton->setToolTip(tr("Clear current text in the line edit"));
}

