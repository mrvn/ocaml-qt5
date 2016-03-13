open External

class oMainWindow obj = object(self)
  inherit OWidget.oWidget obj
  method as_oMainWindow = (self :> oMainWindow)
  method setCentralWidget : 'a . (<as_oWidget : OWidget.oWidget; ..> as 'a) -> unit = fun widget ->
    let module E = (val (module struct
      type e = oMainWindow OClass.t -> OWidget.t -> unit
      external stub : oMainWindow OClass.t -> OWidget.t -> unit = "caml_mrvn_QT5_OMainWindow_setCentralWidget"
    end) : External with type e = oMainWindow OClass.t -> OWidget.t -> unit)
    in
    E.stub self#as_oMainWindow#obj widget#as_oWidget#obj
end

type t = oMainWindow OClass.t

module type Make = sig
  val stub : unit -> #oMainWindow OClass.t
end

class qMainWindow () =
  let obj =
    let module E = (val (module struct
      external stub : unit -> #oMainWindow OClass.t = "caml_mrvn_QT5_OMainWindow_make"
    end) : Make)
    in
    E.stub ()
  in
object
  inherit oMainWindow obj
end
