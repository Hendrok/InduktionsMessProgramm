TEMPLATE = subdirs

SUBDIRS += \
    InduCore \
    InduViewer

InduViewer.depends = InduCore
