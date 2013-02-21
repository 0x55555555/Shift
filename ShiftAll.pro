TEMPLATE = subdirs

CONFIG += ordered minimal_shift

SUBDIRS = ShiftCore \
          MathsCore \
          GraphicsCore \
          ShiftCoreTest


!minimal_shift {
SUBDIRS += MeshCore/MeshCore.pro
}
