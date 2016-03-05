type ('a, 'b) t

external connect :
  'a Proxy.t -> ('a, 'b) t -> 'b -> Connection.t
    = "caml_mrvn_QT5_Signal_connect"
