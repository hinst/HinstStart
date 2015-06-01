#include "CommonUI.h"

CommonUI CommonUI::globalObject;

CommonUI::CommonUI()
{
	fontDatabaseField = nullptr;
}

QString CommonUI::preferredFixedFontName()
{
	return "Consolas";
}

const QFont CommonUI::fixedFont()
{
	auto availableFontNames = fontDatabase()->families();
	if (availableFontNames.contains(preferredFixedFontName()))
	{
		return QFont("Consolas");
	}
	else
	{
		return QFontDatabase::systemFont(QFontDatabase::FixedFont);
	}
}

QFontDatabase *CommonUI::fontDatabase()
{
	if (fontDatabaseField == nullptr)
	{
		fontDatabaseField = new QFontDatabase();
	}
	return fontDatabaseField;
}

CommonUI::~CommonUI()
{
	if (fontDatabaseField != nullptr)
	{
		delete fontDatabaseField;
	}
}

void CommonUI::writeLog(QString text)
{
	qDebug() << text;
}
