TEMPLATE = subdirs

SUBDIRS = mathlib mathgui mathtest guitest

mathgui.depends = mathlib
guitest.depends = mathgui
mathtest.depends = mathlib
