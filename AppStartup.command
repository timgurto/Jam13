#!/bin/sh

EXECUTABLE_NAME=game

# Script for running when packaged in a .app bundle on Mac.
# Get run directory
BASE_DIR=`dirname "$0"`

cd $BASE_DIR/../Resources
exec "$BASE_DIR/$EXECUTABLE_NAME"
