type t
type a
type b
type r = {
  app : t;
  argc : a;
  argv : b;
}

external create : string array -> r = "qApplication_constructor"
external destroy : r -> unit = "qApplication_destructor"
external exec : t -> int = "qApplication_exec"

class virtual qObject =
object
end

class qApplication ?(args = Sys.argv) () =
object(self)
  inherit qObject
  val this = Printf.printf "qApplication create\n%!"; create args
  method exec = exec this.app
(*  method destroy = destroy this
*)  initializer Gc.finalise destroy this
end

let () = at_exit Gc.full_major
