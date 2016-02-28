class virtual qAbstractButton' = object(self : 'self)
  inherit QWidget.qWidget'
end

external clicked : unit -> (qAbstractButton', bool -> unit) Signal.t =
  "caml_mrvn_QT5_QAbstractButton_clicked"

class ['a] qAbstractButton proxy = object(self : 'self)
  inherit qAbstractButton'
  inherit ['a] QObject.qObject proxy
  method clicked = clicked ()
end
