class virtual qApplication' =
object
  inherit QObject.qObject'
  method virtual exec : int
end

external create : StringArray.t -> qApplication' Proxy.t = "caml_mrvn_QT5_QApplication_create"
external exec : unit -> int = "caml_mrvn_QT5_QApplication_exec"

class qApplication argv =
  let argv_init = StringArray.create argv
  in
object(self)
  val argv = argv_init
  inherit QObject.qObject (create argv_init)
  method exec = exec ()
end

let () = at_exit Gc.full_major
