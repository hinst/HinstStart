#ifndef IMPROVEDSORTFILTERPROXYMODEL_H
#define IMPROVEDSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include "CommonLog.h"

class ImprovedSortFilterProxyModel : public QSortFilterProxyModel
{
public:
	ImprovedSortFilterProxyModel();
	void setFilterFixedString(const QString &pattern);
protected:
	QString currentFilterFixedString;
	bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};

#endif // IMPROVEDSORTFILTERPROXYMODEL_H
