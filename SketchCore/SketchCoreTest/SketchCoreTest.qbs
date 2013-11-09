import "../../../Eks/EksBuild" as Eks;

Eks.Test {
  name: "SketchCoreTest"
  toRoot: "../../../"

  Depends { name: "ShiftCore" }
  Depends { name: "SketchCore" }

  cpp.includePaths: base.concat( [ toRoot + "Shift/ShiftCoreTest" ] )

  files: [ "*.h", "*.cpp" ]
}
