class virtual oApplication' = object(self)
  inherit OObject.oObject'
  method as_oApplication = (self :> oApplication')
end

type t = oApplication' Proxy.t

external exec : unit -> int = "caml_mrvn_QT5_OApplication_exec"

class oApplication proxy = object
  inherit oApplication'
  inherit OObject.oObject proxy
  method exec = exec ()
end

external make : string array -> oApplication Proxy.t
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
