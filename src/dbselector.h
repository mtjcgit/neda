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

#ifndef DBSELECTOR_H
#define DBSELECTOR_H

#include <QWidget>

class QListWidget;
class QListWidgetItem;
class QToolButton;
class QLabel;

class dbSelector : public QWidget
{
Q_OBJECT
Q_ENUMS( InsertionPolicy MoveButton )
Q_PROPERTY( bool moveOnDoubleClick READ moveOnDoubleClick WRITE setMoveOnDoubleClick )
Q_PROPERTY( bool keyboardEnabled READ keyboardEnabled WRITE setKeyboardEnabled )
Q_PROPERTY( bool isSortingEnabled READ isSortingEnabled WRITE setSortingEnabled )
Q_PROPERTY( QString availableLabel READ availableLabel WRITE setAvailableLabel )
Q_PROPERTY( QString selectedLabel READ selectedLabel WRITE setSelectedLabel )
Q_PROPERTY( InsertionPolicy availableInsertionPolicy READ availableInsertionPolicy WRITE setAvailableInsertionPolicy )
Q_PROPERTY( InsertionPolicy selectedInsertionPolicy READ selectedInsertionPolicy WRITE setSelectedInsertionPolicy )
Q_PROPERTY( bool showUpDownButtons READ showUpDownButtons WRITE setShowUpDownButtons )

public:
  dbSelector(QWidget *parent = 0);
  ~dbSelector();

public:
  QString availableLabel() const;
  void setAvailableLabel( const QString & text );
  QString selectedLabel() const;
  void setSelectedLabel( const QString & text );
  QListWidget *avlbListWidget() const;
  QListWidget *slctdListWidget() const;
  enum MoveButton {ButtonAdd, ButtonRemove, ButtonUp, ButtonDown};
  enum InsertionPolicy {BelowCurrent, Sorted, AtTop, AtBottom};
  void setButtonIcon( const QString &icon, MoveButton button );
  void setButtonIconSet( const QIcon &iconset, MoveButton button );
  void setButtonTooltip( const QString &tip, MoveButton button );
  void setButtonWhatsThis( const QString &text, MoveButton button );
  bool moveOnDoubleClick() const;
  void setMoveOnDoubleClick( bool enable );
  bool keyboardEnabled() const;
  void setKeyboardEnabled( bool enable );
  bool isSortingEnabled() const;
  void setSortingEnabled( bool enable );
  InsertionPolicy availableInsertionPolicy() const;
  void setAvailableInsertionPolicy( InsertionPolicy policy );
  InsertionPolicy selectedInsertionPolicy() const;
  void setSelectedInsertionPolicy( InsertionPolicy policy );
  bool showUpDownButtons() const;
  void setShowUpDownButtons( bool show );
  void setButtonsEnabled();

private:
  QListWidget *availableListWidget, *selectedListWidget;
  QToolButton *btnAdd, *btnRemove, *btnUp, *btnDown, *btnSortAscending, *btnSortDescending;
  QLabel *lAvailable, *lSelected;
  QString addIcon, removeIcon, upIcon, downIcon;
  bool mvOnDoubleClick : 1;
  bool kbEnabled : 1;
  bool shwUpDownButtons : 1;
  bool shwSortingButtons : 1;
  bool sortEnabled : 1;
  InsertionPolicy availableInsertPolicy, selectedInsertPolicy;
  int insertionIndex( QListWidget *lb, InsertionPolicy policy );
  void moveItem( QListWidgetItem *item );
  void retranslateUi();

private slots:
  void buttonSortAClicked();
  void buttonSortDClicked();
  void buttonAddClicked();
  void buttonRemoveClicked();
  void buttonUpClicked();
  void buttonDownClicked();

public slots:
  void polish();

private slots:
  void itemDoubleClicked( QListWidgetItem *item );
  void slotCurrentChanged( QListWidgetItem * ) { setButtonsEnabled(); };

signals:
  void added( QListWidgetItem *item );
  void removed( QListWidgetItem *item );
  void movedUp( QListWidgetItem *item );
  void movedDown( QListWidgetItem *item );

protected:
  void keyPressEvent( QKeyEvent * );
  bool eventFilter( QObject *, QEvent * );
};

#endif
