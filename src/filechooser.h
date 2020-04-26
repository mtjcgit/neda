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

#ifndef FILECHOOSER_H
#define FILECHOOSER_H

#include <QFileDialog>

class QToolButton;
class QCompleter;
class lineEdit;

/*!
 \class fileChooser
 \brief This class provides file chooser.
*/

class fileChooser : public QWidget
{
Q_OBJECT
Q_PROPERTY(QString text READ text WRITE setText)
Q_PROPERTY(QString caption READ caption WRITE setCaption)
Q_PROPERTY(QString filter READ filter WRITE setFilter)
Q_PROPERTY(DialogType dialogType READ dialogType WRITE setDialogType)
Q_PROPERTY(QFileDialog::Options options READ options WRITE setOptions)

public:
  enum DialogType { GetFileName = 0, GetDirectory = 1 };
  //! Constructor of file chooser.
  fileChooser( QWidget* parent = 0 );
  //! Destructor of file chooser.
  ~fileChooser();

public:
  QString text() const;
  QString caption() const { return _caption; };
  QString filter() const { return _filter; };
  DialogType dialogType() const { return _type; };
  QFileDialog::Options options() const { return _options; };
  bool modification() const;

signals:
  bool lineditChanged(bool);
  QString textChanged(const QString&);
  QString textEdited(const QString&);

public slots:
  void setText(const QString & text);
  void setCaption(const QString & caption) { _caption = caption; };
  void setFilter(const QString & filter) { _filter = filter; };
  void setDialogType( DialogType type) { _type = type; };
  void setOptions( QFileDialog::Options options) { _options = options; };

protected:
  QString _caption;
  QString _filter;
  DialogType _type;
  QFileDialog::Options _options;

protected slots:
  virtual void on_button_clicked();
  virtual void lineditState();

private:
  QToolButton *button;
  QCompleter *completer;
  lineEdit *line_edit;
};

#endif
