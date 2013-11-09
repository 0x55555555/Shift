import "../../Eks/EksBuild" as Eks;

Eks.Library {
  name: "GraphicsCore"
  toRoot: "../../"

  property bool uiSupport: true

  Depends { name: "ShiftCore" }
  Depends { name: "RenderCore" }
  Depends { name: "MathsCore" }


  Depends {
    condition: uiSupport
    name: "Qt.gui"
  }

  Depends {
    condition: uiSupport
    name: "Qt.widgets"
  }

  Export {
    Depends { name: "cpp" }
    cpp.includePaths: [ "./include" ]
  }
}
