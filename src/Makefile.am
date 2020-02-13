bin_PROGRAMS = piagnostics

piagnostics_CFLAGS = \
	-I$(top_srcdir) \
	-DPACKAGE_LIB_DIR=\""$(libdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)/piagnostics"\" \
	-DPACKAGE_UI_DIR=\""$(datadir)/piagnostics/ui"\" \
	-DPACKAGE_BIN_DIR=\""$(bindir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	$(PACKAGE_CFLAGS) \
	$(G_CAST_CHECKS)

piagnostics_SOURCES = piagnostics.c

piagnostics_includedir = $(includedir)/piagnostics

piagnostics_include_HEADERS =

piagnostics_LDFLAGS = $(DYNAMIC_FLAGS)
piagnostics_DEPENDENCIES_EXTRA = $(BUILTIN_PLUGINS)

piagnostics_LDADD = \
		$(BUILTIN_PLUGINS) \
		$(PACKAGE_LIBS) \
		$(X11_LIBS) \
		$(INTLLIBS)

EXTRA_DIST =
