open External

include OWidget_OLayout

class virtual paintEvent = object(self)
  method external_paintEvent event =
    self#paintEvent (new OPaintEvent.oPaintEvent event)
  method virtual paintEvent : OPaintEvent.oPaintEvent -> unit
  method qPaintEvent : 'a . (<as_oPaintEvent : OPaintEvent.oPaintEvent; ..> as 'a) -> unit = fun event ->
    let module E = (val (module struct
      type e = oWidget OClass.t -> OPaintEvent.t -> unit
      external stub : oWidget OClass.t -> OPaintEvent.t -> unit = "caml_mrvn_QT5_OWidget_qPaintEvent"
    end) : External with type e = oWidget OClass.t -> OPaintEvent.t -> unit)
    in
    E.stub self#as_oWidget#obj event#as_oPaintEvent#obj
  method virtual as_oWidget : oWidget
end

type t = oWidget OClass.t
module type Make = sig
  val stub : unit -> #oWidget OClass.t
end

class qWidget () =
  let obj =
    let module E = (val (module struct
      external stub : unit -> #oWidget OClass.t = "caml_mrvn_QT5_OWidget_make"
    end) : Make)
    in
    E.stub ()
  in
object
  inherit oWidget obj
end
