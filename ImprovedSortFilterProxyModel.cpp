#include "ImprovedSortFilterProxyModel.h"

ImprovedSortFilterProxyModel::ImprovedSortFilterProxyModel(): QSortFilterProxyModel()
{
}

void ImprovedSortFilterProxyModel::setFilterFixedString(const QString &pattern)
{
	this->QSortFilterProxyModel::setFilterFixedString(pattern);
	this->currentFilterFixedString = pattern;
	this->setSourceModel(this->sourceModel());
}

bool ImprovedSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
	auto result = this->QSortFilterProxyModel::lessThan(left, right);
	if (currentFilterFixedString.length() > 0)
	{
		QVariant leftData = sourceModel()->data(left);
		QVariant rightData = sourceModel()->data(right);
		if (leftData.type() == QVariant::String && rightData.type() == QVariant::String)
		{
			auto leftString = leftData.toString();
			auto rightString = rightData.toString();
			auto leftIndex = leftString.indexOf(currentFilterFixedString, 0, Qt::CaseInsensitive);
			auto rightIndex = rightString.indexOf(currentFilterFixedString, 0, Qt::CaseInsensitive);
			if (leftIndex >= 0 && rightIndex >= 0)
			{
				if (leftIndex == 0 && rightIndex == 0)
				{
					result = leftString.length() < rightString.length();
				}
				else
				{
					result = leftIndex < rightIndex;
				}
			}
		}
	}
	return result;
}

