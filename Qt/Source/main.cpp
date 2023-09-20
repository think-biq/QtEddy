// Copy:   (c) 2023 blurryroots innovation qanat OÜ
// Author: sven freiberg

#include <Core/Utilities.h>
#include <Editor/MainWindow.h>

#include <QtWidgets/QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QProcess>
#include <QString>

int main (int ac, char **av) {
	// Change log output pattern for verbose file info
	qSetMessagePattern ("%{time}%{file}(%{line}): %{message}");

	QApplication app(ac, av);
	if (1 < ac && QStringLiteral ("dark") == QString (av[1])) {
		qDebug ("Applying dark mode ...");
		Utility::ApplyDarkMode (&app);
	}

	long int pid = QCoreApplication::applicationPid ();
	qDebug ("Running Editor in process %ld ...", pid);

	MainWindow window ("Eddy");
	window.show ();

	return app.exec ();
}
