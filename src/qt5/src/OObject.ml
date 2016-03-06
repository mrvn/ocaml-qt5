class virtual oObject' = object(self)
  inherit OClass.oClass'
  method as_oObject = (self :> oObject')
end

type t = oObject' Proxy.t

class oObject proxy = object(self:'self)
  inherit oObject'
  inherit OClass.oClass proxy
  method connect : 'b . ('a, 'b) Signal.t -> 'b -> Connection.t
    = fun signal fn -> Signal.connect proxy signal fn
  method disconnect : Connection.t -> unit
    = fun con -> Connection.disconnect con
end
