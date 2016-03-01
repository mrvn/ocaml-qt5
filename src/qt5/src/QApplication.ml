class virtual qApplication' =
object
  inherit QObject.qObject'
  method virtual exec : int
end

external create : StringArray.t -> qApplication' Proxy.t = "caml_mrvn_QT5_QApplication_create"
external exec : unit -> int = "caml_mrvn_QT5_QApplication_exec"

class ['a] qApplication argv =
  let argv_init = StringArray.create argv
  in
object(self)
  val argv = argv_init
  inherit ['a] QObject.qObject (create argv_init)
  method exec = exec ()
end

(* show backtraces on failure *)
let () = Printexc.record_backtrace true

(* free all resources at exit *)
let () = at_exit Gc.full_major
