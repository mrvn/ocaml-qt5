class oPushButton obj = object(self)
  inherit OAbstractButton.oAbstractButton obj
  method as_oPushButton = (self :> oPushButton)
end

type t = oPushButton OClass.t

external external_make : string -> t = "caml_mrvn_QT5_OPushButton_make"

let make text =
  let obj = external_make text
  in
  new oPushButton obj
