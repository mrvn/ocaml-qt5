class virtual qMainWindow' =
object
  inherit QWidget.qWidget'
  method virtual show : unit
  method virtual centralWidget : QWidget.qWidget' QWidget.qWidget
  method virtual setCentralWidget :
      'a 'b . ((#QWidget.qWidget' as 'a) #QWidget.qWidget as 'b) -> unit
end

external create : unit -> qMainWindow' Proxy.t
  = "caml_mrvn_QT5_QMainWindow_create"
external show : qMainWindow' Proxy.t -> unit
  = "caml_mrvn_QT5_QMainWindow_show"
external centralWidget : qMainWindow' Proxy.t -> QWidget.qWidget' Proxy.t
  = "caml_mrvn_QT5_QMainWindow_centralWidget"
external setCentralWidget :
  qMainWindow' Proxy.t -> #QWidget.qWidget' Proxy.t -> unit
    = "caml_mrvn_QT5_QMainWindow_setCentralWidget"

class ['a] qMainWindow =
object(self)
  inherit qMainWindow'
  inherit ['a] QWidget.qWidget (create ())
  method show = show proxy
  method centralWidget =
    let proxy = centralWidget proxy
    in
    new QWidget.qWidget proxy
  method setCentralWidget : 'b 'c . ((#QWidget.qWidget' as 'b) #QWidget.qWidget as 'c) -> unit = fun w ->
    let proxy_w = w#proxy
    in
    setCentralWidget proxy proxy_w
end
