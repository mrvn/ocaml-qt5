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

(* FIXME: AbstractButton is abstract, provide virtual class with virtual methods and glue them to c++ code *)
