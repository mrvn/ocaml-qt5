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

external make : string array -> t
  = "caml_mrvn_QT5_OApplication_make"

let make args =
  let proxy = make args
  in
  new oApplication proxy

(* show backtraces on failure *)
let () = Printexc.record_backtrace true

(* free all resources at exit *)
let () =
  at_exit
    (fun () ->
      let rec loop = function
	| 0 -> ()
	| n -> Gc.full_major (); loop (n - 1)
      in
      loop 10)
