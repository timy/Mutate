#!/bin/sh

cp ../info/mutate.png ~/.local/share/icons
cp ../info/Mutate.desktop ~/.local/share/applications
echo "Copy resource files (desktop and icon)... done"

DIR_CONFIG="$HOME/.config/Mutate"
if [ ! -d $DIR_CONFIG ] ; then
    mkdir -p $DIR_CONFIG
fi
cp -r ../config/* $DIR_CONFIG
chmod -R a+x $DIR_CONFIG/scripts
chmod -R a+w $DIR_CONFIG
echo "Setup configuration files in $DIR_CONFIG... done"
