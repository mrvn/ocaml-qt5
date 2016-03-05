class ['a] oAbstractButton proxy = object
  inherit ['a] OWidget.oWidget proxy
(*  method clicked = clicked ()
*)end

external clicked : unit -> ('a oAbstractButton, bool -> unit) Signal.t =
  "caml_mrvn_QT5_QAbstractButton_clicked"

