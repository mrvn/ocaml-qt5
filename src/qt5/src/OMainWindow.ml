class ['a] oMainWindow proxy = object
  inherit ['a] OWidget.oWidget proxy
    (*
  method show = show proxy
  method centralWidget =
    let proxy = centralWidget proxy
    in
    new QWidget.qWidget proxy
  method setCentralWidget : 'b 'c . ((#QWidget.qWidget' as 'b) #QWidget.qWidget as 'c) -> unit = fun w ->
    let proxy_w = w#proxy
    in
    setCentralWidget proxy proxy_w
    *)
end

external make : unit -> 'a oMainWindow Proxy.t
  = "caml_mrvn_QT5_OMainWindow_make"

let make () =
  let proxy = make ()
  in
  new oMainWindow proxy

external show : 'a oMainWindow Proxy.t -> unit
  = "caml_mrvn_QT5_OMainWindow_show"

let show win =
  let win = win#proxy
  in
  show win

external centralWidget : 'a oMainWindow Proxy.t -> 'b OWidget.oWidget Proxy.t
  = "caml_mrvn_QT5_OMainWindow_centralWidget"

let centralWidget win =
  let win = win#proxy in
  let proxy = centralWidget win
  in
  new OWidget.oWidget proxy

external setCentralWidget : 'a oMainWindow Proxy.t -> 'b OWidget.oWidget Proxy.t -> unit
  = "caml_mrvn_QT5_OMainWindow_setCentralWidget"

let setCentralWidget win w =
  let win = win#proxy in
  let w = w#proxy
  in
  setCentralWidget win w
