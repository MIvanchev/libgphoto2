EXTRA_DIST =


# included by all *.c files containing translated string literals as
# libgphoto2/i18n.h
EXTRA_DIST += i18n.h


# dummy file needed by gtk-doc
EXTRA_DIST += gphoto2-library.c


lib_LTLIBRARIES             = libgphoto2.la
libgphoto2_la_CFLAGS        =
libgphoto2_la_CPPFLAGS      =
libgphoto2_la_DEPENDENCIES  =
libgphoto2_la_LDFLAGS       =
libgphoto2_la_LIBADD        =
libgphoto2_la_SOURCES       =

libgphoto2_la_CPPFLAGS     += -I$(top_srcdir)
libgphoto2_la_CPPFLAGS     += -I$(top_builddir)

libgphoto2_la_CPPFLAGS     += -I$(top_srcdir)/libgphoto2_port
libgphoto2_la_CPPFLAGS     += -I$(top_builddir)/libgphoto2_port

libgphoto2_la_CPPFLAGS     += $(AM_CPPFLAGS)

libgphoto2_la_LDFLAGS      += -no-undefined

# Notes about the list of exported symbols:
#    gp_* also contains internal symbols which are intended for
#         INTERNAL USE ONLY and should be converted into gpi_* symbols
#    gpi_* are for libgphoto2/camlib internal use only
#          NEVER USE gpi_* in frontends!
#    gp_* gphoto2 API, used in
#         - frontends
#           BE AWARE that NOT ALL gp_* FUNCTIONS ARE CONSIDERED PUBLIC.
#
# Yes, this is messy, but we are going to clean this up.

# Keep on using libgphoto2.sym until we actually have a libgphoto2.ver
# version script.
# EXTRA_DIST                 += libgphoto2.ver
EXTRA_DIST                 += libgphoto2.sym
# if HAVE_ASM_SYMVER
# libgphoto2_la_DEPENDENCIES += libgphoto2.ver
# libgphoto2_la_LDFLAGS      += -Wl,--version-script=$(srcdir)/libgphoto2.ver
# else
libgphoto2_la_DEPENDENCIES += libgphoto2.sym
libgphoto2_la_LDFLAGS      += -export-symbols $(srcdir)/libgphoto2.sym
# endif

libgphoto2_la_LDFLAGS      += -version-info @LIBGPHOTO2_VERSION_INFO@

libgphoto2_la_LIBADD       += $(top_builddir)/libgphoto2_port/libgphoto2_port/libgphoto2_port.la

# The libtool docs describe these params, but they don't build.
#	"-dlopen" self \
#	"-dlopen" $(top_builddir)/camlibs/canon/....la \
#	"-dlopen" $(top_builddir)/camlibs/ptp2/....la

libgphoto2_la_CPPFLAGS     += $(LTDLINCL)
libgphoto2_la_LIBADD       += $(LIBLTDL)

libgphoto2_la_CPPFLAGS     += $(LIBEXIF_CFLAGS)
libgphoto2_la_LIBADD       += $(LIBEXIF_LIBS)

libgphoto2_la_LIBADD       += -lm
libgphoto2_la_LIBADD       += $(INTLLIBS)

libgphoto2_la_SOURCES      += gphoto2-abilities-list.c
libgphoto2_la_SOURCES      += ahd_bayer.c
libgphoto2_la_SOURCES      += bayer.c
libgphoto2_la_SOURCES      += bayer.h
libgphoto2_la_SOURCES      += bayer-types.h
libgphoto2_la_SOURCES      += gphoto2-camera.c
libgphoto2_la_SOURCES      += gphoto2-context.c
libgphoto2_la_SOURCES      += exif.c
libgphoto2_la_SOURCES      += exif.h
libgphoto2_la_SOURCES      += gphoto2-file.c
libgphoto2_la_SOURCES      += gphoto2-filesys.c
libgphoto2_la_SOURCES      += gamma.c
libgphoto2_la_SOURCES      += gamma.h
libgphoto2_la_SOURCES      += jpeg.c
libgphoto2_la_SOURCES      += jpeg.h
libgphoto2_la_SOURCES      += gphoto2-list.c
libgphoto2_la_SOURCES      += gphoto2-result.c
libgphoto2_la_SOURCES      += gphoto2-version.c
libgphoto2_la_SOURCES      += gphoto2-setting.c
libgphoto2_la_SOURCES      += gphoto2-widget.c

libgphoto2_la_DEPENDENCIES += $(top_srcdir)/gphoto2/gphoto2-version.h

libgphoto2_la_SOURCES      += dll-preload.h

BUILT_SOURCES = dll-preload.h

CLEANFILES = dll-preload.h

dll-preload.h:
	$(AM_V_at)find ../camlibs -name "Makefile-files" -exec sed -i 's/^\(.*\)_la_\(C\|CPP\)FLAGS\s*=\s*\$$(camlib_\(c\|cpp\)flags)$$/\0 -Dcamera_id=\1_camera_id -Dcamera_abilities=\1_camera_abilities -Dcamera_init=\1_camera_init/g' {} \;
	$(AM_V_at)rm -f $@
	$(AM_V_at)echo "#ifndef __DLL_PRELOAD_H__" >> $@
	$(AM_V_at)echo "#define __DLL_PRELOAD_H__" >> $@
	$(AM_V_at)echo >> $@
	$(AM_V_at)echo "struct camlib {" >> $@
	$(AM_V_at)echo "   const char *name;" >> $@
	$(AM_V_at)echo "   const CameraLibraryIdFunc fp_camera_id;" >> $@
	$(AM_V_at)echo "   const CameraLibraryAbilitiesFunc fp_camera_abilities;" >> $@
	$(AM_V_at)echo "   const CameraLibraryInitFunc fp_camera_init;" >> $@
	$(AM_V_at)echo "};" >> $@
	$(AM_V_at)echo >> $@
	$(AM_V_at)echo "extern struct camlib camlibs[];" >> $@
	$(AM_V_at)echo >> $@
	echo "extern struct camlib *get_camlib_by_name(const char *name);" >> $@
	$(AM_V_at)echo >> $@
	$(AM_V_at)echo "#ifdef DEFINE_CAMLIBS" >> $@
	$(AM_V_at)echo >> $@
	$(AM_V_at)list="$(GP_CAMLIB_SET)"; for be in $$list; do be=$${be%.la}; \
	echo "extern int $${be}_camera_id(CameraText *id);" >> $@; \
	echo "extern int $${be}_camera_abilities(CameraAbilitiesList *list);" >> $@; \
	echo "extern int $${be}_camera_init(Camera *camera, GPContext *context);" >> $@; \
	echo >> $@; \
	done
	$(AM_V_at)echo "struct camlib camlibs[] = {" >> $@
	$(AM_V_at)list="$(GP_CAMLIB_SET)"; for be in $$list; do be=$${be%.la}; \
	echo "    {\"$$be.la\", $${be}_camera_id, $${be}_camera_abilities, $${be}_camera_init}," >> $@; \
	done
	$(AM_V_at)echo "    { NULL, NULL, NULL, NULL }" >> $@
	$(AM_V_at)echo "};" >> $@
	$(AM_V_at)echo >> $@
	$(AM_V_at)echo "struct camlib *get_camlib_by_name(const char *name) {" >> $@
	$(AM_V_at)echo "    struct camlib *lib;" >> $@
	$(AM_V_at)echo "    for (lib = camlibs; lib->name; lib++) {" >> $@
	$(AM_V_at)echo "        if (!strcmp(lib->name, name)) {" >> $@
	$(AM_V_at)echo "            break;" >> $@
	$(AM_V_at)echo "        }" >> $@
	$(AM_V_at)echo "    }" >> $@
	$(AM_V_at)echo "    return lib;" >> $@
	$(AM_V_at)echo "}" >> $@
	$(AM_V_at)echo >> $@
	$(AM_V_at)echo "#endif // DEFINE_CAMLIBS" >> $@
	$(AM_V_at)echo >> $@
	$(AM_V_at)echo "#endif // __DLL_PRELOAD_H__" >> $@

