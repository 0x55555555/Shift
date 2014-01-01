import "../Eks/EksBuild" as Eks;

Eks.SubModule {
  name: "Shift"
  toRoot: "../"

  qbsSearchPaths: base.concat( [ "C:/Users/Jorj/SpaceGamez/Eks" ] )

  references: [
    "ShiftCore/ShiftCore.qbs",
    "ShiftCoreTest/ShiftCoreTest.qbs",
    "RenderCore/RenderCore.qbs",
    "RenderCoreTest/RenderCoreTest.qbs",
    "GraphicsCore/GraphicsCore.qbs",
    "MathsCore/MathsCore.qbs",
    //"MeshCore/MeshCore.qbs",
    "SketchCore/SketchCore.qbs",
    "SketchCore/SketchCoreTest/SketchCoreTest.qbs",
  ]
}
