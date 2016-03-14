include OWidget_OLayout

type t = oWidget OClass.t
module type Make = sig
  val stub : unit -> #oWidget OClass.t
end

class qWidget () =
  let obj =
    let module E = (val (module struct
      external stub : unit -> #oWidget OClass.t = "caml_mrvn_QT5_OWidget_make"
    end) : Make)
    in
    E.stub ()
  in
object
  inherit oWidget obj
end
