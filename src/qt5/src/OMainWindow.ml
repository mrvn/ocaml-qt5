module rec E : sig
  val make : unit -> C.t Proxy.t
  val show : 'a C.oMainWindow Proxy.t -> unit
  val centralWidget : 'a C.oMainWindow Proxy.t -> 'b OWidget.oWidget Proxy.t
  val setCentralWidget : 'a C.oMainWindow Proxy.t -> 'b OWidget.oWidget Proxy.t -> unit
end = struct
  external make : unit -> C.t Proxy.t
    = "caml_mrvn_QT5_OMainWindow_make"
  external show : 'a C.oMainWindow Proxy.t -> unit
    = "caml_mrvn_QT5_OMainWindow_show"
  external centralWidget : 'a C.oMainWindow Proxy.t -> 'b OWidget.oWidget Proxy.t
    = "caml_mrvn_QT5_OMainWindow_centralWidget"
  external setCentralWidget : 'a C.oMainWindow Proxy.t -> 'b OWidget.oWidget Proxy.t -> unit
    = "caml_mrvn_QT5_OMainWindow_setCentralWidget"
end
and C : sig
  class ['a] oMainWindow : 'a Proxy.t -> object
    constraint 'a = 'b oMainWindow as 'a
    inherit ['a] OWidget.oWidget
    method show : unit
    method centralWidget : 'c . 'c OWidget.oWidget OWidget.oWidget
    method setCentralWidget : 'd . 'd OWidget.oWidget OWidget.oWidget -> unit
  end

  type t = ('a oMainWindow as 'a) oMainWindow

  val make : unit -> 'a oMainWindow
end = struct
  class ['a] oMainWindow proxy = object
    constraint 'a = 'b oMainWindow as 'a
    inherit ['a] OWidget.oWidget proxy
    method show = E.show proxy
    method centralWidget : 'c . 'c OWidget.oWidget OWidget.oWidget =
      let widget_proxy = E.centralWidget proxy
      in
      new OWidget.oWidget widget_proxy
    method setCentralWidget : 'd . 'd OWidget.oWidget OWidget.oWidget -> unit = fun w ->
      let widget_proxy = w#proxy
      in
      E.setCentralWidget proxy widget_proxy
  end

  type t = ('a oMainWindow as 'a) oMainWindow

  let make () =
    let proxy = E.make ()
    in
    new oMainWindow proxy
end

include C
