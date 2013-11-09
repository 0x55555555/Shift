import "../../Eks/EksBuild" as Eks;

Eks.Library {
  name: "RenderCore"
  toRoot: "../../"

  Depends { name: "Eks3D" }
  Depends { name: "ShiftCore" }
  Depends { name: "Qt.gui" }

  Export {
    Depends { name: "cpp" }
    Depends { name: "Eks3D" }

    cpp.includePaths: [ "./include" ]
  }
}
