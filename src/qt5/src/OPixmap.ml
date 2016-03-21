open External

class oPixmap obj = object(self)
  inherit OClass.oClass obj
  inherit OPaintDevice.oPaintDevice obj
  method as_oPixmap = (self :> oPixmap)
  method rect =
    let module E = (val (module struct
      type e = oPixmap OClass.t -> ORect.t
      external stub : oPixmap OClass.t -> ORect.t = "caml_mrvn_QT5_OPixmap_rect"
    end) : External with type e = oPixmap OClass.t -> ORect.t)
    in
    new ORect.oRect (E.stub self#as_oPixmap#obj)
end

type t = oPixmap OClass.t

module type Make = sig
  val stub : int -> int -> #oPixmap OClass.t
end

class qPixmap w h =
  let obj =
    let module E = (val (module struct
      external stub : int -> int -> #oPixmap OClass.t = "caml_mrvn_QT5_OPixmap_make"
    end) : Make)
    in
    E.stub w h
  in
object
  inherit oPixmap obj
end
