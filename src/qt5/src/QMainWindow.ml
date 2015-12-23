type t

external create : unit -> t = "qMainWindow_constructor"
external destroy : t -> unit = "qMainWindow_destructor"
external show : t -> unit = "qMainWindow_show"

class virtual qWidget =
object
end

class qMainWindow =
object(self)
  inherit qWidget
  val this = create ()
  method show = show this
  method destroy = destroy this
  initializer Gc.finalise (fun t -> t#destroy) self
end
