open External

class oLayoutItem obj = object(self)
  inherit OClass.oClass obj
  method as_oLayoutItem = (self :> oLayoutItem)
end

type t = oLayoutItem OClass.t

(* abstract
module type Make = sig
  val stub : unit -> #oLayoutItem OClass.t
end

class qLayoutItem () =
  let obj =
    let module E = (val (module struct
      external stub : unit -> #oLayoutItem OClass.t = "caml_mrvn_QT5_OLayoutItem_make"
    end) : Make)
    in
    E.stub ()
  in
object
  inherit oLayoutItem obj
end
*)

