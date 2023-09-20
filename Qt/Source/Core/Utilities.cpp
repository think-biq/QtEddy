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
	QPalette palette;
	palette.setColor(QPalette::Window, QColor(53, 53, 53));
	palette.setColor(QPalette::WindowText, Qt::white);
	palette.setColor(QPalette::Base, QColor(25, 25, 25));
	palette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
	palette.setColor(QPalette::ToolTipBase, Qt::black);
	palette.setColor(QPalette::ToolTipText, Qt::white);
	palette.setColor(QPalette::Text, Qt::white);
	palette.setColor(QPalette::Button, QColor(53, 53, 53));
	palette.setColor(QPalette::ButtonText, Qt::white);
	palette.setColor(QPalette::BrightText, Qt::red);
	palette.setColor(QPalette::Link, QColor(128, 13, 128));
	palette.setColor(QPalette::Highlight, QColor(128, 13, 128));
	palette.setColor(QPalette::HighlightedText, Qt::black);
	palette.setColor(QPalette::Active, QPalette::Button, QColor(53, 53, 53));
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, Qt::darkGray);
    palette.setColor(QPalette::Disabled, QPalette::WindowText, Qt::darkGray);
    palette.setColor(QPalette::Disabled, QPalette::Text, Qt::darkGray);
    palette.setColor(QPalette::Disabled, QPalette::Light, QColor(53, 53, 53));
	app->setPalette(palette);
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