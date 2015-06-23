#include "ImprovedSortFilterProxyModel.h"

ImprovedSortFilterProxyModel::ImprovedSortFilterProxyModel(): QSortFilterProxyModel()
{
}

void ImprovedSortFilterProxyModel::setFilterFixedString(const QString &pattern)
{
	this->QSortFilterProxyModel::setFilterFixedString(pattern);
	this->currentFilterFixedString = pattern;
}

bool ImprovedSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
	CommonLog::Write("lt");
//	auto result = false;
//	QVariant leftData = sourceModel()->data(left);
//	QVariant rightData = sourceModel()->data(right);
//	if (leftData.type() == QVariant::String && rightData.type() == QVariant::String)
//	{
//		auto leftString = leftData.toString();
//		auto rightString = rightData.toString();
//		result = leftString < rightString;
//	}
//	return result;
	return this->QSortFilterProxyModel::lessThan(left, right);
}

