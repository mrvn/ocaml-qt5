open External

class oAbstractButton obj = object(self)
  inherit OWidget.oWidget obj
  method as_oAbstractButton = (self :> oAbstractButton)
  method clicked : (oAbstractButton, bool -> unit) Signal.signal =
    let module E = (val (module struct
      type e = unit -> (oAbstractButton, bool -> unit) Signal.t
      external stub : unit -> (oAbstractButton, bool -> unit) Signal.t = "caml_mrvn_QT5_QAbstractButton_clicked"
    end) : External with type e = unit -> (oAbstractButton, bool -> unit) Signal.t)
    in
    new Signal.signal self#as_oAbstractButton (E.stub ())
end

type t = oAbstractButton OClass.t

  (*
external make : unit -> t = "caml_mrvn_QT5_OAbstractButton_make"

let make () =
  let obj = make ()
  in
  new oAbstractButton obj
  *)
  
(*
external clicked : unit -> (oAbstractButton', bool -> unit) Signal.t =
  "caml_mrvn_QT5_QAbstractButton_clicked"

class oAbstractButton proxy = object(self)
  inherit oAbstractButton'
  inherit OWidget.oWidget proxy
  method clicked = new Signal.signal self#as_oAbstractButton#proxy (clicked ())
end
*)
  
