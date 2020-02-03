TEMPLATE = subdirs

SUBDIRS += \
    ClassTest \
    InduControlCore \
    InduCore \
    InduViewer

ClassTest.depends =InduCore
ClassTest.depends =InduCore

