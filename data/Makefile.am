uidir = $(datadir)/piagnostics

ui_in_files = piagnostics.ui
	
ui_DATA = $(ui_in_files)

desktopdir=/usr/share/applications

desktop_in_files= \
	piagnostics.desktop.in \
	$(NULL)
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)
@INTLTOOL_DESKTOP_RULE@

EXTRA_DIST = $(ui_in_files) \
			$(desktop_in_files) \
			$(desktop_DATA) \
			$(NULL)
