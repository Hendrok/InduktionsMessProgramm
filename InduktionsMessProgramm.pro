TEMPLATE = subdirs

SUBDIRS += \
    ClassTest \
    InduCore \
    InduViewer

ClassTest.depends= InduCore
InduViewer.depends=ClassTest
