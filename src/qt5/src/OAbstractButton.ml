class virtual oAbstractButton' = object(self)
  inherit OWidget.oWidget'
  method as_oAbstractButton = (self :> oAbstractButton')
end

type t = oAbstractButton' Proxy.t

external clicked : unit -> (oAbstractButton', bool -> unit) Signal.t =
  "caml_mrvn_QT5_QAbstractButton_clicked"

class oAbstractButton proxy = object(self)
  inherit oAbstractButton'
  inherit OWidget.oWidget proxy
  method clicked = new Signal.signal self#as_oAbstractButton#proxy (clicked ())
end

