// Copy:   (c) 2023 blurryroots innovation qanat OÜ
// Author: sven freiberg

#pragma once

#include <QtWidgets/QMainWindow>
#include <QString>

class QEvent;

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QString title, QWidget* pParent = nullptr);

	bool event(QEvent *event) override;

private:
	QVector<int> m_keyGuard;
};
