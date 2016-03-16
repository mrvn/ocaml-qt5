open External

class oRect obj = object(self)
  inherit OClass.oClass obj
  method as_oRect = (self :> oRect)
  method x =
    let module E = (val (module struct
      type e = oRect OClass.t -> int
      external stub : oRect OClass.t -> int = "caml_mrvn_QT5_ORect_x"
    end) : External with type e = oRect OClass.t -> int)
    in
    E.stub self#as_oRect#obj
  method y =
    let module E = (val (module struct
      type e = oRect OClass.t -> int
      external stub : oRect OClass.t -> int = "caml_mrvn_QT5_ORect_y"
    end) : External with type e = oRect OClass.t -> int)
    in
    E.stub self#as_oRect#obj
  method width =
    let module E = (val (module struct
      type e = oRect OClass.t -> int
      external stub : oRect OClass.t -> int = "caml_mrvn_QT5_ORect_width"
    end) : External with type e = oRect OClass.t -> int)
    in
    E.stub self#as_oRect#obj
  method height =
    let module E = (val (module struct
      type e = oRect OClass.t -> int
      external stub : oRect OClass.t -> int = "caml_mrvn_QT5_ORect_height"
    end) : External with type e = oRect OClass.t -> int)
    in
    E.stub self#as_oRect#obj
  method top =
    let module E = (val (module struct
      type e = oRect OClass.t -> int
      external stub : oRect OClass.t -> int = "caml_mrvn_QT5_ORect_top"
    end) : External with type e = oRect OClass.t -> int)
    in
    E.stub self#as_oRect#obj
  method bottom =
    let module E = (val (module struct
      type e = oRect OClass.t -> int
      external stub : oRect OClass.t -> int = "caml_mrvn_QT5_ORect_bottom"
    end) : External with type e = oRect OClass.t -> int)
    in
    E.stub self#as_oRect#obj
  method left =
    let module E = (val (module struct
      type e = oRect OClass.t -> int
      external stub : oRect OClass.t -> int = "caml_mrvn_QT5_ORect_left"
    end) : External with type e = oRect OClass.t -> int)
    in
    E.stub self#as_oRect#obj
  method right =
    let module E = (val (module struct
      type e = oRect OClass.t -> int
      external stub : oRect OClass.t -> int = "caml_mrvn_QT5_ORect_right"
    end) : External with type e = oRect OClass.t -> int)
    in
    E.stub self#as_oRect#obj
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
