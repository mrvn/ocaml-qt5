open External

class virtual event = object(self)
  method external_event event =
    self#event (new OEvent.oEvent event)
  method virtual event : OEvent.oEvent -> bool
end

class oObject obj = object(self)
  inherit OClass.oClass obj
  method as_oObject = (self :> oObject)
  method disconnect : Connection.t -> unit
    = fun con -> Connection.disconnect con
end

type t = oObject OClass.t

external make : unit -> t = "caml_mrvn_QT5_OObject_make"

let make () =
  let obj = make ()
  in
  new oObject obj

external destroy : t -> unit = "caml_mrvn_QT5_OObject_destroy"

let destroy obj = destroy obj#as_oObject#obj
