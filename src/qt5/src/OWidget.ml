class oWidget obj = object(self)
  inherit OObject.oObject obj
  method as_oWidget = (self :> oWidget)
end

type t = oWidget OClass.t

external make : unit -> t = "caml_mrvn_QT5_OWidget_make"

let make () =
  let obj = make ()
  in
  new oWidget obj
