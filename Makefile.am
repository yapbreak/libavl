ACLOCAL_AMFLAGS = -I m4

include Makefile.common

SUBDIRS = libavl

ALLPHONY = coverage

################################################################################ if COVERAGE
if COVERAGE

################################################################################	if LCOV
if LCOV
lcov-coverage-clean:
	lcov --compat-libtool --directory "$(top_srcdir)/src" --zerocounters --output-file "coverage-report.info"

lcov-coverage-filter:
	lcov --rc lcov_branch_coverage=1 --compat-libtool --directory "$(top_srcdir)" --capture --output-file "coverage-report.info"
	lcov --rc lcov_branch_coverage=1 --extract "coverage-report.info" "$$(readlink -f $(top_srcdir))/*" --output-file "coverage-report2.info"
	lcov --rc lcov_branch_coverage=1 --remove "coverage-report2.info" "*unittests*" --output-file "coverage-report.info"

###############################################################################			if GENHTML
if GENHTML
GENHTML_EXTRA =

################################################################################			if PERLGD
if PERLGD
GENHTML_EXTRA += --frames
endif
################################################################################			endif

genhtml-coverage-report:
	genhtml --rc lcov_branch_coverage=1 --highlight --legend --demangle-cpp $(GENHTML_EXTRA) --output-directory "coverage-report" --prefix "$$(readlink -f $(top_srcdir))" "coverage-report.info"
################################################################################		else
else
genhtml-coverage-report:
	@(echo "Lcov suite is not completely installed. Please be sure to have genhtml to get beautiful coverage report")

endif
################################################################################		endif

################################################################################	else
else
lcov-coverage-clean:
	@(echo ACH!!!! Caca)

lcov-coverage-filter:
	@(echo ACH!!!! Caca2)

genhtml-coverage-report:
	@(echo ACH!!!! Caca3)

endif
################################################################################	endif

if GCOVR
gcovr-coverage-report:
	gcovr -r . -e "avl_test.*" --xml -o coverage-report.xml
else
gcovr-coverage-report:

endif


coverage-clean: lcov-coverage-clean

coverage-report: lcov-coverage-filter genhtml-coverage-report gcovr-coverage-report

coverage: coverage-clean check coverage-report

ALLPHONY += coverage-clean coverage-report lcov-coverage-clean lcov-coverage-filter genhtml-coverage-report gcovr-coverage-report
else
coverage:
	@(echo "Coverage support is disabled. Re-run configure with --enable-coverage switch.")
endif

CLEANFILES = "coverage-report.info" "coverage-report2.info" "coverage-report" "coverage-report.xml"

clean-local:
	@rm -rf $(CLEANFILES)

.PHONY: $(ALLPHONY)
