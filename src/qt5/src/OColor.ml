open External

class oColor obj = object(self)
  inherit OClass.oClass obj
  method as_oColor = (self :> oColor)
  method darker =
    let module E = (val (module struct
      type e = oColor OClass.t -> oColor OClass.t
      external stub : oColor OClass.t -> oColor OClass.t = "caml_mrvn_QT5_OColor_darker"
    end) : External with type e = oColor OClass.t -> oColor OClass.t)
    in
    new oColor (E.stub self#as_oColor#obj)
  method lighter =
    let module E = (val (module struct
      type e = oColor OClass.t -> oColor OClass.t
      external stub : oColor OClass.t -> oColor OClass.t = "caml_mrvn_QT5_OColor_lighter"
    end) : External with type e = oColor OClass.t -> oColor OClass.t)
    in
    new oColor (E.stub self#as_oColor#obj)
end

type t = oColor OClass.t

module type Make = sig
  val stub : string -> #oColor OClass.t
end

class qColor name =
  let obj =
    let module E = (val (module struct
      external stub : string -> #oColor OClass.t = "caml_mrvn_QT5_OColor_make"
    end) : Make)
    in
    E.stub name
  in
object
  inherit oColor obj
end
