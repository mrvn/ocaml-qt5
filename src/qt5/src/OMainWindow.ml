open External

class oMainWindow obj = object(self)
  inherit OWidget.oWidget obj
  method as_oMainWindow = (self :> oMainWindow)
  method show =
    let module E = (val (module struct
      type e = oMainWindow OClass.t -> unit
      external stub : oMainWindow OClass.t -> unit = "caml_mrvn_QT5_OMainWindow_show"
    end) : External with type e = oMainWindow OClass.t -> unit)
    in
    E.stub self#as_oMainWindow#obj
  method setCentralWidget : 'a . (<as_oWidget : OWidget.oWidget; ..> as 'a) -> unit = fun widget ->
    let module E = (val (module struct
      type e = oMainWindow OClass.t -> OWidget.t -> unit
      external stub : oMainWindow OClass.t -> OWidget.t -> unit = "caml_mrvn_QT5_OMainWindow_setCentralWidget"
    end) : External with type e = oMainWindow OClass.t -> OWidget.t -> unit)
    in
    E.stub self#as_oMainWindow#obj widget#as_oWidget#obj
end

type t = oMainWindow OClass.t

  (*
external centralWidget : t -> OWidget.oWidget Proxy.t = "caml_mrvn_QT5_OMainWindow_centralWidget"
external setCentralWidget : t -> OWidget.t -> unit
  = "caml_mrvn_QT5_OMainWindow_setCentralWidget"
  *)
  
external make : unit -> t = "caml_mrvn_QT5_OMainWindow_make"

let make () =
  let obj = make ()
  in
  new oMainWindow obj
