
Debian
====================
This directory contains files used to package alnjd/alnj-qt
for Debian-based Linux systems. If you compile alnjd/alnj-qt yourself, there are some useful files here.

## alnj: URI support ##


alnj-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install alnj-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your alnj-qt binary to `/usr/bin`
and the `../../share/pixmaps/alnj128.png` to `/usr/share/pixmaps`

alnj-qt.protocol (KDE)

