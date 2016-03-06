type ('a, 'b) t

external set :
  'a Proxy.t -> ('a, 'b) t -> 'b -> unit
    = "caml_mrvn_QT5_EventHandler_set"

class ['a, 'b] eventHandler (proxy : 'a Proxy.t) (handler : ('a, 'b) t) = object
  method set (fn : 'b) = set proxy handler fn
end
