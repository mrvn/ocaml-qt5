open External

class oGridLayout obj = object(self)
  inherit OLayout.oLayout obj
  method as_oGridLayout = (self :> oGridLayout)
  method addWidgetAt : 'a . (<as_oWidget : OWidget.oWidget; ..> as 'a) -> 'b = fun widget ?(rowSpan=1) ?(columnSpan=1) row column ->
    let module E = (val (module struct
      type e = oGridLayout OClass.t -> OWidget.t -> int * int * int * int -> unit
      external stub : oGridLayout OClass.t -> OWidget.t -> int * int * int * int -> unit = "caml_mrvn_QT5_OGridLayout_addWidgetAt"
    end) : External with type e = oGridLayout OClass.t -> OWidget.t -> int * int * int * int -> unit)
    in
    E.stub self#as_oGridLayout#obj widget#as_oWidget#obj (row, column, rowSpan, columnSpan)
end

type t = oGridLayout OClass.t

module type Make = sig
  val stub : unit -> #oGridLayout OClass.t
end

class qGridLayout () =
  let obj =
    let module E = (val (module struct
      external stub : unit -> #oGridLayout OClass.t = "caml_mrvn_QT5_OGridLayout_make"
    end) : Make)
    in
    E.stub ()
  in
object
  inherit oGridLayout obj
end

