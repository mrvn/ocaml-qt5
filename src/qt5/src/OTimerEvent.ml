open External

class oTimerEvent obj = object(self:'self)
  inherit OEvent.oEvent obj
  method as_oTimerEvent = (self :> oTimerEvent)
  method timerId =
    let module E = (val (module struct
      type e = oTimerEvent OClass.t -> int
      external stub : oTimerEvent OClass.t -> int = "caml_mrvn_QT5_OTimerEvent_timerId"
    end) : External with type e = oTimerEvent OClass.t -> int)
    in
    E.stub self#as_oTimerEvent#obj
end

type t = oTimerEvent OClass.t
