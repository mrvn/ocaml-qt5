class virtual oObject' = object(self)
  inherit OClass.oClass'
  method as_oObject = (self :> oObject')
end

type t = oObject' Proxy.t

external handler_event : t -> (oObject', OEvent.t -> bool) EventHandler.t = "caml_mrvn_QT5_OObject_QObject_handler_event"

class oObject proxy = object(self:'self)
  inherit oObject'
  inherit OClass.oClass proxy
  method connect : 'b . ('a, 'b) Signal.t -> 'b -> Connection.t
    = fun signal fn -> Signal.connect proxy signal fn
  method disconnect : Connection.t -> unit
    = fun con -> Connection.disconnect con
  method handler_event =
    new EventHandler.eventHandler self#as_oObject#proxy (handler_event self#as_oObject#proxy)
end
