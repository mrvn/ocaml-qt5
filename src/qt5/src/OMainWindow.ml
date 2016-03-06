class virtual oMainWindow' = object(self)
  inherit OWidget.oWidget'
  method as_oMainWindow = (self :> oMainWindow')
end

type t = oMainWindow' Proxy.t

external show : t -> unit = "caml_mrvn_QT5_OMainWindow_show"
external centralWidget : t -> OWidget.oWidget Proxy.t = "caml_mrvn_QT5_OMainWindow_centralWidget"
external setCentralWidget : t -> OWidget.t -> unit
  = "caml_mrvn_QT5_OMainWindow_setCentralWidget"

class oMainWindow proxy = object(self)
  inherit oMainWindow'
  inherit OWidget.oWidget proxy
  method show = show self#as_oMainWindow#proxy
  method centralWidget : OWidget.oWidget =
    let widget_proxy = centralWidget self#as_oMainWindow#proxy
    in
    new OWidget.oWidget widget_proxy
  method setCentralWidget : 'd . (#OWidget.oWidget' as 'd) -> unit = fun w ->
      let widget_proxy = w#as_oWidget#proxy
      in
      setCentralWidget self#as_oMainWindow#proxy widget_proxy
end

external make : unit -> oMainWindow Proxy.t = "caml_mrvn_QT5_OMainWindow_make"

let make () =
  let proxy = make ()
  in
  new oMainWindow proxy
