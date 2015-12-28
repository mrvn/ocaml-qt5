class type qApplication_type =
object
  inherit QObject.qObject_type
  method exec : int
end

type t = qApplication_type QObject.ptr
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

class qApplication argv =
  let r_init = create argv
  in
object
  val r = r_init
  inherit QObject.qObject r_init.app
  method exec = exec this
  method destroy = destroy r
end

let () = at_exit Gc.full_major
