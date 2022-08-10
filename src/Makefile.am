bin_PROGRAMS = agnostics

agnostics_CFLAGS = \
	-I$(top_srcdir) \
	-DPACKAGE_LIB_DIR=\""$(libdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)/agnostics"\" \
	-DPACKAGE_UI_DIR=\""$(datadir)/agnostics/ui"\" \
	-DPACKAGE_BIN_DIR=\""$(bindir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	$(PACKAGE_CFLAGS) \
	$(G_CAST_CHECKS) \
	-Wall

agnostics_SOURCES = agnostics.c

agnostics_includedir = $(includedir)/agnostics

agnostics_include_HEADERS =

agnostics_LDFLAGS = $(DYNAMIC_FLAGS)
agnostics_DEPENDENCIES_EXTRA = $(BUILTIN_PLUGINS)

agnostics_LDADD = \
		$(BUILTIN_PLUGINS) \
		$(PACKAGE_LIBS) \
		$(X11_LIBS) \
		$(INTLLIBS)

EXTRA_DIST =
