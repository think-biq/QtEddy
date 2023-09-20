// Copy:   (c) 2023 blurryroots innovation qanat OÜ
// Author: sven freiberg

#include <Editor/MainWindow.h>

#include <QEvent>
#include <QMenuBar>
#include <QDebug>
#include <QCoreApplication>
#include <QFileDialog>
#include <QDebug>
#include <QMessageLogger>
#include <QTextStream>
#include <QKeyEvent>

#define LOG QMessageLogger(__FILE__, __LINE__, "MainWindow")

MainWindow::MainWindow (QString title, QWidget* pParent)
: QMainWindow (pParent) {
	#if WIN32
	addToolBar (title);
	#endif
	setWindowTitle (title);
}

bool MainWindow::event (QEvent *event) {
	switch (event->type ()) {
		case (QEvent::KeyPress): {
			auto e = dynamic_cast<QKeyEvent *>(event);

			if (!m_keyGuard.contains (e->key ())) {
				m_keyGuard.append (e->key ());

				switch (e->key ()) {
				case (Qt::Key_Escape): {
					close ();
				} break;

				case (Qt::Key_F4): {
					if (m_keyGuard.contains (Qt::Key_Alt)) {
						close ();
					}
				} break;

				default:
					break;
				}
			}
		} break;

		case (QEvent::KeyRelease): {
			auto e = dynamic_cast<QKeyEvent *>(event);
			
			#if 0
			switch (e->key())
			{
			default:
				break;
			}
			#endif

			if (m_keyGuard.contains (e->key ())) {
				m_keyGuard.removeAt (m_keyGuard.indexOf (e->key ()));
			}
		} break;

		default:
			break;
	}

	return QMainWindow::event (event);
}
