TEMPLATE = subdirs

SUBDIRS += \
    InduControl \
    InduControlCore \
    InduCore \
    InduViewer



InduControlCore.depends=InduCore
ClassTest.depends =InduControlCore
InduControl.depends=InduControlCore
InduViewer.depends=InduCore
InduControl.depends=InduControlCore

