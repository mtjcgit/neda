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

#include "bookmarkmanager.h"
#include "globalvar.h"

bookMarkmanager::bookMarkmanager()
{
}
/*
bool bookMarkmanager::addBookmarkDialog(QWidget* parent, const QString &word)
{
	if (word.isEmpty()) {
		return false;
	}
	
	QDialog* dialog = new QDialog(parent);
	QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom, dialog);
	QLabel* label = new QLabel(dialog);
	QLineEdit* edit = new QLineEdit(dialog);
	
	QDialogButtonBox* box = new QDialogButtonBox(dialog);
	box->addButton(QDialogButtonBox::Ok);
	box->addButton(QDialogButtonBox::Cancel);
	QObject::connect(box, SIGNAL(rejected()), dialog, SLOT(reject()));
	QObject::connect(box, SIGNAL(accepted()), dialog, SLOT(accept()));
	
	layout->addWidget(label);
	layout->addWidget(edit);
	layout->addWidget(box);
	
	label->setText(tr("Choose location of this bookmark."));
	edit->setText(word);
	edit->setCursorPosition(0);
	dialog->setWindowIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/bookmarks.png"));
	dialog->setWindowTitle(tr("Add New Bookmark"));
	
	QSize size = dialog->size();
	size.setWidth(350);
	dialog->resize(size);
	dialog->exec();
	
	if (dialog->result() == QDialog::Rejected || edit->text().isEmpty()) {
		delete dialog;
		return false;
	}
	
		delete dialog;
		return true;
}*/
