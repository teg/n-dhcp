# ------------------------------------------------------------------------------
# autotools

SHELL = bash
ACLOCAL_AMFLAGS = -I build/m4 ${ACLOCAL_FLAGS}
AM_MAKEFLAGS = --no-print-directory
AUTOMAKE_OPTIONS = color-tests parallel-tests

GCC_COLORS ?= 'ooh, shiny!'
export GCC_COLORS

# remove targets if the command fails
.DELETE_ON_ERROR:

# keep intermediate files
.SECONDARY:

# keep the test-suite.log and Makefile around at all times
.PRECIOUS: $(TEST_SUITE_LOG) Makefile

pkgincludedir=$(includedir)/ndhcp
pkgconfiglibdir=$(libdir)/pkgconfig

BUILT_SOURCES =
CLEANFILES = $(BUILT_SOURCES)
EXTRA_DIST =
pkginclude_HEADERS =
pkgconfiglib_DATA =
noinst_LIBRARIES =
lib_LIBRARIES =
bin_PROGRAMS =
check_PROGRAMS =
TESTS =
default_tests =

AM_CPPFLAGS = \
	-include $(top_builddir)/build/config.h \
	-I $(top_srcdir)/src \
	-I $(top_builddir)/src \
	$(OUR_CPPFLAGS)

AM_CFLAGS = $(OUR_CFLAGS)
AM_LDFLAGS = $(OUR_LDFLAGS)

# ------------------------------------------------------------------------------
# libndhcp.a

noinst_LIBRARIES += \
	libndhcp.a

libndhcp_a_SOURCES = \
	src/libndhcp.sym \
	src/n-dhcp-private.h \
	src/n-dhcp4-client.c \
	src/n-dhcp4-lease.c \
	src/n-dhcp4-message.c \
	src/ndhcp/n-dhcp4-client.h \
	src/ndhcp/n-dhcp4-lease.h

# ------------------------------------------------------------------------------
# libndhcp.so.0

all-local: libndhcp.so.0

pkginclude_HEADERS += \
	src/ndhcp/n-dhcp4-client.h \
	src/ndhcp/n-dhcp4-lease.h

libndhcp.so.0: libndhcp.a $(top_srcdir)/src/libndhcp.sym
	$(AM_V_CCLD)$(LINK) -shared \
	-Wl,-soname=$@ \
	-Wl,--version-script=$(top_srcdir)/src/libndhcp.sym \
	-Wl,--whole-archive libndhcp.a -Wl,--no-whole-archive

CLEANFILES += \
	libndhcp.so.0

install-exec-local:
	@echo " $(MKDIR_P) '$(DESTDIR)$(libdir)'"; \
		$(MKDIR_P) "$(DESTDIR)$(libdir)" || exit 1
	@echo " $(INSTALL) libndhcp.so.0 '$(DESTDIR)$(libdir)'"; \
		$(INSTALL) libndhcp.so.0 "$(DESTDIR)$(libdir)" || exit $$?
	@echo " $(LN_S) -f libndhcp.so.0 '$(DESTDIR)$(libdir)/libndhcp.so'"; \
	$(LN_S) -f libndhcp.so.0 "$(DESTDIR)$(libdir)/libndhcp.so" || exit $$?

uninstall-local:
	@test ! -d "$(DESTDIR)$(libdir)" || \
		{ echo " ( cd '$(DESTDIR)$(libdir)' && rm -f libndhcp.so.0 )"; \
		  rm -f "$(DESTDIR)$(libdir)/libndhcp.so.0"; }

%.pc: %.pc.in
	$(AM_V_GEN)$(SED) \
		-e 's,@includedir\@,$(includedir),g' \
		-e 's,@libdir\@,$(libdir),g' \
		-e 's,@VERSION\@,$(VERSION),g' \
		$< > $@

pkgconfiglib_DATA += \
	src/ndhcp.pc

EXTRA_DIST += \
	src/ndhcp.pc.in

CLEANFILES += \
	src/ndhcp.pc

# ------------------------------------------------------------------------------
# test-api

default_tests += \
	test-api

test_api_SOURCES = \
	src/test-api.c

test_api_LDADD = \
	libndhcp.so.0 # explicitly linked against public library

# ------------------------------------------------------------------------------
# test-message4

default_tests += \
	test-message4

test_message4_SOURCES = \
	src/test-message4.c

test_message4_LDADD = \
	libndhcp.a

# ------------------------------------------------------------------------------
# test suite

AM_TESTS_ENVIRONMENT = LD_LIBRARY_PATH=$(abs_builddir)
check_PROGRAMS += $(default_tests)
TESTS += $(default_tests)

# ------------------------------------------------------------------------------
# check "make install" directory tree

install-tree: all
	rm -rf $(abs_builddir)/install-tree
	$(MAKE) install DESTDIR=$(abs_builddir)/install-tree
	tree $(abs_builddir)/install-tree
.PHONY: install-tree
