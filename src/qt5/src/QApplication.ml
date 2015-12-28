class type qApplication_type =
object
  inherit QObject.qObject_type
  method exec : int
end

type t = qApplication_type QObject.ptr

external create : StringArray.t -> t = "qApplication_constructor"
external exec : t -> int = "qApplication_exec"

class qApplication argv =
  let argv_init = StringArray.create argv
  in
object
  val argv = argv_init
  inherit QObject.qObject (create argv_init)
  method exec = exec this
end

let () = at_exit Gc.full_major
