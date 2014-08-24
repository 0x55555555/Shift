import "../Eks/EksBuild" as Eks;

Eks.SubModule {
  name: "Shift"
  toRoot: "../"

  qbsSearchPaths: base.concat( [ "C:/Users/Jorj/SpaceGamez/Eks" ] )

  references: [
    "ShiftCore/ShiftCore.qbs",
    "ShiftCore/ShiftQt.qbs",
    "ShiftCoreTest/ShiftCoreTest.qbs",
    "RenderCore/RenderCore.qbs",
    "GraphicsCore/GraphicsCore.qbs",
    "MathsCore/MathsCore.qbs",
    "SketchCore/SketchCore.qbs",
    "SketchCore/SketchCoreTest/SketchCoreTest.qbs",
  ]


  //"RenderCoreTest/RenderCoreTest.qbs",
  //"MeshCore/MeshCore.qbs",
}
