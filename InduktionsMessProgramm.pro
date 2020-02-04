TEMPLATE = subdirs

SUBDIRS += \
    ClassTest \
    InduControl \
    InduControlCore \
    InduCore \
    InduViewer

ClassTest.depends =InduCore
InduControlCore.depends=InduCore
ClassTest.depends =InduControlCore


