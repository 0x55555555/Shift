TEMPLATE = subdirs

CONFIG += ordered minimal_shift

SUBDIRS = ShiftCore/shift.pro \
          MathsCore/MathsCore.pro \
          GraphicsCore/GraphicsCore.pro

!minimal_shift {
SUBDIRS += MeshCore/MeshCore.pro
}
