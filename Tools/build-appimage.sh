APPIMAGETOOL=$1
DESKTOP=$2
QT_ROOT=$3
DEPLOY_TARGET=$4

chmod +x $APPIMAGETOOL

PATH=$PATH:$QT_ROOT/bin; \
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$QT_ROOT/lib/; \
$APPIMAGETOOL \
	$DESKTOP \
	-appimage -no-translations -no-strip \
	-extra-plugins=iconengines,platformthemes/libqgtk3.so \
	-qmake=$QT_ROOT/bin/qmake

mv *.AppImage $DEPLOY_TARGET