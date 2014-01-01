import "../../Eks/EksBuild" as Eks;

Eks.Test {
  property bool windows: qbs.targetOS == "windows"
  property bool linux: qbs.targetOS == "linux"
  property bool osx: !windows && !linux

  name: "RenderCoreTest"
  toRoot: "../../"

  Depends { name: "Qt.widgets" }
  Depends { name: "Qt.opengl" }
  Depends { name: "ShiftCore" }
  Depends { name: "RenderCore" }

  files: [ "*.h", "*.cpp", "*.qrc" ]

  Properties {
    condition: osx
    cpp.frameworks: [ "OpenGL" ]
  }
}
