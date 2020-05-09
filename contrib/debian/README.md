
Debian
====================
This directory contains files used to package alnjld/alnjl-qt
for Debian-based Linux systems. If you compile alnjld/alnjl-qt yourself, there are some useful files here.

## alnjl: URI support ##


alnjl-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install alnjl-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your alnjl-qt binary to `/usr/bin`
and the `../../share/pixmaps/alnjl128.png` to `/usr/share/pixmaps`

alnjl-qt.protocol (KDE)

