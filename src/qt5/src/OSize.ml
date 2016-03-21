open External

class oSize obj = object(self)
  inherit OClass.oClass obj
  method as_oSize = (self :> oSize)
  method width =
    let module E = (val (module struct
      type e = oSize OClass.t -> int
      external stub : oSize OClass.t -> int = "caml_mrvn_QT5_OSize_width"
    end) : External with type e = oSize OClass.t -> int)
    in
    E.stub self#as_oSize#obj
  method height =
    let module E = (val (module struct
      type e = oSize OClass.t -> int
      external stub : oSize OClass.t -> int = "caml_mrvn_QT5_OSize_height"
    end) : External with type e = oSize OClass.t -> int)
    in
    E.stub self#as_oSize#obj
end

type t = oSize OClass.t

module type Make = sig
  val stub : int -> int -> #oSize OClass.t
end

class qSize width height =
  let obj =
    let module E = (val (module struct
      external stub : int -> int -> #oSize OClass.t = "caml_mrvn_QT5_OSize_make"
    end) : Make)
    in
    E.stub width height
  in
object
  inherit oSize obj
end
