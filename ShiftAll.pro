TEMPLATE = subdirs

CONFIG += ordered minimal_shift

SUBDIRS = ShiftCore \
          MathsCore \
          RenderCore \
          GraphicsCore \
          ShiftCoreTest \
          SketchCore \
          SketchCore\SketchCoreTest\SketchCoreTest.pro


!minimal_shift {
SUBDIRS += MeshCore/MeshCore.pro
}
