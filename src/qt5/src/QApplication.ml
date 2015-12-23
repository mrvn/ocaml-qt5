type t

external create : unit -> t = "qApplication_constructor"
external destroy : t -> unit = "qApplication_destructor"
external exec : t -> int = "qApplication_exec"

class virtual qObject =
object
end

class qApplication =
object(self)
  inherit qObject
  val this = Printf.printf "qApplication create\n%!"; create ()
  method exec = exec this
  method destroy = destroy this
  initializer Gc.finalise (fun t -> t#destroy) self
end
