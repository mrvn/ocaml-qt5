open External

type shadow =
| Plain
| Raised
| Sunken

type shape =
| NoFrame
| Box
| Panel
| StyledPanel
| HLine
| VLine
| WinPanel
  
class oFrame obj = object(self)
  inherit OWidget.oWidget obj
  method as_oFrame = (self :> oFrame)
  method setFrameStyle ?(shadow=Plain) ?(shape=NoFrame) () =
    let module E = (val (module struct
      type e = oFrame OClass.t -> int -> unit
      external stub : oFrame OClass.t -> int -> unit = "caml_mrvn_QT5_OFrame_setFrameStyle"
    end) : External with type e = oFrame OClass.t -> int -> unit)
    in
    let style =
      match shadow with
      | Plain  -> 0x0010
      | Raised -> 0x0020
      | Sunken -> 0x0030
    in
    let style = style lor
      match shape with
      | NoFrame     -> 0x0000
      | Box         -> 0x0001
      | Panel       -> 0x0002
      | StyledPanel -> 0x0006
      | HLine       -> 0x0004
      | VLine       -> 0x0005
      | WinPanel    -> 0x0003
    in
    E.stub self#as_oFrame#obj style
  method frameWidth =
    let module E = (val (module struct
      type e = oFrame OClass.t -> int
      external stub : oFrame OClass.t -> int = "caml_mrvn_QT5_OFrame_frameWidth"
    end) : External with type e = oFrame OClass.t -> int)
    in
    E.stub self#as_oFrame#obj
end

type t = oFrame OClass.t

module type Make = sig
  val stub : unit -> #oFrame OClass.t
end

class qFrame () =
  let obj =
    let module E = (val (module struct
      external stub : unit -> #oFrame OClass.t = "caml_mrvn_QT5_OFrame_make"
    end) : Make)
    in
    E.stub ()
  in
object
  inherit oFrame obj
end
