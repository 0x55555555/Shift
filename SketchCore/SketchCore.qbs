import "../../Eks/EksBuild" as Eks;

Eks.Library {
  name: "SketchCore"
  toRoot: "../../"

  property bool uiSupport: true

  Depends { name: "Qt.core" }
  Depends { name: "Eks3D" }
  Depends { name: "ShiftCore" }

  Export {
    Depends { name: "Eks3D" }
    Depends { name: "cpp" }
    cpp.includePaths: [ "./include" ]
  }

  Eks.TestDependency { name: "SketchCoreTest" }
}
