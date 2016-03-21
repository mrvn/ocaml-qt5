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
  method fillRect : 'a . int -> int -> int -> int -> (<as_oColor : OColor.oColor; ..> as 'a) -> unit = fun x y w h color ->
    let module E = (val (module struct
      type e = oPainter OClass.t -> ORect.t -> OColor.t -> unit
      external stub : oPainter OClass.t -> ORect.t -> OColor.t -> unit = "caml_mrvn_QT5_OPainter_fillRect"
    end) : External with type e = oPainter OClass.t -> ORect.t -> OColor.t -> unit)
    in
    let rect = new ORect.qRect x y w h
    in
    E.stub self#as_oPainter#obj rect#as_oRect#obj color#as_oColor#obj
  method setPenColor : 'a . (<as_oColor : OColor.oColor; ..> as 'a) -> unit = fun color ->
    let module E = (val (module struct
      type e = oPainter OClass.t -> OColor.t -> unit
      external stub : oPainter OClass.t -> OColor.t -> unit = "caml_mrvn_QT5_OPainter_setPenColor"
    end) : External with type e = oPainter OClass.t -> OColor.t -> unit)
    in
    E.stub self#as_oPainter#obj color#as_oColor#obj
  method drawLine x1 y1 x2 y2 =
    let module E = (val (module struct
      type e = oPainter OClass.t -> int -> int -> int -> int -> unit
      external stub : oPainter OClass.t -> int -> int -> int -> int -> unit = "caml_mrvn_QT5_OPainter_drawLine"
    end) : External with type e = oPainter OClass.t -> int -> int -> int -> int -> unit)
    in
    E.stub self#as_oPainter#obj x1 y1 x2 y2
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
