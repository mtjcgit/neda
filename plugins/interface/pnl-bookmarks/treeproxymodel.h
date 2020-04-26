#ifndef TREEPROXYMODEL_H
#define TREEPROXYMODEL_H

#include <QSortFilterProxyModel>

class treeProxyModel : public QSortFilterProxyModel
{
public:
	treeProxyModel(QObject *parent = 0);

protected:
	bool filterAcceptsRow (int source_row, const QModelIndex& source_parent) const;
};

#endif
