open External

class oObject obj = object(self)
  inherit OClass.oClass obj
  method as_oObject = (self :> oObject)
  method disconnect : Connection.t -> unit
    = fun con -> Connection.disconnect con
end

class virtual event = object(self)
  method external_event event =
    self#event (new OEvent.oEvent event)
  method virtual event : OEvent.oEvent -> bool
end

class virtual timerEvent = object(self)
  method external_timerEvent event =
    self#timerEvent (new OTimerEvent.oTimerEvent event)
  method virtual timerEvent : OTimerEvent.oTimerEvent -> unit
  method virtual as_oObject : oObject
  method qTimerEvent : 'a . (<as_oTimerEvent : OTimerEvent.oTimerEvent; ..> as 'a) -> unit = fun event ->
    let module E = (val (module struct
      type e = oObject OClass.t -> OTimerEvent.t -> unit
      external stub : oObject OClass.t -> OTimerEvent.t -> unit = "caml_mrvn_QT5_OObject_qTimerEvent"
    end) : External with type e = oObject OClass.t -> OTimerEvent.t -> unit)
    in
    E.stub self#as_oObject#obj event#as_oTimerEvent#obj
end

type t = oObject OClass.t

module type Make = sig
  val stub : unit -> #oObject OClass.t
end

class qObject () =
  let obj =
    let module E = (val (module struct
      external stub : unit -> #oObject OClass.t = "caml_mrvn_QT5_OObject_make"
    end) : Make)
    in
    E.stub ()
  in
object
  inherit oObject obj
end

external destroy : oObject OClass.t -> unit = "caml_mrvn_QT5_OObject_destroy"

let destroy obj = destroy obj#as_oObject#obj
