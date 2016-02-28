class virtual qPushButton' = object(self : 'self)
  inherit QAbstractButton.qAbstractButton'
end

external create : string -> qPushButton' Proxy.t = "caml_mrvn_QT5_QPushButton_create"

class ['a] qPushButton proxy = object(self : 'self)
  inherit qPushButton'
  inherit ['a] QAbstractButton.qAbstractButton proxy
end

let make text =
  let proxy = create text
  in
  new qPushButton proxy
