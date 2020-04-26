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

#include "colorbutton.h"

#include <QPainter>
#include <QtGui/qdrawutil.h>
#include <QApplication>
#include <QClipboard>
#include <QStyle>
#include <QMouseEvent>
#include <QStyleOptionButton>
#include <QColorDialog>

colorButton::colorButton( QWidget *parent ) : QPushButton( parent )
{
  m_bdefaultColor = false;
  m_defaultColor = QColor();
  setAcceptDrops(true);
  connect (this, SIGNAL(clicked()), this, SLOT(chooseColor()));
}

colorButton::colorButton( const QColor &c, QWidget *parent ) : QPushButton( parent )
{
  col = c;
  m_bdefaultColor = false;
  m_defaultColor = QColor();
  setAcceptDrops( true);
  connect (this, SIGNAL(clicked()), this, SLOT(chooseColor()));
}

colorButton::colorButton( const QColor &c, const QColor &defaultColor, QWidget *parent ) : QPushButton( parent )
{
  col = c;
  m_bdefaultColor = true;
  m_defaultColor = defaultColor;
  setAcceptDrops( true);
  connect (this, SIGNAL(clicked()), this, SLOT(chooseColor()));
}

colorButton::~colorButton()
{
}

QColor colorButton::color() const
{
  return col;
}

void colorButton::setColor( const QColor &c )
{
  if ( col != c ) {
    col = c;
    repaint();
    emit changed( col );
  }
}

QColor colorButton::defaultColor() const
{
  return m_defaultColor;
}

void colorButton::setDefaultColor( const QColor &c )
{
  m_bdefaultColor = c.isValid();
  m_defaultColor = c;
}

void colorButton::initStyleOption(QStyleOptionButton* opt) const
{
    opt->initFrom(this);
    opt->state |= this->isDown() ? QStyle::State_Sunken : QStyle::State_Raised;
    opt->features = QStyleOptionButton::None;
    if (this->isDefault())
      opt->features |= QStyleOptionButton::DefaultButton;
    opt->text.clear();
    opt->icon = QIcon();
}

void colorButton::paintEvent( QPaintEvent* )
{
  QPainter painter(this);

  //First, we need to draw the bevel.
  QStyleOptionButton butOpt;
  initStyleOption(&butOpt);
  style()->drawControl( QStyle::CE_PushButtonBevel, &butOpt, &painter, this );

  //OK, now we can muck around with drawing out pretty little color box
  //First, sort out where it goes
  QRect labelRect = style()->subElementRect( QStyle::SE_PushButtonContents, &butOpt, this );
  int shift = style()->pixelMetric( QStyle::PM_ButtonMargin ) / 2;
  labelRect.adjust(shift, shift, -shift, -shift);
  int x, y, w, h;
  labelRect.getRect(&x, &y, &w, &h);

  if (isChecked() || isDown()) {
    x += style()->pixelMetric( QStyle::PM_ButtonShiftHorizontal );
    y += style()->pixelMetric( QStyle::PM_ButtonShiftVertical   );
  }

  QColor fillCol = isEnabled() ? col : palette().color(backgroundRole());
  qDrawShadePanel( &painter, x, y, w, h, palette(), true, 1, NULL);
  if ( fillCol.isValid() )
    painter.fillRect( x+1, y+1, w-2, h-2, fillCol );

  if ( hasFocus() ) {
    QRect focusRect = style()->subElementRect( QStyle::SE_PushButtonFocusRect, &butOpt, this );
    QStyleOptionFocusRect focusOpt;
    focusOpt.init(this);
    focusOpt.rect            = focusRect;
    focusOpt.backgroundColor = palette().background().color();
    style()->drawPrimitive( QStyle::PE_FrameFocusRect, &focusOpt, &painter, this );
  }
}

QSize colorButton::sizeHint() const
{
  QStyleOptionButton opt;
  initStyleOption(&opt);
  return style()->sizeFromContents(QStyle::CT_PushButton, &opt, QSize(40, 15), this).expandedTo(QApplication::globalStrut());
}

QSize colorButton::minimumSizeHint() const
{
  QStyleOptionButton opt;
  initStyleOption(&opt);
  return style()->sizeFromContents(QStyle::CT_PushButton, &opt, QSize(3, 3), this).expandedTo(QApplication::globalStrut());
}

void colorButton::mousePressEvent( QMouseEvent *e)
{
  mPos = e->pos();
  QPushButton::mousePressEvent(e);
}

void colorButton::chooseColor()
{
  QColor c = color();
  
  if ( m_bdefaultColor ) {
    c = QColorDialog::getColor( m_defaultColor, this );
    if ( c.isValid() )
      setColor( c );
    else
      setColor( m_defaultColor );
  } else {
    c = QColorDialog::getColor( c, this );
    setColor( c );
  }
}
