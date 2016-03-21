open External

include OWidget_OLayout

class virtual paintEvent = object(self)
  method virtual as_oWidget : oWidget
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
end

class virtual keyPressEvent = object(self)
  method virtual as_oWidget : oWidget
  method external_keyPressEvent event =
    self#keyPressEvent (new OKeyEvent.oKeyEvent event)
  method virtual keyPressEvent : OKeyEvent.oKeyEvent -> unit
  method qKeyPressEvent : 'a . (<as_oKeyEvent : OKeyEvent.oKeyEvent; ..> as 'a) -> unit = fun event ->
    let module E = (val (module struct
      type e = oWidget OClass.t -> OKeyEvent.t -> unit
      external stub : oWidget OClass.t -> OKeyEvent.t -> unit = "caml_mrvn_QT5_OWidget_qKeyPressEvent"
    end) : External with type e = oWidget OClass.t -> OKeyEvent.t -> unit)
    in
    E.stub self#as_oWidget#obj event#as_oKeyEvent#obj
end

class virtual sizeHint = object(self)
  method virtual as_oWidget : oWidget
  method external_sizeHint =
    self#sizeHint#as_oSize#obj
  method virtual sizeHint : OSize.oSize
  method qSizeHint =
    let module E = (val (module struct
      type e = oWidget OClass.t -> OSize.t
      external stub : oWidget OClass.t -> OSize.t = "caml_mrvn_QT5_OWidget_qSizeHint"
    end) : External with type e = oWidget OClass.t -> OSize.t)
    in
    new OSize.oSize (E.stub self#as_oWidget#obj)
end

class virtual minimumSizeHint = object(self)
  method virtual as_oWidget : oWidget
  method external_minimumSizeHint =
    self#minimumSizeHint#as_oSize#obj
  method virtual minimumSizeHint : OSize.oSize
  method qMinimumSizeHint =
    let module E = (val (module struct
      type e = oWidget OClass.t -> OSize.t
      external stub : oWidget OClass.t -> OSize.t = "caml_mrvn_QT5_OWidget_qMinimumSizeHint"
    end) : External with type e = oWidget OClass.t -> OSize.t)
    in
    new OSize.oSize (E.stub self#as_oWidget#obj)
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
