type ('a, 'b) t

external connect :
  'a Proxy.t -> ('a, 'b) t -> 'b -> Connection.t
    = "caml_mrvn_QT5_Signal_connect"

class ['a, 'b] signal (proxy : 'a Proxy.t) (signal : ('a, 'b) t) = object
  method connect (fn : 'b) = connect proxy signal fn
end
