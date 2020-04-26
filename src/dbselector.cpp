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

#include "dbselector.h"
#include "globalvar.h"

dbSelector::dbSelector(QWidget *parent) : QWidget(parent)
{
  QHBoxLayout *lo = new QHBoxLayout( this );
  
  QVBoxLayout *loAv = new QVBoxLayout();
  lo->addLayout( loAv );
  lAvailable = new QLabel( this );
  loAv->addWidget( lAvailable );
  availableListWidget = new QListWidget( this );
  loAv->addWidget( availableListWidget );
  lAvailable->setBuddy( availableListWidget );

  QVBoxLayout *loHBtns = new QVBoxLayout();
  lo->addLayout( loHBtns );
  loHBtns->addStretch( 1 );
  btnSortAscending = new QToolButton( this );
  btnSortAscending->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/view-sort-ascending.png"));
  loHBtns->addWidget( btnSortAscending );
  btnAdd = new QToolButton( this );
  btnAdd->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/list-add.png"));
  loHBtns->addWidget( btnAdd );
  btnRemove = new QToolButton( this );
  btnRemove->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/list-remove.png"));
  loHBtns->addWidget( btnRemove );
  btnSortDescending = new QToolButton( this );
  btnSortDescending->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/view-sort-descending.png"));
  loHBtns->addWidget( btnSortDescending );
  loHBtns->addStretch( 1 );
  
  QVBoxLayout *loS = new QVBoxLayout();
  lo->addLayout( loS );
  lSelected = new QLabel( this );
  loS->addWidget( lSelected );
  selectedListWidget = new QListWidget( this );
  loS->addWidget( selectedListWidget );
  lSelected->setBuddy( selectedListWidget );
  
  QVBoxLayout *loVBtns = new QVBoxLayout();
  lo->addLayout( loVBtns );
  loVBtns->addStretch( 1 );
  btnUp = new QToolButton( this );
  btnUp->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/go-up.png"));
  btnUp->setAutoRepeat( true );
  loVBtns->addWidget( btnUp );
  btnDown = new QToolButton( this );
  btnDown->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/go-down.png"));
  btnDown->setAutoRepeat( true );
  loVBtns->addWidget( btnDown );
  loVBtns->addStretch( 1 );
  
  connect( btnSortAscending, SIGNAL(clicked()), this, SLOT(buttonSortAClicked()) );
  connect( btnAdd, SIGNAL(clicked()), this, SLOT(buttonAddClicked()) );
  connect( btnRemove, SIGNAL(clicked()), this, SLOT(buttonRemoveClicked()) );
  connect( btnSortDescending, SIGNAL(clicked()), this, SLOT(buttonSortDClicked()) );
  connect( btnUp, SIGNAL(clicked()), this, SLOT(buttonUpClicked()) );
  connect( btnDown, SIGNAL(clicked()), this, SLOT(buttonDownClicked()) );
  connect( availableListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(itemDoubleClicked(QListWidgetItem*)) );
  connect( selectedListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(itemDoubleClicked(QListWidgetItem*)) );
  connect( availableListWidget, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(slotCurrentChanged(QListWidgetItem *)) );
  connect( selectedListWidget, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(slotCurrentChanged(QListWidgetItem *)) );
  //setMaximumSize(400, 400);

  setLayout(lo);

  retranslateUi();
}

dbSelector::~dbSelector()
{}

QListWidget *dbSelector::avlbListWidget() const
{
  return availableListWidget;
}

QListWidget *dbSelector::slctdListWidget() const
{
  return selectedListWidget;
}

void dbSelector::buttonSortAClicked()
{
  availableListWidget->sortItems(Qt::AscendingOrder);
}

void dbSelector::buttonSortDClicked()
{
  availableListWidget->sortItems(Qt::DescendingOrder);
}

void dbSelector::buttonAddClicked()
{
  // move all selected items from available to selected listbox
  QList<QListWidgetItem *> list = availableListWidget->selectedItems();
  foreach (QListWidgetItem* item, list) {
    availableListWidget->takeItem( availableListWidget->row( item ) );
    selectedListWidget->insertItem( insertionIndex( selectedListWidget, selectedInsertPolicy ), item );
    selectedListWidget->setCurrentItem( item );
    emit added( item );
  }
  //if ( selectedInsertionPolicy == KActionSelector::Sorted )
  //  selectedListWidget->sortItems();
  selectedListWidget->setFocus();
}

void dbSelector::buttonRemoveClicked()
{
  // move all selected items from selected to available listbox
  QList<QListWidgetItem *> list = selectedListWidget->selectedItems();
  foreach (QListWidgetItem* item, list) {
    selectedListWidget->takeItem( selectedListWidget->row( item ) );
    availableListWidget->insertItem( insertionIndex( availableListWidget, selectedInsertPolicy ), item );
    availableListWidget->setCurrentItem( item );
    emit removed( item );
  }
  //if ( availableInsertionPolicy == Sorted )
  //  availableListWidget->sortItems();
  
  availableListWidget->setFocus();
}

void dbSelector::buttonUpClicked()
{
  int c = selectedListWidget->currentRow();
  if ( c < 1 ) return;
  QListWidgetItem *item = selectedListWidget->item( c );
  selectedListWidget->takeItem( c );
  selectedListWidget->insertItem( c-1, item );
  selectedListWidget->setCurrentItem( item );
  emit movedUp( item );
}

void dbSelector::buttonDownClicked()
{
  int c = selectedListWidget->currentRow();
  if ( c < 0 || c == selectedListWidget->count() - 1 ) return;
  QListWidgetItem *item = selectedListWidget->item( c );
  selectedListWidget->takeItem( c );
  selectedListWidget->insertItem( c+1, item );
  selectedListWidget->setCurrentItem( item );
  emit movedDown( item );
}

QString dbSelector::availableLabel() const
{
  return lAvailable->text();
}

void dbSelector::setAvailableLabel( const QString &text )
{
  lAvailable->setText( text );
}

QString dbSelector::selectedLabel() const
{
  return lSelected->text();
}

void dbSelector::setSelectedLabel( const QString &text )
{
  lSelected->setText( text );
}

void dbSelector::setButtonIcon( const QString &icon, MoveButton button )
{
  switch ( button )
  {
    case ButtonAdd:
      addIcon = icon;
      btnAdd->setIcon( QIcon( icon ) );
    break;
    case ButtonRemove:
      removeIcon = icon;
      btnRemove->setIcon( QIcon( icon ) );
    break;
    case ButtonUp:
      upIcon = icon;
      btnUp->setIcon( QIcon( icon ) );
    break;
    case ButtonDown:
      downIcon = icon;
      btnDown->setIcon( QIcon( icon ) );
    break;
    default:
      qDebug()<<"DbSelector::setButtonIcon: DAINBREAD!";
  }
}

void dbSelector::setButtonIconSet( const QIcon &iconset, MoveButton button )
{
  switch ( button )
  {
    case ButtonAdd:
      btnAdd->setIcon( iconset );
    break;
     case ButtonRemove:
      btnRemove->setIcon( iconset );
    break;
    case ButtonUp:
      btnUp->setIcon( iconset );
    break;
    case ButtonDown:
      btnDown->setIcon( iconset );
    break;
    default:
      qDebug()<<"DbSelector::setButtonIconSet: DAINBREAD!";
  }
}

void dbSelector::setButtonTooltip( const QString &tip, MoveButton button )
{
  switch ( button )
  {
    case ButtonAdd:
      btnAdd->setText( tip );
      btnAdd->setToolTip( tip );
    break;
    case ButtonRemove:
      btnRemove->setText( tip );
      btnRemove->setToolTip( tip );
    break;
    case ButtonUp:
      btnUp->setText( tip );
      btnUp->setToolTip( tip );
    break;
    case ButtonDown:
      btnDown->setText( tip );
      btnDown->setToolTip( tip );
    break;
    default:
      qDebug()<<"DbSelector::setButtonToolTip: DAINBREAD!";
  }
}

void dbSelector::setButtonWhatsThis( const QString &text, MoveButton button )
{
  switch ( button )
  {
    case ButtonAdd:
      btnAdd->setWhatsThis(text );
    break;
    case ButtonRemove:
      btnRemove->setWhatsThis(text );
    break;
    case ButtonUp:
      btnUp->setWhatsThis(text );
    break;
    case ButtonDown:
      btnDown->setWhatsThis(text );
    break;
    default:
      qDebug()<<"DbSelector::setButtonWhatsThis: DAINBREAD!";
  }
}

bool dbSelector::moveOnDoubleClick() const
{
  return mvOnDoubleClick;
}

void dbSelector::setMoveOnDoubleClick( bool b )
{
  mvOnDoubleClick = b;
}

bool dbSelector::keyboardEnabled() const
{
  return kbEnabled;
}

void dbSelector::setKeyboardEnabled( bool b )
{
  kbEnabled = b;
}

bool dbSelector::isSortingEnabled() const
{
  return sortEnabled;
}

void dbSelector::setSortingEnabled( bool b )
{
  sortEnabled = b;
  shwSortingButtons = b;
  if ( b )
  {
    btnSortAscending->show();
    btnSortDescending->show();
  } else {
    btnSortAscending->hide();
    btnSortDescending->hide();
  }
}

dbSelector::InsertionPolicy dbSelector::availableInsertionPolicy() const
{
  return availableInsertPolicy;
}

void dbSelector::setAvailableInsertionPolicy( InsertionPolicy p )
{
  availableInsertPolicy = p;
}

dbSelector::InsertionPolicy dbSelector::selectedInsertionPolicy() const
{
  return selectedInsertPolicy;
}

void dbSelector::setSelectedInsertionPolicy( InsertionPolicy p )
{
  selectedInsertPolicy = p;
}

bool dbSelector::showUpDownButtons() const
{
  return shwUpDownButtons;
}

void dbSelector::setShowUpDownButtons( bool show )
{
  shwUpDownButtons = show;
  if ( show )
  {
    btnUp->show();
    btnDown->show();
  } else {
    btnUp->hide();
    btnDown->hide();
  }
}

void dbSelector::setButtonsEnabled()
{
  btnAdd->setEnabled( availableListWidget->currentRow() > -1 );
  btnRemove->setEnabled( selectedListWidget->currentRow() > -1 );
  btnUp->setEnabled( selectedListWidget->currentRow() > 0 );
  btnDown->setEnabled( selectedListWidget->currentRow() > -1 && selectedListWidget->currentRow() < selectedListWidget->count() - 1 );
}

int dbSelector::insertionIndex( QListWidget *lb, InsertionPolicy policy )
{
  int index;
  switch ( policy )
  {
    case BelowCurrent:
      index = lb->currentRow();
      if ( index > -1 ) index += 1;
    break;
    case AtTop:
      index = 0;
    break;
    default:
    index = -1;
  }
  return index;
}

void dbSelector::moveItem( QListWidgetItem *item )
{
  QListWidget *lbFrom = item->listWidget();
  QListWidget *lbTo;
  if ( lbFrom == availableListWidget )
    lbTo = selectedListWidget;
  else if ( lbFrom == selectedListWidget )
    lbTo = availableListWidget;
  else  //?! somewhat unlikely...
  return;

  InsertionPolicy p = AtBottom;
  //InsertionPolicy p = ( lbTo == availableListWidget ) ?
  //availableInsertionPolicy : selectedInsertionPolicy;
  
  lbFrom->takeItem( lbFrom->row( item ) );
  lbTo->insertItem( insertionIndex( lbTo, p ), item );
  lbTo->setFocus();
  lbTo->setCurrentItem( item );
  
  if ( p == Sorted )
    lbTo->sortItems();
  
  if ( lbTo == selectedListWidget )
    emit added( item );
  else
    emit removed( item );
}

void dbSelector::polish()
{
  setButtonsEnabled();
}

void dbSelector::keyPressEvent( QKeyEvent *e )
{
  if ( ! kbEnabled ) return;
  if ( (e->modifiers() & Qt::ControlModifier) )
  {
    switch ( e->key() )
    {
      case Qt::Key_Right:
        buttonAddClicked();
      break;
      case Qt::Key_Left:
        buttonRemoveClicked();
      break;
      case Qt::Key_Up:
        buttonUpClicked();
      break;
      case Qt::Key_Down:
        buttonDownClicked();
      break;
      default:
        e->ignore();
      return;
    }
  }
  
}

bool dbSelector::eventFilter( QObject *o, QEvent *e )
{
  if ( kbEnabled && e->type() == QEvent::KeyPress )
  {
    if  ( (((QKeyEvent*)e)->modifiers() & Qt::ControlModifier) )
    {
      switch ( ((QKeyEvent*)e)->key() )
      {
        case Qt::Key_Right:
          buttonAddClicked();
        break;
        case Qt::Key_Left:
          buttonRemoveClicked();
        break;
        case Qt::Key_Up:
          buttonUpClicked();
        break;
        case Qt::Key_Down:
          buttonDownClicked();
        break;
        default:
          return QWidget::eventFilter( o, e );
        break;
      }
      return true;
    } else if ( QListWidget *lb = qobject_cast<QListWidget*>(o) ) {
      switch ( ((QKeyEvent*)e)->key() )
      {
        case Qt::Key_Return:
        case Qt::Key_Enter:
        int index = lb->currentRow();
        if ( index < 0 ) break;
        moveItem( lb->item( index ) );
        return true;
      }
    }
  }
  return QWidget::eventFilter( o, e );
}

void dbSelector::itemDoubleClicked( QListWidgetItem *item )
{
  if ( mvOnDoubleClick )
    moveItem( item );
}

void dbSelector::retranslateUi()
{
  lAvailable->setText( tr("&Available:") );
  lSelected->setText( tr("&Selected:") );

  btnAdd->setToolTip( tr("Add selected item(s)") );
  btnRemove->setToolTip( tr("Remove selected item(s)") );
  btnSortAscending->setToolTip( tr("Sort items Ascending") );
  btnSortDescending->setToolTip( tr("Sort items Descending") );
}
