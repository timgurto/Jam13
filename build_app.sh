#!/bin/sh

APP_NAME=Game.app
SRC_EXECUTABLE_NAME=NetBeans6.9.1/dist/Release/GNU-MacOSX/netbeans6.9.1
DST_EXECUTABLE_NAME=game
TOP_DIR=.

# Make package directories
mkdir -p $TOP_DIR/$APP_NAME/Contents/MacOS
mkdir -p $TOP_DIR/$APP_NAME/Contents/Resources

# Scripts and executables
cp $SRC_EXECUTABLE_NAME $TOP_DIR/$APP_NAME/Contents/MacOS/$DST_EXECUTABLE_NAME
cp $TOP_DIR/AppStartup.command $TOP_DIR/$APP_NAME/Contents/MacOS/AppStartup.command
chmod ugo+x $TOP_DIR/$APP_NAME/Contents/MacOS/AppStartup.command

# Packaging info
cp $TOP_DIR/Info.plist $TOP_DIR/$APP_NAME/Contents/Info.plist
cp $TOP_DIR/PkgInfo $TOP_DIR/$APP_NAME/Contents/PkgInfo

# Fonts and icons
cp $TOP_DIR/icon.icns $TOP_DIR/$APP_NAME/Contents/Resources/icon.icns
cp $TOP_DIR/Arial.ttf $TOP_DIR/$APP_NAME/Contents/Resources/Arial.ttf
cp $TOP_DIR/Dina.fon $TOP_DIR/$APP_NAME/Contents/Resources/Dina.fon

# Game resources
cp -Rf $TOP_DIR/Images $TOP_DIR/$APP_NAME/Contents/Resources/Images
cp -Rf $TOP_DIR/Images $TOP_DIR/$APP_NAME/Contents/Resources/Sounds
