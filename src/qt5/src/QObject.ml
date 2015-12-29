class virtual qObject' = object(self : 'self)
(*
  method virtual call : 'b 'c . (('self, 'b) Proxy.fn -> 'c) -> 'b -> 'c
*)
end

class qObject proxy = object(self : 'self)
  inherit qObject'
  val proxy = proxy
(*
  method call fn = Proxy.call proxy fn
*)
end
