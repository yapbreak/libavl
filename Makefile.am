ACLOCAL_AMFLAGS = -I m4

include Makefile.common

SUBDIRS = libavl

ALLPHONY = coverage

if COVERAGE
coverage-clean:
	lcov --compat-libtool --directory "$(top_srcdir)" --zerocounters --output-file "$(top_srcdir)/coverage-report.info"

coverage-report:
	lcov --compat-libtool --directory "$(top_srcdir)" --capture --output-file "$(top_srcdir)/coverage-report.info"
	genhtml --highlight --legend --output-directory "$(top_srcdir)/coverage-report" --prefix "$(top_srcdir)" "$(top_srcdir)/coverage-report.info"

coverage: clean coverage-clean all check coverage-report

ALLPHONY += coverage-clean coverage-report
else
coverage:
	@(echo "Coverage support is disabled. Re-run configure with --enable-coverage switch.")
endif

CLEANFILES = $(top_srcdir)/coverage-report.info

clean-local:
	@rm -rf "$(top_srcdir)/coverage-report"


.PHONY: $(ALLPHONY)
