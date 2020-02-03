TEMPLATE = subdirs

SUBDIRS += \
    ClassTest \
    InduCore \
    InduViewer

InduViewer.depends= InduCore
ClassTest.depends =InduViewer

