class virtual oPushButton' = object(self)
  inherit OAbstractButton.oAbstractButton'
  method as_oPushButton = (self :> oPushButton')
end

type t = oPushButton' Proxy.t

class oPushButton proxy = object
  inherit oPushButton'
  inherit OAbstractButton.oAbstractButton proxy
end

external make : string -> oPushButton Proxy.t = "caml_mrvn_QT5_OPushButton_make"

let make text =
  let proxy = make text
  in
  new oPushButton proxy
