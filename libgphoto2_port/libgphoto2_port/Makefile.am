EXTRA_DIST =


# included by all *.c files containing translated string literals as
# libgphoto2_port/i18n.h
EXTRA_DIST += i18n.h


EXTRA_DIST += compiletime-assert.h


lib_LTLIBRARIES                  = libgphoto2_port.la
libgphoto2_port_la_CFLAGS        =
libgphoto2_port_la_CPPFLAGS      =
libgphoto2_port_la_DEPENDENCIES  =
libgphoto2_port_la_LDFLAGS       =
libgphoto2_port_la_LIBADD        =
libgphoto2_port_la_SOURCES       =

libgphoto2_port_la_CPPFLAGS     += -I$(top_srcdir)
libgphoto2_port_la_CPPFLAGS     += -I$(top_srcdir)/libgphoto2_port
libgphoto2_port_la_CPPFLAGS     += $(AM_CPPFLAGS)

libgphoto2_port_la_LDFLAGS      += -no-undefined

# Notes about the list of exported symbols:
#    gp_* also contains internal symbols which are intended for
#         INTERNAL USE ONLY and should be converted into gpi_* symbols
#    gp_log_* is the gphoto2 logging API for use by
#             - libgphoto2_port and iolibs
#             - libgphoto2      and camlibs
#             - frontends (optional)
#    gp_system_* is a portable interface to a few filesystem functions
#             Used by
#             - libgphoto2_port and iolibs
#             - libgphoto2      and camlibs
#             - the gphoto2 frontend (NOT for other frontends)
#             Other frontends use their respective toolkit (glib, Qt, ...)
#    gp_port_* is the "real" gphoto2_port API for use by
#             - libgphoto2      and camlibs
#             - frontends
#
# Yes, this is messy, but we are going to clean this up.

# EXTRA_DIST                      += libgphoto2_port.sym
EXTRA_DIST                      += libgphoto2_port.ver
if HAVE_ASM_SYMVER
libgphoto2_port_la_DEPENDENCIES += $(srcdir)/libgphoto2_port.ver
libgphoto2_port_la_LDFLAGS      += -Wl,--version-script=$(srcdir)/libgphoto2_port.ver
# else
# libgphoto2_port_la_DEPENDENCIES += $(srcdir)/libgphoto2_port.sym
# libgphoto2_port_la_LDFLAGS      += -export-symbols $(srcdir)/libgphoto2_port.sym
endif

libgphoto2_port_la_LDFLAGS      += -version-info @LIBGPHOTO2_PORT_VERSION_INFO@

# The libtool docs describe these params, but they don't build.
#	"-dlopen" self \
#	"-dlopen" $(top_builddir)/serial/....la \
#	"-dlopen" $(top_builddir)/usb/....la

libgphoto2_port_la_CPPFLAGS     += $(LTDLINCL)
libgphoto2_port_la_LIBADD       += $(LIBLTDL)

libgphoto2_port_la_LIBADD       += $(INTLLIBS)

libgphoto2_port_la_SOURCES      += gphoto2-port-info-list.c
libgphoto2_port_la_SOURCES      += gphoto2-port-info.h
libgphoto2_port_la_SOURCES      += gphoto2-port-locking.c
libgphoto2_port_la_SOURCES      += gphoto2-port-log.c
libgphoto2_port_la_SOURCES      += gphoto2-port-version.c
libgphoto2_port_la_SOURCES      += gphoto2-port.c
libgphoto2_port_la_SOURCES      += gphoto2-port-portability.c
libgphoto2_port_la_SOURCES      += gphoto2-port-result.c

libgphoto2_port_la_DEPENDENCIES += $(top_srcdir)/gphoto2/gphoto2-port-locking.h
libgphoto2_port_la_DEPENDENCIES += $(top_srcdir)/gphoto2/gphoto2-port-version.h
libgphoto2_port_la_DEPENDENCIES += $(top_srcdir)/gphoto2/gphoto2-port-library.h

libgphoto2_port_la_SOURCES      += dll-preload.h

BUILT_SOURCES = dll-preload.h

CLEANFILES = dll-preload.h

dll-preload.h:
	$(AM_V_at)rm -f $@
	$(AM_V_at)echo "#ifndef __DLL_PRELOAD_H__" >> $@
	$(AM_V_at)echo "#define __DLL_PRELOAD_H__" >> $@
	$(AM_V_at)echo >> $@
	$(AM_V_at)echo "struct iolib {" >> $@
	$(AM_V_at)echo "   const char *name;" >> $@
	$(AM_V_at)echo "   const GPPortLibraryType fp_gp_port_library_type;" >> $@
	$(AM_V_at)echo "   const GPPortLibraryList fp_gp_port_library_list;" >> $@
	$(AM_V_at)echo "   const GPPortLibraryOperations fp_gp_port_library_operations;" >> $@
	$(AM_V_at)echo "};" >> $@
	$(AM_V_at)echo >> $@
	$(AM_V_at)echo "extern struct iolib iolibs[];" >> $@
	$(AM_V_at)echo >> $@
	echo "extern struct iolib *get_iolib_by_name(const char *name);" >> $@
	$(AM_V_at)echo >> $@
	$(AM_V_at)echo "#ifdef DEFINE_IOLIBS" >> $@
	$(AM_V_at)echo >> $@
	$(AM_V_at)list="$(IOLIB_LIST)"; for be in $$list; do be=$${be%.la}; \
	echo "extern GPPortType $${be}_gp_port_library_type(void);" >> $@; \
	echo "extern int $${be}_gp_port_library_list(GPPortInfoList *list);" >> $@; \
	echo "extern GPPortOperations *$${be}_gp_port_library_operations(void);" >> $@; \
	echo >> $@; \
	done
	$(AM_V_at)echo "struct iolib iolibs[] = {" >> $@
	$(AM_V_at)list="$(IOLIB_LIST)"; for be in $$list; do be=$${be%.la}; \
	echo "    {\"$$be.la\", $${be}_gp_port_library_type, $${be}_gp_port_library_list, $${be}_gp_port_library_operations}," >> $@; \
	done
	$(AM_V_at)echo "    { NULL, NULL, NULL, NULL }" >> $@
	$(AM_V_at)echo "};" >> $@
	$(AM_V_at)echo >> $@
	$(AM_V_at)echo "struct iolib *get_iolib_by_name(const char *name) {" >> $@
	$(AM_V_at)echo "    struct iolib *lib;" >> $@
	$(AM_V_at)echo "    for (lib = iolibs; lib->name; lib++) {" >> $@
	$(AM_V_at)echo "        if (!strcmp(lib->name, name)) {" >> $@
	$(AM_V_at)echo "            break;" >> $@
	$(AM_V_at)echo "        }" >> $@
	$(AM_V_at)echo "    }" >> $@
	$(AM_V_at)echo "    return lib;" >> $@
	$(AM_V_at)echo "}" >> $@
	$(AM_V_at)echo >> $@
	$(AM_V_at)echo "#endif // DEFINE_IOLIBS" >> $@
	$(AM_V_at)echo >> $@
	$(AM_V_at)echo "#endif // __DLL_PRELOAD_H__" >> $@

