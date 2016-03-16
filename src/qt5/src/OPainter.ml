open External

class oPainter obj = object(self:'a)
  inherit OClass.oClass obj
  method as_oPainter = (self :> oPainter)
  method drawText : 'a . (<as_oRect : ORect.oRect; ..> as 'a) -> ?absolute:bool -> (Qt.alignmentHorizontal * Qt.alignemntVertical) -> string -> unit = fun rect ?(absolute=false) (horizontal, vertical) text ->
    let module E = (val (module struct
      type e = oPainter OClass.t -> ORect.t -> int -> string -> unit
      external stub :oPainter OClass.t -> ORect.t -> int -> string -> unit = "caml_mrvn_QT5_OPainter_drawText"
    end) : External with type e = oPainter OClass.t -> ORect.t -> int -> string -> unit)
    in
    let align = Qt.int_of_align absolute horizontal vertical
    in
    E.stub self#as_oPainter#obj rect#as_oRect#obj align text
end

type t = oPainter OClass.t

module type Make = sig
  val stub : OPaintDevice.t -> #oPainter OClass.t
end

class qPainter device =
  let obj =
    let module E = (val (module struct
      external stub : OPaintDevice.t -> #oPainter OClass.t = "caml_mrvn_QT5_OPainter_make"
    end) : Make)
    in
    E.stub device#as_oPaintDevice#obj
  in
object
  inherit oPainter obj
end
