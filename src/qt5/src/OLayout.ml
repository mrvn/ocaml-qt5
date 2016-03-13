include OWidget_OLayout

type t = OWidget_OLayout.oLayout OClass.t

(* abstract
module type Make = sig
  val stub : unit -> #oLayout OClass.t
end

class qLayout () =
  let obj =
    let module E = (val (module struct
      external stub : unit -> #oLayout OClass.t = "caml_mrvn_QT5_OLayout_make"
    end) : Make)
    in
    E.stub ()
  in
object
  inherit oLayout obj
end
*)
  
