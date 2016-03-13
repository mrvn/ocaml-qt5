open External
  
class oApplication obj = object(self)
  inherit OObject.oObject obj
  method as_oApplication = (self :> oApplication)
  method exec =
    let module E = (val (module struct
      type e = unit -> int
      external stub : unit -> int = "caml_mrvn_QT5_OApplication_exec"
    end) : External with type e = unit -> int)
    in
    E.stub ()
end

type t = oApplication OClass.t

module type Make = sig
  val stub : string array -> #oApplication OClass.t
end

class qApplication args =
  let obj =
    let module E = (val (module struct
      external stub : string array -> #oApplication OClass.t = "caml_mrvn_QT5_OApplication_make"
    end) : Make)
    in
    E.stub args
  in
object
  inherit oApplication obj
end

(* show backtraces on failure *)
let () = Printexc.record_backtrace true

(* free all resources at exit *)
let () =
  at_exit
    (fun () ->
      let rec loop = function
	| 0 -> ()
	| n -> Printf.printf "Gc.full_major ()\n%!"; Gc.full_major (); loop (n - 1)
      in
      loop 10)
