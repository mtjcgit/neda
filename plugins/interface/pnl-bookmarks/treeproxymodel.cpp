#include "treeproxymodel.h"

treeProxyModel::treeProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
	setFilterCaseSensitivity(Qt::CaseInsensitive);
}

bool treeProxyModel::filterAcceptsRow (int source_row, const QModelIndex& source_parent) const
{
	QModelIndex idx = sourceModel()->index(source_row, 0, source_parent);
	if (sourceModel()->hasChildren(idx))
		return(true);
	return(QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent));
}
