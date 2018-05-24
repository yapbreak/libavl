ACLOCAL_AMFLAGS = -I m4

include Makefile.common

SUBDIRS = libavl

ALLPHONY = coverage

################################################################################ if COVERAGE
if COVERAGE

if LCOV

lcov-coverage-clean:
	lcov --compat-libtool --directory "$(top_srcdir)/src" --zerocounters --output-file "coverage-report.info"

lcov-coverage-filter:
	lcov --rc lcov_branch_coverage=1 --compat-libtool --directory "$$(readlink -f "$(top_builddir)/")" --capture --output-file "coverage-report.info"
	lcov --rc lcov_branch_coverage=1 --extract "coverage-report.info" "$$(readlink -f "$(top_srcdir)")/*" --output-file "coverage-report2.info"
	lcov --rc lcov_branch_coverage=1 --remove "coverage-report2.info" "*unittests*" --output-file "coverage-report.info"

if GENHTML

GENHTML_EXTRA = --rc lcov_branch_coverage=1 --highlight --legend --demangle-cpp
if PERLGD
GENHTML_EXTRA += --frames
endif # PERLGD

genhtml-coverage-report:
	genhtml $(GENHTML_EXTRA) --output-directory "coverage-report" --prefix "$$(readlink -f $(top_srcdir))" "coverage-report.info"

else # GENHTML

genhtml-coverage-report:
	@(echo "Lcov suite is not completely installed. Please be sure to have genhtml to get beautiful coverage report")

endif # GENHTML

else # LCOV

lcov-coverage-clean:

lcov-coverage-filter:

genhtml-coverage-report:

endif # LCOV

if LCOV_COBERTURA

lcov-cobertura-report:
	lcov_cobertura "coverage-report.info" -o "coverage-report.xml"

gcovr-coverage-report:

else # LCOV_COBERTURA

lcov-cobertura-report:

if GCOVR

gcovr-coverage-report:
	gcovr -r . --exclude-unreachable-branches --exclude-directories="unittests" --xml -o "coverage-report.xml"
else # GCOVR

gcovr-coverage-report:

endif # GCOVR

endif # LCOV_COBERTURA


coverage-clean: lcov-coverage-clean

coverage-report: lcov-coverage-filter genhtml-coverage-report lcov-cobertura-report gcovr-coverage-report

coverage: coverage-clean check coverage-report

ALLPHONY += coverage-clean
ALLPHONY += coverage-report
ALLPHONY += lcov-coverage-clean
ALLPHONY += lcov-coverage-filter
ALLPHONY += genhtml-coverage-report
ALLPHONY += gcovr-coverage-report
ALLPHONY += lcov-cobertura-report

else # COVERAGE

coverage:
	@(echo "Coverage support is disabled. Re-run configure with --enable-coverage switch.")

endif # COVERAGE

CLEANFILES = "coverage-report.info" "coverage-report2.info" "coverage-report" "coverage-report.xml"

clean-local:
	@rm -rf $(CLEANFILES)

.PHONY: $(ALLPHONY)
