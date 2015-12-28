class type qMainWindow_type =
object
  inherit QWidget.qWidget_type
end

type t = qMainWindow_type QObject.ptr
external create : unit -> t = "qMainWindow_constructor"
external destroy : t -> unit = "qMainWindow_destructor"
external show : t -> unit = "qMainWindow_show"

class qMainWindow =
object(self)
  inherit QWidget.qWidget (create ())
  method show = show this
end
