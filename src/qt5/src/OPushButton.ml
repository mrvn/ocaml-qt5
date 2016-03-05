class ['a] oPushButton proxy = object
  inherit ['a] OAbstractButton.oAbstractButton proxy
end

external make : string -> 'a oPushButton Proxy.t
  = "caml_mrvn_QT5_OPushButton_make"

let make text =
  let proxy = make text
  in
  new oPushButton proxy
