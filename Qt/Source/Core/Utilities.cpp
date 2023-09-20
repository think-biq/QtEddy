// Copy:   (c) 2023 blurryroots innovation qanat OÜ
// Author: sven freiberg

#include <Core/Utilities.h>

#include <QtGlobal>
#include <QMetaEnum>
#include <QObject>
#include <QPalette>
#include <QtWidgets/QApplication>
#include <QDebug>

namespace Utility {

void ApplyDarkMode (QApplication *app) {
	static QColor A 	( 53,  53,  53);
	static QColor B 	( 25,  25,  25);
	static QColor C 	(128,  13, 128);
	static QColor Black ( 13,   7,  13);
	static QColor Grey 	( 64,  60,  64);
	static QColor White (248, 255, 248);

	QPalette palette;
	palette.setColor (QPalette::Window,								A);
	palette.setColor (QPalette::WindowText,							White);
	palette.setColor (QPalette::Base,								B);
	palette.setColor (QPalette::AlternateBase,						A);
	palette.setColor (QPalette::ToolTipBase,						Black);
	palette.setColor (QPalette::ToolTipText,						White);
	palette.setColor (QPalette::Text,								White);
	palette.setColor (QPalette::Button,								A);
	palette.setColor (QPalette::ButtonText,							White);
	palette.setColor (QPalette::BrightText,							Qt::red);
	palette.setColor (QPalette::Link,								C);
	palette.setColor (QPalette::Highlight,							C);
	palette.setColor (QPalette::HighlightedText,					Black);
	palette.setColor (QPalette::Active, 	QPalette::Button,		A);
    palette.setColor (QPalette::Disabled, 	QPalette::ButtonText,	Grey);
    palette.setColor (QPalette::Disabled, 	QPalette::WindowText,	Grey);
    palette.setColor (QPalette::Disabled, 	QPalette::Text,			Grey);
    palette.setColor (QPalette::Disabled, 	QPalette::Light,		A);
	app->setPalette (palette);
}

QJsonObject MergeJsonObjects (const QJsonObject &a, const QJsonObject &b) {
	QVariantMap map = a.toVariantMap ();
	AppendMap (map, b.toVariantMap ());

	return QJsonObject::fromVariantMap (map);
}

QString QObjectToQString (const QObject *o) {
	if (nullptr == o) {
		return "nullptr";
	}

	return QString (o->metaObject ()->className ());
}

bool IsEqual (float f1, float f2) {
    if (qFuzzyIsNull (qAbs (f1 - f2))) {
        return true;
    }

    return qFuzzyCompare (f1, f2);
}

}