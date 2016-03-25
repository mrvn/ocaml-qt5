open External

type key =
| Unknown
| Left
| Right
| Down
| Up
| Space
| D

class oKeyEvent obj = object(self:'self)
  inherit OEvent.oEvent obj
  method as_oKeyEvent = (self :> oKeyEvent)
  method key =
    let module E = (val (module struct
      type e = oKeyEvent OClass.t -> int
      external stub : oKeyEvent OClass.t -> int = "caml_mrvn_QT5_OKeyEvent_key"
    end) : External with type e = oKeyEvent OClass.t -> int)
    in
    match E.stub self#as_oKeyEvent#obj with
    | 0x01000012 -> Left
    | 0x01000014 -> Right
    | 0x01000015 -> Down
    | 0x01000013 -> Up
    | 0x20 -> Space
    | 0x44 -> D
    | _ -> Unknown
end

type t = oKeyEvent OClass.t
