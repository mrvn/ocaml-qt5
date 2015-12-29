class virtual qMainWindow' =
object
  inherit QWidget.qWidget'
end

external create : unit -> qMainWindow' Proxy.t = "caml_mrvn_QT5_QMainWindow_create"
external show : qMainWindow' Proxy.t -> unit = "caml_mrvn_QT5_QMainWindow_show"

class qMainWindow =
object(self)
  inherit qMainWindow'
  inherit QWidget.qWidget (create ())
  method show = show proxy
end
