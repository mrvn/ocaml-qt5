open External

class oRect obj = object(self)
  inherit OClass.oClass obj
  method as_oRect = (self :> oRect)
end

type t = oRect OClass.t

module type Make = sig
  val stub : int -> int -> int -> int -> #oRect OClass.t
end

class qRect x y w h =
  let obj =
    let module E = (val (module struct
      external stub : int -> int -> int -> int -> #oRect OClass.t = "caml_mrvn_QT5_ORect_make"
    end) : Make)
    in
    E.stub x y w h
  in
object
  inherit oRect obj
end
