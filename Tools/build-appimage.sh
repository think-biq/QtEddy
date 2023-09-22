# Copy:   (c) 2023 blurryroots innovation qanat OÜ
# Author: sven freiberg

# Helper script to make sure environment variables are set and result is
# renamed and located at the desired location.

# Read the root dir of Qt installtion.
QT_ROOT=$1
shift
# Read the desired output file path for appimage.
DESTINATION_FILE=$1
shift
# Read the linuxdeployqt toolpath. 
LINUXDEPLOYQT=$1
shift

# Make Qt installtion availble in path and library search.
export PATH="$PATH:$QT_ROOT/bin"
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$QT_ROOT/lib/"

# Make sure the tool is executable.
chmod +x "$LINUXDEPLOYQT"
# Call deploy tool. Assume the remaining variables are meant for appimage.
echo "Running $LINUXDEPLOYQT ..."
"$LINUXDEPLOYQT" $*

# Copy result to destination file path.
echo "Copying result to $DESTINATION_FILE ..."
cp *.AppImage "$DESTINATION_FILE"
# Make sure app image is executable.
chmod +x "$DESTINATION_FILE"