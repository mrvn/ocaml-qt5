open External

class oWidget obj = object(self)
  inherit OObject.oObject obj
  method as_oWidget = (self :> oWidget)
  method resize (x, y) =
    let module E = (val (module struct
      type e = oWidget OClass.t -> int -> int -> unit
      external stub : oWidget OClass.t -> int -> int -> unit = "caml_mrvn_QT5_OWidget_resize"
    end) : External with type e = oWidget OClass.t -> int -> int -> unit)
    in
    E.stub self#as_oWidget#obj x y
  method setWindowTitle text =
    let module E = (val (module struct
      type e = oWidget OClass.t -> string -> unit
      external stub : oWidget OClass.t -> string -> unit = "caml_mrvn_QT5_OWidget_setWindowTitle"
    end) : External with type e = oWidget OClass.t -> string -> unit)
    in
    E.stub self#as_oWidget#obj text
  method setLayout : 'a . (<as_oLayout : oLayout; ..> as 'a) -> unit = fun layout ->
    let module E = (val (module struct
      type e = oWidget OClass.t -> oLayout OClass.t -> unit
      external stub : oWidget OClass.t -> oLayout OClass.t -> unit = "caml_mrvn_QT5_OWidget_setLayout"
    end) : External with type e = oWidget OClass.t -> oLayout OClass.t -> unit)
    in
    E.stub self#as_oWidget#obj layout#as_oLayout#obj
  method show =
    let module E = (val (module struct
      type e = oWidget OClass.t -> unit
      external stub : oWidget OClass.t -> unit = "caml_mrvn_QT5_OWidget_show"
    end) : External with type e = oWidget OClass.t -> unit)
    in
    E.stub self#as_oWidget#obj
end

and oLayout obj = object(self)
  inherit OObject.oObject obj
  method as_oLayout = (self :> oLayout)
  method addWidget : 'a . (<as_oWidget : oWidget; ..> as 'a) -> unit = fun widget ->
    let module E = (val (module struct
      type e = oLayout OClass.t -> oWidget OClass.t -> unit
      external stub : oLayout OClass.t -> oWidget OClass.t -> unit = "caml_mrvn_QT5_OLayout_addWidget"
    end) : External with type e = oLayout OClass.t -> oWidget OClass.t -> unit)
    in
    E.stub self#as_oLayout#obj widget#as_oWidget#obj
end
