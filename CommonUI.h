#ifndef COMMONUI_H
#define COMMONUI_H

#include <QString>
#include <QDebug>
#include <QFont>
#include <QStringList>
#include <QFontDatabase>

class CommonUI
{
public:
	CommonUI();
	static CommonUI globalObject;
	QString preferredFixedFontName();
	const QFont fixedFont();
	QFontDatabase *fontDatabase();
	~CommonUI();
	void writeLog(QString text);
private:
	QFontDatabase* fontDatabaseField;
};

#endif // COMMONUI_H
