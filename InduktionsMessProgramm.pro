TEMPLATE = subdirs

SUBDIRS += \
    ClassTest \
    InduControl \
    InduControlCore \
    InduCore \
    InduViewer

ClassTest.depends =InduCore
ClassTest.depends =InduCore

