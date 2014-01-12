import "../../Eks/EksBuild" as Eks;

Eks.Test {
  name: "RenderCoreTest"
  toRoot: "../../"

  Depends { name: "Qt.widgets" }
  Depends { name: "Qt.opengl" }
  Depends { name: "ShiftCore" }
  Depends { name: "RenderCore" }

  Properties {
    condition: buildtools.osx
    cpp.frameworks: [ "OpenGL" ]
  }
}
