// Copy:   (c) 2023 blurryroots innovation qanat OÜ
// Author: sven freiberg

#pragma once

#include <Core/Macros.h>

#include <QString>
#include <QJsonObject>

struct HermesReceiver;
class QEvent;
class QObject;
class QApplication;

namespace Utility
{

template<typename TKey, typename TValue>
CORE_EXPORT int AppendMap (QMap<TKey, TValue> &core, const QMap<TKey, TValue> &appendix) {
	for (const TKey &k : appendix.keys ()) {
		core.insert (k, appendix[k]);
	}

	return appendix.count();
}

CORE_EXPORT void ApplyDarkMode (QApplication *app);

CORE_EXPORT QJsonObject MergeJsonObjects (const QJsonObject &a, const QJsonObject &b);

CORE_EXPORT QString QObjectToQString (const QObject *o);

CORE_EXPORT bool IsEqual(float f1, float f2);

}