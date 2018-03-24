TEMPLATE = subdirs

CONFIG += ordered
SUBDIRS += src app tester

CONFIG(debug, debug|release) {
    SUBDIRS += tests
    tests.depends = src
}

win32: copydata.commands = $(COPY_DIR) $$shell_path($$PWD/help) $$shell_path($$OUT_PWD/app/help)
!win32: copydata.commands = $(COPY_DIR) $$shell_path($$PWD/help) $$shell_path($$OUT_PWD/app)

first.depends = $(first) copydata

export(first.depends)
export(copydata.commands)

QMAKE_EXTRA_TARGETS += first copydata
