external exec : unit -> int = "caml_mrvn_QT5_OApplication_exec"

class ['a] oApplication proxy =
object
  inherit ['a] OObject.oObject proxy
  method exec = exec ()
end

external make : string array -> 'a oApplication Proxy.t
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
