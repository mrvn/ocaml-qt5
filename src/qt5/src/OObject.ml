class ['a] oObject proxy = object
  inherit ['a] OClass.oClass proxy
  method connect : 'b . ('a, 'b) Signal.t -> 'b -> Connection.t
    = fun signal fn -> Signal.connect proxy signal fn
  method disconnect : Connection.t -> unit
    = fun con -> Connection.disconnect con
end
