TEMPLATE = subdirs

SUBDIRS = mathlib mathgui guitest

mathgui.depends = mathlib
guitest.depends = mathgui
mathtest.depends = mathlib
