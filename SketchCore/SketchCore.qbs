import "../../Eks/EksBuild" as Eks;

Eks.Library {
  name: "SketchCore"
  toRoot: "../../"

  property bool uiSupport: true

  Depends { name: "ShiftCore" }
  Depends { name: "SketchCoreTest" }

  files: [ "*.h", "*.cpp" ]
}
