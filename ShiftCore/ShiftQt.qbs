import qbs	
import "../../Eks/EksBuild" as Eks;

Eks.Library {
  name: "ShiftQt"
  toRoot: "../../"

  property bool uiSupport: true

  files: [ "QtExtensions/include/**/*", "QtExtensions/src/**/*" ]
  cpp.includePaths: base.concat([ "QtExtensions/include" ])

  Depends { name: "EksCore" }
  Depends { name: "EksGui" }
  Depends { name: "Qt.gui" }
  Depends { name: "ShiftCore" }

  Export {
    Depends { name: "cpp" }
    Depends { name: "EksCore" }
    Depends { name: "EksGui" }

    cpp.includePaths: [ "./QtExtensions/include" ]
  }
}
