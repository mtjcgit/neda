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

#include "tipdialog.h"
#include "globalvar.h"
#include "langmanager.h"

tipDialog::tipDialog(QWidget *parent) : QDialog(parent)
{
  setWindowIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/tip.png"));

  bool isTipDialog = (parent != 0);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->setMargin( 0 );
  mainLayout->setSpacing( 12 );
  setLayout(mainLayout);

  if ( isTipDialog ) {
    titleLabel = new QLabel( this );
    //titleLabel->setFont( QFont( KGlobalSettings::generalFont().family(), 20, QFont::Bold ) );
    titleLabel->setAlignment( Qt::AlignCenter );
    mainLayout->addWidget( titleLabel );
  }

  QHBoxLayout *browserLayout = new QHBoxLayout();
  browserLayout->setMargin( 0 );
  mainLayout->addLayout( browserLayout );

  tipText = new QTextBrowser( this );
  tipText->setOpenExternalLinks( true );
  tipText->setWordWrapMode( QTextOption::WrapAtWordBoundaryOrAnywhere );

  QStringList paths;
  paths << globalVar::tips() << globalVar::defaultIcons("22", "actions") << globalVar::defaultIcons("22", "apps") << globalVar::dataPath() << "." << "/usr/local/share/icons";
  tipText->setSearchPaths( paths );

  tipText->setFrameStyle( QFrame::NoFrame );
  tipText->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
  QPalette tipPal(tipText->palette());
  tipPal.setColor(QPalette::Base, Qt::transparent);
  tipText->setPalette(tipPal);

  browserLayout->addWidget( tipText );

  QLabel *label = new QLabel( this );
  label->setPixmap( QPixmap(globalVar::dataPath() + "/qtip.png") );
  label->setAlignment( Qt::AlignRight | Qt::AlignVCenter );
  browserLayout->addWidget( label );

  if ( !isTipDialog ) {
  resize( 520, 280 );
  QSize sh = size();
  //QRect rect = KGlobalSettings::splashScreenDesktopGeometry();
  //move( rect.x() + ( rect.width() - sh.width() ) / 2, rect.y() + ( rect.height() - sh.height() ) / 2 );
  }

  QHBoxLayout *buttonLayout = new QHBoxLayout();
  mainLayout->addLayout( buttonLayout );

  tipOnStart = new QCheckBox(this);
  buttonLayout->addWidget( tipOnStart, 1 );
  
  prvBtn = new QPushButton(this);
  buttonLayout->addWidget(prvBtn);

  nxtBtn = new QPushButton(this);
  buttonLayout->addWidget(nxtBtn);

  okBtn = new QPushButton(this);
  buttonLayout->addWidget(okBtn);
  okBtn->setDefault( true );
  okBtn->setFocus();

  QSettings settings(globalVar::config(), QSettings::IniFormat);
  tipOnStart->setChecked( settings.value("generals/RunTipOnStart").toBool() );

  connect(nxtBtn, SIGNAL(clicked()), this, SLOT(nextTip()));
  connect(prvBtn, SIGNAL(clicked()), this, SLOT(prevTip()));
  connect(okBtn, SIGNAL(clicked()), this, SLOT(close()));
  connect(tipOnStart, SIGNAL(toggled(bool)), this, SLOT(showOnStart(bool)));

  // FIXME add tips for current language.
  tipDatabase(globalVar::tips() + "/" + langManager::current());
  nextTip();

  retranslateUi();
}

tipDialog::~tipDialog()
{
}

void tipDialog::showOnStart(bool on)
{
  setShowOnStart( on );
}

void tipDialog::setShowOnStart( bool on )
{
  QSettings settings(globalVar::config(), QSettings::IniFormat);
  settings.setValue("generals/RunTipOnStart", on);	/*stores settings*/
}

void tipDialog::addTips( const QString &tipFile )
{
  QString fileName = tipFile;
  if ( fileName.isEmpty() ) {
    qDebug() << "TipDatabase::addTips: can't find '" << tipFile << "' in standard dirs";
    return;
  }

  QFile file( fileName );
  if ( !file.open( QIODevice::ReadOnly ) ) {
    qDebug() << "TipDatabase::addTips: can't open '" << fileName << "' for reading";
    return;
  }

  QByteArray data = file.readAll();
  QString content = QString::fromUtf8( data.constData(), data.size() );
  const QRegExp rx( "\\n+" );

  int pos = -1;
  while ( ( pos = content.indexOf( "<html>", pos + 1, Qt::CaseInsensitive ) ) != -1 ) {
    QString tip = content.mid( pos + 6, content.indexOf( "</html>", pos, Qt::CaseInsensitive ) - pos - 6 ).replace( rx, "\n" );

    if ( !tip.endsWith( '\n' ) )
      tip += '\n';

    if ( tip.startsWith( '\n' ) )
      tip = tip.mid( 1 );

    if ( tip.isEmpty() ) {
      qDebug() << "Empty tip found! Skipping! " << pos;
      continue;
    }

  tips.append( tip );
  }

  file.close();
}

void tipDialog::loadTips(const QString &tipFile)
{
  tips.clear();
  addTips( tipFile );
}

void tipDialog::tipDatabase( const QString &tipFile )
{
  loadTips( tipFile );

  if ( !tips.isEmpty() )
    currentTip = qrand() % tips.count();
}

QString tipDialog::tip() const
{
  if ( tips.isEmpty() )
    return QString();

  return tips[ currentTip ];
}

void tipDialog::nextTip()
{
  if ( tips.isEmpty() )
    return;

  currentTip += 1;

  if ( currentTip >= (int) tips.count() )
    currentTip = 0;

  tipText->setHtml( QString::fromLatin1( "<html><center>%1</center></html>" ).arg( tr(tip().toUtf8() ) ) );

}

void tipDialog::prevTip()
{
  if ( tips.isEmpty() )
    return;

  currentTip -= 1;
  
  if ( currentTip < 0 )
    currentTip = tips.count() - 1;

  tipText->setHtml( QString::fromLatin1( "<html><center>%1</center></html>" ).arg( tr( tip().toUtf8() ) ) );
}

void tipDialog::retranslateUi()
{
  setWindowTitle(tr("Tip of the Day - %1").arg(globalVar::appName()));
  //setToolTip("Tip of the Day.");

  titleLabel->setText( tr( "Did you know...?\n" ) );
  tipOnStart->setText( tr( "&Show tips on startup" ) );

  prvBtn->setText(tr("&Previous"));
  prvBtn->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/go-previous.png"));
  nxtBtn->setText(tr("&Next"));
  nxtBtn->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/go-next.png"));
  okBtn->setText(tr("&Close"));
  okBtn->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/dialog-close.png"));
}
