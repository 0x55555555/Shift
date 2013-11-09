import "../../Eks/EksBuild" as Eks;

Eks.Library {
  name: "RenderCore"
  toRoot: "../../"

  Depends { name: "Eks3D" }
  Depends { name: "ShiftCore" }

  Export {
    Depends { name: "cpp" }
    Depends { name: "Eks3D" }

    cpp.includePaths: [ "./include" ]
  }
}
