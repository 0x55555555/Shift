import "../Eks/EksBuild" as Eks;

Eks.SubModule {
  name: "Shift"
  toRoot: "../"

  moduleSearchPaths: [ "." ]

  references: [
    "ShiftCore/ShiftCore.qbs",
    "ShiftCoreTest/ShiftCoreTest.qbs",
  ]
}
