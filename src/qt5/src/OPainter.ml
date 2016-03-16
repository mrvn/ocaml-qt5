open External

class oPainter obj = object(self:'a)
  inherit OClass.oClass obj
  method as_oPainter = (self :> oPainter)
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
