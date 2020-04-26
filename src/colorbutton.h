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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>

/*!
 \class colorButton
 \brief This class provides button for choose color.
*/

/*class QColor;
class QPoint;*/

class colorButton : public QPushButton
{
Q_OBJECT
Q_PROPERTY( QColor color READ color WRITE setColor USER true )
Q_PROPERTY( QColor defaultColor READ defaultColor WRITE setDefaultColor )

public:
  //! Constructor of color button.
  explicit colorButton( QWidget *parent = 0 );
  //! Constructor of a color button with an initial color @p c.
  explicit colorButton( const QColor &c, QWidget *parent = 0 );
  //! Constructor of a color button with an initial color @p c and default color @p defaultColor.
  colorButton( const QColor &c, const QColor &defaultColor, QWidget *parent = 0 );
  //! Destructor of color button.
  ~colorButton();
  
public:
  //! Returns the currently chosen color.
  QColor color() const;
  //! Sets the current color to @p c.
  void setColor( const QColor &c );
  //! Returns the default color or an invalid color, if no default color is set.
  QColor defaultColor() const;
  //! Sets the default color to @p c.
  void setDefaultColor( const QColor &c );
  QSize sizeHint() const;
  QSize minimumSizeHint() const;
  
signals:
  //! Emitted when the color of the widget is changed, either with setColor() or via user selection.
  void changed( const QColor &newColor );
  
protected:
  virtual void paintEvent( QPaintEvent *pe );
  virtual void mousePressEvent( QMouseEvent *e );
  
private:
  void initStyleOption(QStyleOptionButton* opt) const;
  
private slots:
  void chooseColor();
  
private:
  QColor m_defaultColor;
  QColor col;
  QPoint mPos;
  bool m_bdefaultColor;
  bool dragFlag;
};

#endif
