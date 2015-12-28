type 'a ptr

class type qObject_type =
object('self)
  val this : #qObject_type ptr
  method destroy : unit
end

external destroy : #qObject_type ptr -> unit = "qObject_destructor"

class qObject obj =
  (object(self)
    val this = obj
    method destroy =
      Printf.printf "qObject#destroy\n%!";
      destroy this
    initializer Gc.finalise (fun t -> t#destroy) self
   end : qObject_type)
