open External

(* must be mixed in with a child of OClass.t *)
class virtual oPaintDevice (obj : 'a OClass.t) = object(self:'a)
  method virtual as_oClass : OClass.oClass
  method virtual obj : 'a OClass.t
  method as_oPaintDevice = (self :> oPaintDevice)
end

type t = oPaintDevice OClass.t

(* protected
module type Make = sig
  val stub : unit -> #oPaintDevice OClass.t
end

class qPaintDevice () =
  let obj =
    let module E = (val (module struct
      external stub : unit -> #oPaintDevice OClass.t = "caml_mrvn_QT5_OPaintDevice_make"
    end) : Make)
    in
    E.stub ()
  in
PaintDevice
  inherit oPaintDevice obj
end
*)
