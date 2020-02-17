TEMPLATE = subdirs

SUBDIRS += \
    InduControl \
    InduControlCore \
    InduCore \
    InduViewer \
    Instruments


InduCore.depends=Instruments
InduControlCore.depends=InduCore
InduControl.depends=InduControlCore
InduViewer.depends=InduCore
InduControl.depends=InduControlCore



