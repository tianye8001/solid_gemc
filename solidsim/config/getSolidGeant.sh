#!/bin/bash

G4PATH=$G4INSTALL/environments/g4py/lib/Geant4/
BASEDIR=`dirname $PWD`
PYLIBDIR=$BASEDIR/pylib
SOLG4NAME=SolidGeant4

echo

if [ -e $G4PATH ]; then
   echo "Copying from $G4PATH"
else
   echo You must build the Geant4 interface first.  See 
   echo the documentation
   exit
fi

if [ -e ../pylib ]; then
    echo "Checking for previous installation..."
    if [ -e ../pylib/$SOLG4NAME ]; then
	echo "Cleaning out previous installation"
	rm -rf ../pylib/$SOLG4NAME
	echo "Done"
    else
	echo "No previous installation found"
    fi
    echo "Copying..."
    cp -r $G4PATH ../pylib/$SOLG4NAME
    echo "Done"

    echo "Modifying..."

    # Add our own nice tagline...
    sed -i '/WWW/a \  Modified for SolidSim Python\' ../pylib/$SOLG4NAME/__init__.py

    # Here is where we strip out the VisManager
    # initialization.  It's existance conflicts
    # with running as we do

    sed -i '/G4VisManager\.GetConcreteInstance/,/gVisManager\.Initialize/d' ../pylib/$SOLG4NAME/__init__.py

else
    echo ""
    echo "You should run this while in config/"
    echo "(sorry I'm too dumb to make it better)"
    echo ""
    exit
fi

echo
echo --- Finished ---
echo "Add $PYLIBDIR"
echo "to \$PYTHONPATH" in your .login, .bashrc, .cshrc, etc...
echo
