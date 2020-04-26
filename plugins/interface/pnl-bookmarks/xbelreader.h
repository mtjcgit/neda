#ifndef XBELREADER_H
#define XBELREADER_H

#include <QIcon>
#include <QXmlStreamReader>

class QTreeWidget;
class QTreeWidgetItem;

class XbelReader
{
public:
  XbelReader(QTreeWidget *treeWidget);
  bool read(QIODevice *device);
  QString errorString() const;

private:
  void readXBEL();
  void readTitle(QTreeWidgetItem *item);
  void readSeparator(QTreeWidgetItem *item);
  void readFolder(QTreeWidgetItem *item);
  void readBookmark(QTreeWidgetItem *item);

  QTreeWidgetItem *createChildItem(QTreeWidgetItem *item);
  QXmlStreamReader xml;
  QTreeWidget *treeWidget;
  QIcon folderIcon;
  QIcon bookmarkIcon;
};

#endif
