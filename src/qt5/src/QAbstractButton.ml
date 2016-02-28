class virtual qAbstractButton' = object(self : 'self)
  inherit QWidget.qWidget'
  method virtual connect : unit
end

  external connect : #qAbstractButton' Proxy.t -> unit
    = "caml_mrvn_QT5_QAbstractButton_connect"

class ['a] qAbstractButton proxy = object(self : 'self)
  inherit qAbstractButton'
  inherit ['a] QObject.qObject proxy
  method connect = connect proxy
end
