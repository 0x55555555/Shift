import "../Eks/EksBuild" as Eks;

Eks.SubModule {
  name: "Shift"
  toRoot: "../"

  moduleSearchPaths: base.concat( [ "../" ] )

  references: [
    "ShiftCore/ShiftCore.qbs",
    "ShiftCoreTest/ShiftCoreTest.qbs",
    "GraphicsCore/GraphicsCore.qbs",
    "MathsCore/MathsCore.qbs",
    "MeshCore/MeshCore.qbs",
    "SketchCore/SketchCore.qbs",
    "SketchCore/SketchCoreTest/SketchCoreTest.qbs",
  ]
}
