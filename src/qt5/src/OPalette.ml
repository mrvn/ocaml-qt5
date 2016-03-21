open External

class oPalette obj = object(self)
  inherit OClass.oClass obj
  method as_oPalette = (self :> oPalette)
  method background =
    let module E = (val (module struct
      type e = oPalette OClass.t -> OColor.t
      external stub : oPalette OClass.t -> OColor.t = "caml_mrvn_QT5_OPalette_background"
    end) : External with type e = oPalette OClass.t -> OColor.t)
    in
    new OColor.oColor (E.stub self#as_oPalette#obj)
end

type t = oPalette OClass.t

module type Make = sig
  val stub : unit -> #oPalette OClass.t
end

class qPalette () =
  let obj =
    let module E = (val (module struct
      external stub : unit -> #oPalette OClass.t = "caml_mrvn_QT5_OPalette_make"
    end) : Make)
    in
    E.stub ()
  in
object
  inherit oPalette obj
end
