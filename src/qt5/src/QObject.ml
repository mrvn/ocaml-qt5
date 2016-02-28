class virtual qObject' = object(self : 'self)
end

class ['a] qObject (proxy : 'a Proxy.t) = object(self : 'self)
  inherit qObject'
  val proxy = proxy
  method proxy = proxy
  method connect : 'b . ('a, 'b) Signal.t -> 'b -> 'b Connection.t
    = fun signal fn -> Signal.connect proxy signal fn
  method disconnect : 'b . 'b Connection.t -> unit
    = fun con -> Connection.disconnect con
end
